/*
 * Button.c
 *
 *  Created on: 13.01.2021
 *      Author: Andreas Roth, Kevin Schultz, Sebastian Hofmaier
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"          // for several predefined macros like "GPIO_PORTN_BASE"
#include "driverlib/gpio.h"         // for gpio access
#include "examples\boards\ek-tm4c1294xl-boostxl-senshub\drivers\buttons.h"

//*******************************************************
// \brief Initialize the button on booster pack
// \param void
// \return int
//*******************************************************
int Button_Init(void)
{
    // Initialize the buttons.
    ButtonsInit();

    return (1);  // Success
}

//*******************************************************
// \brief The button action function
// \param void
// \return int
//*******************************************************
int Button_Action(void)
{
    unsigned char ucDelta, ucState;

    {
        // Poll the buttons. When called periodically this function will
        // run the button debouncing algorithm.
        ucState = ButtonsPoll(&ucDelta, 0);

        // Test to see if the left button (S1) was pressed and do something
        if(BUTTON_PRESSED(LEFT_BUTTON, ucState, ucDelta))
        {
        // TODO: Implement reset or acknowledge functionality
        }

        // Test to see if the right button (S2) was pressed and do something
        if(BUTTON_PRESSED(RIGHT_BUTTON, ucState, ucDelta))
        {
            // TODO: Implement start measurement functionality
        }
    }

    return (1);  // Success
}


