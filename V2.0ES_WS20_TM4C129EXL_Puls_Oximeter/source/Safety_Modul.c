/*
 * Safety_Modul.c
 *
 *  Created on: 20.12.2020
 *      Author: Andreas
 *
 *      Description: This module shall ensure that the expected functionality from the pulsoximeter is given. This module covers the following cases:
 *      -->Processing the signals shall not take more time as the frequency to measure the signals
 *      -->A two stage watchdog should prevent the the SW stucks at any time by informing the user via display about such an issue and executing a reset afterwards
 *      -->This module shall provide a few error codes to distingush between different error scenarios and to show a respective error message on the display
 *      -->To prevent corruption of values casued by an interrupt during a writing process in each measuruement cycle a "protect-funtion" shall be implemented.
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/watchdog.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "drivers/buttons.h"
#include "../header/OMM_Modul.h"
#include "../header/LCD.h"


/** @brief The interrupt handler for the watchdog
*/

void WatchdogIntHandler(void)
    {
        //Display commands:
        LCD_Error(event_error_watchdog, 400, "watchdog triggered, reset incoming..");
        SetEvent(event_error_watchdog);

    }
