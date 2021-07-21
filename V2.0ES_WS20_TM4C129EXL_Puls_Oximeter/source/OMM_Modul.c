/*
 * OMM_Modul.c
 *
 *  Created on: 20.12.2020
 *      Author: Sebastian Hofmaier, Andreas Roth, Kevin Schultz



OMM Modul:
-Zusände
-Anpassung Messqrequenz
-Ausgabe

Description of this SW Module:
This module implements a state machine.
Depending on the current event it is switching the active states depending if the respective conditions are given.
OMM is using Timer2 for the states which are timing depended like inactive (after 5s without a valid signal).
*/
#include <stdint.h>
#include <stdbool.h>

#include "driverlib/watchdog.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"

#include "../header/OMM_Modul.h"
#include "../header/timer.h"
#include "../header/I2C_MC4728.h"
#include "inc/hw_ints.h"            // Macros that define the interrupt assignment on Tiva C Series MCUs (e.g. "INT_TIMER0A")
#include "inc/hw_memmap.h"          // for several predefined macros like "GPIO_PORTN_BASE"


static event_type current_event;
static state_type current_state;
static uint8_t counter_finger_detected; //Counter to ensure that the finger is correctly positioned within a defined time range
static bool timer_status_OMM;    //Flag welches gesetzt wird solange Timer2 aktiv ist und 5s hoch zählt
static bool timer_expired_OMM;    //Flag welches gesetzt wird solange Timer2 aktiv ist und 5s hoch zählt


/** @brief Set the respective event for state machine
* @param  event         : event
* @return  void
*/
void SetEvent(event_type event)
{
    current_event = event;
}

/** @brief Passes the event which is currently active
* @param  event       : event
* @return  event
*/
event_type GetEvent(void)
{
    return current_event;
}

/** @brief Function which checks events for a possible error. Return value is bool (false = no error occured)
* @param  void
* @return  error_occured : bool : false
*                        : bool : true
*/

bool ErrorOccured(void)
{
    bool error_occured = false;

    if (GetEvent() == event_error_diagnostic || event_error_memoryoverflow || event_error_proceccing_time_extended || event_error_watchdog)
    {
        error_occured = true;
    }

    return error_occured;

}

/** @brief This function will increment a specific value until it is 20 if a finger is detected, otherwise the value will be set as 0
* @param  void
* @return void
*/

void SecureFingerPlacement(void)
{

    if (GetEvent() == event_finger_detected && counter_finger_detected < 20)
    {
        counter_finger_detected++;
    }
    if (GetEvent() == event_no_finger_detected)
    {
        counter_finger_detected = 0;
    }

}

/** @brief If 20 times in a row a finger was detected the this function will return its return value as true
* @param  void
* @return  returnvalue   : bool : false
*                        : bool : true
*/

bool FingerPositioned(void)
{
    bool returnvalue = false;

    if (counter_finger_detected == 20)
    {
        returnvalue = true;
    }
    return returnvalue;
}

/** @brief This function will be called by the interrupt if timer2 whenever timer expired and it sets a value to true that the state machine can enter a new state
* @param  void
* @return void
*/

void TimeManagerOMM(void)
{
    timer_expired_OMM = true;
}

/** @brief This function implements the state machine which will be continuously called by the main to manage the operation modes
* @param  timer2         : timer
* @param  g_ui32SysClock : SystemClock
* @return  void
*/

