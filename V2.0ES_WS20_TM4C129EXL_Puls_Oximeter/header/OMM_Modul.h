/*
 * OMM_Modul.h
 *
 *  Created on: 20.12.2020
 *      Author: Andreas
 OMM Modul:
-Zusände
-Anpassung Messqrequenz
-Ausgabe

*/


#ifndef HEADER_OMM_MODUL_H_
#define HEADER_OMM_MODUL_H_

#include <stdint.h>
#include <stdbool.h>
#include "../header/timer.h"

/** @brief Includes all available states for state machine  */
typedef enum {
    state_active,   //normal operation      -->Übergabewerte: Puls + SPO2
    state_inactive, //no finger detected within 5s
    state_eco,      //no finger detected within another 5s in inactive state (--> in total: 10s)
    state_error,     //error occured         -->Übergabewerte: Event, Fehlercode und/oder Fehlerbeschreibung
} state_type;

/** @brief Includes all available events which can be set by other SW Modules for which the state machine triggers */
typedef enum {
    event_no_finger_detected,
    event_finger_detected,
    event_error_watchdog,
    event_error_diagnostic,
    event_error_proceccing_time_extended,
    event_error_memoryoverflow,
} event_type;

/** @brief Set the respective event for state machine
* @param  event         : event
* @return  void
*/

void SetEvent(event_type event);

/** @brief Passes the event which is currently active
* @param  event       : event
* @return  event
*/

event_type GetEvent(void);

/** @brief Function which checks events for a possible error. Return value is bool (false = no error occured)
* @param  void
* @return  error_occured : bool : false
*                        : bool : true
*/

bool ErrorOccured(void);

/** @brief This function implements the state machine which will be continuously called by the main to manage the operation modes
* @param  timer2         : timer
* @param  g_ui32SysClock : SystemClock
* @return  void
*/

void StateMachine(timer timer2, uint32_t g_ui32SysClock);

/** @brief This function will increment a specific value until it is 20 if a finger is detected, otherwise the value will be set as 0
* @param  void
* @return void
*/

void SecureFingerPlacement(void);

/** @brief This function will be called by the interrupt if timer2 whenever timer expired and it sets a value to true that the state machine can enter a new state
* @param  void
* @return void
*/

void TimeManagerOMM(void);

/** @brief If 20 times in a row a finger was detected the this function will return its return value as true
* @param  void
* @return  returnvalue   : bool : false
*                        : bool : true
*/

bool FingerPositioned(void);

#endif /* HEADER_OMM_MODUL_H_ */
