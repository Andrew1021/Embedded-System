/*
 * Processing.c
 *
 * For processing the ADC values
 *
 *  Created on: 09.01.2021
 *      Author: Andreas Roth, Kevin Schultz, Sebastian Hofmaier
 */

#include "../header/FIFO.h"
#include "../header/ADC.h"
#include "../header/Init.h"
#include "../header/Calculation.h"
#include "../header/Processing.h"
#include "../header/OMM_Modul.h"
#include "../header/Beeper.h"

static uint16_t pulse_detection_vals[3] = { 0 }; //contains the last three measured values from LED red

//*******************************************************
// \brief Detects wheter a finger is there or not
// \param    measuredVal: uint16_t
// \return   result : bool
//*******************************************************
static bool Finger_Detection(uint16_t measuredVal)
{
    // ADC Resolution 12 bit -> max value 4096
    // if no finger inserted the ADC should get the
    // full power from the photo diode
    return (measuredVal <= 3800);
}

//*******************************************************
// \brief Detects if there was a pulse peak, Idea:
//        If the value in the middle was the highest
//        the should be pulse, because spO2 was maximum
// \param    arrayIdx: uint16_t*
// \return   result : bool
//*******************************************************
static bool Pulse_Detection(uint16_t *arrayIdx)
{
    bool detected = (*arrayIdx < *(arrayIdx+1)) && (*(arrayIdx+2) < *(arrayIdx+1));
    return detected;
}

//*******************************************************
// \brief Update the array for the last three values
//        for pulse detection
// \param    value: uint16_t
// \return   result : bool
//*******************************************************
static void Update_Pulse_Detection(uint16_t value)
{
    pulse_detection_vals[2] = pulse_detection_vals[1];
    pulse_detection_vals[1] = pulse_detection_vals[0];
    pulse_detection_vals[0] = value;
}

//*******************************************************
// \brief Executes the processing routine
// \param    led: led_t
// \return   void
//*******************************************************
static uint32_t time_steps_pulse = 0;
void Execute_Processing(led_t measured_led)
{
    uint16_t adcVal_DC = ADC_Trigger(ADC_ID_ADC0); //Get current ADC value
    uint16_t adcVal_AC = ADC_Trigger(ADC_ID_ADC1); //Get current ADC value

    if(!Finger_Detection(adcVal_AC + adcVal_DC)) {
        SetEvent(event_no_finger_detected);
        return;
    }
    else {
        SetEvent(event_finger_detected);
    }

    bool pulse_detected = false;
    if (measured_led == LED_IR_ON) {
        Update_Pulse_Detection(adcVal_AC);
        pulse_detected = Pulse_Detection(&pulse_detection_vals[0]);
    }

    // Saving ADC values in corressponding FIFO
    switch(measured_led)
    {
        case LED_RED_ON:{
            Fifo_Write(&buffer_led_red_DC,   adcVal_DC);
            Fifo_Write(&buffer_led_red_AC,   adcVal_AC);
            break;
        }
        case LED_IR_ON: {
            Fifo_Write(&buffer_led_ir_DC,    adcVal_DC);
            Fifo_Write(&buffer_led_ir_AC,    adcVal_AC);
            break;
        }
        case LED_OFF:   {
            Fifo_Write(&buffer_led_off_DC,   adcVal_DC);
            Fifo_Write(&buffer_led_off_AC,   adcVal_AC);
            break;
        }
    }

    if(pulse_detected) {
        Beeper_Tone();
        time_steps_pulse++;
        Start_Calculation(time_steps_pulse);
        time_steps_pulse = 0;
    }
    else {
        time_steps_pulse++;
    }
}