void StateMachine(timer timer2, uint32_t g_ui32SysClock)
{
    //Checks if finger is correctly positioned
    SecureFingerPlacement();

    //Clear watchdog interrupt
    ROM_WatchdogIntClear(WATCHDOG0_BASE);

    //Assigment of the respective event which is currently active
    current_event = GetEvent();

    switch(current_event)
    {
    case event_finger_detected:
        switch(current_state)
        {
        case state_active:
             break;

        case state_inactive:
            if (ErrorOccured() == false && FingerPositioned() == true)
            {
                current_state = state_active;
            }
            break;

        case state_eco:
            if (ErrorOccured() == false && FingerPositioned() == true)
            {
                current_state = state_active;
            }
            break;

        case state_error:
            //No event defined until yet which allows to leave state_error
            break;
        }
    case event_no_finger_detected:
        switch(current_state)
        {
        case state_active:
            //Flag abfragen ob es schon gesetzt ist bzw ob Timer schon läuft
            //-->Timer aktivieren falls nein der 5s hoch zählt bis er anspringt
            //-->Timer interrupt enabeln
            //-->Flag setzen für "timer aktiv"
            //Im Handler Hilfsfunktion TimeManager von OMM welcher das Flag "5s abgelaufen" setzt
            //Im Handler (wenn möglich): Timer wieder disabeln sodass er evtl für Übergang zu Eco verwendet werden kann
            //Abfragen ob Flag 5sabgelaufen gesetzt, falls ja state -->Eco und Flag zurück setzten

            if (timer_status_OMM == false)
            {
                Timer_Init(timer2, (g_ui32SysClock * 5));    //initializes and enables the timer + Periodendauer 5s (Wann soll Interrupt getriggert werden)
                TimerInterrupt_Init (timer2, 0xE0);          //initializes the interrupt for the respective timer
                timer_status_OMM = true;
            }

            if (timer_expired_OMM == true)
            {
                current_state = state_inactive;
                timer_expired_OMM = false;
            }
            break;

        case state_inactive:
            //Flag abfragen ob es schon gesetzt ist bzw ob Timer schon läuft
            //-->Timer aktivieren falls nein der 5s hoch zählt bis er anspringt
            //-->Timer interrupt enabeln
            //-->Flag setzen für "timer aktiv"
            //Im Handler Hilfsfunktion TimeManager von OMM welcher das Flag "5s abgelaufen" setzt
            //Im Handler (wenn möglich): Timer wieder disabeln sodass er evtl für Übergang zu Eco verwendet werden kann
            //Abfragen ob Flag 5sabgelaufen gesetzt, falls ja state -->Eco und Flag zurück setzten

            if (timer_status_OMM == false)
            {
                Timer_Init(timer2, (g_ui32SysClock * 5));    //initializes and enables the timer + Periodendauer 5s (Wann soll Interrupt getriggert werden)
                TimerInterrupt_Init (timer2, 0xE0);          //initializes the interrupt for the respective timer
                timer_status_OMM = true;
            }

            if (timer_expired_OMM == true)
            {
                current_state = state_eco;
                timer_expired_OMM = false;
                //            case state_eco: /*Anweisung*/
                //                            //Address Byte for MCP4728: 1100 000 0, DeviceCode=1100, AddressBits=000, R/nW=0(write)
                //                            FirstByte = 0xc0;
                //                            DAC_Write(FirstByte, 0xa0, 0x40, 0x00);     //2nd_Byte = 0b10100000(power-down ch_A), 3rd_Byte = 0b01000000(Vref=VDD 100kOhm)
                //                            DAC_Write(FirstByte, 0xa2, 0x40, 0x00);     //2nd_Byte = 0b10100010(power-down ch_B), 3rd_Byte = 0b01000000(Vref=VDD 100kOhm)
                //                            DAC_Write(FirstByte, 0xa4, 0x40, 0x00);     //2nd_Byte = 0b10100100(power-down ch_C), 3rd_Byte = 0b01000000(Vref=VDD 100kOhm)
                //                            DAC_Write(FirstByte, 0xa6, 0x40, 0x00);     //2nd_Byte = 0b10100110(power-down ch_D), 3rd_Byte = 0b01000000(Vref=VDD 100kOhm);
            }
            break;

        case state_eco:
            break;

        case state_error:
            //No event defined until yet which allows to leave state_error
            break;
        }
        case event_error_watchdog:
            switch(current_state)
            {
            case state_active:
                //
                break;

            case state_inactive:
                //
                break;

            case state_eco:
                //
                break;

            case state_error:
                //No event defined until yet which allows to leave state_error
                break;


//......
            }

        }
    }









