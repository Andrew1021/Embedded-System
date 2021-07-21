/*
 * Beeper.c
 *
 *  Created on: 20.12.2020
 *      Author: Andreas Roth, Kevin Schultz, Sebastian Hofmaier
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"          // for several predefined macros like "GPIO_PORTN_BASE"
#include "inc/hw_ints.h"            // Macros that define the interrupt assignment on Tiva C Series MCUs (e.g. "INT_TIMER0A")
#include "driverlib/sysctl.h"       // clock
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"         // for gpio access
#include "driverlib/pwm.h"          // for pwm access
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "../header/Beeper.h"
#include "../header/PWM.h"


/** @brief Beeper init function
* @return  1: Success
*          0: Error
*/
int Beeper_Init(void)
{
    PWM_Init(PWM_ID_PWM0_GEN2, 1, 2);

    return (1);  // Success
}


/** @brief Beeper tone function
* @return  1: Success
*          0: Error
*/
int Beeper_Tone(void)
{
    PWM_Enable(PWM_ID_PWM0_GEN2);

    return (1);  // Success
}


/** @brief Beeper close function
* @return  1: Success
*          0: Error
*/
int Beeper_Close(void)
{
    // enable peripheral again:
    PWM_Close(PWM_ID_PWM0_GEN2);

    return (1);  // Success
}
