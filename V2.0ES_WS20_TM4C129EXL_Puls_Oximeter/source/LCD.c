/*
 * LCD.c
 *
 *  Created on: 20.12.2020
 *      Author: Andreas Roth, Kevin Schultz, Sebastian Hofmaier
 */

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "../booster_pack_display/CFAF128128B0145T.h" // Boosterpack display lib
#include "../header/LCD.h"
#include "../header/OMM_Modul.h"


// The system clock speed.
extern uint32_t g_ui32SysClock;

static const lcd_t lcd_display[LCD_STATES] =
        {
             {10, 10, {"Embedded Systems", "Puls-Oximeter", "v1.0", "Group5", NULL, NULL, NULL, NULL, NULL}, LCD_COLOR_TEXT},
             {10, 10, {"Active Measure Mode", "Puls (bpm): ", "SPO2 (%): ", NULL, NULL, NULL, NULL, NULL, NULL}, LCD_COLOR_TEXT},
             {10, 10, {"Inactive Mode", "No finger detected!", "Wait for another 5s!", NULL, NULL, NULL, NULL, NULL, NULL}, LCD_COLOR_TEXT},
             {10, 10, {"Eco Mode", "Going into sleep mode!", "Display will be turned off!", NULL, NULL, NULL, NULL, NULL, NULL}, LCD_COLOR_TEXT},
             {10, 10, {"Error Mode", "Error event occurred: ", "Error code: ", NULL, NULL, NULL, NULL, NULL, NULL}, LCD_COLOR_TEXT},
        };


/** @brief Display state on lcd display at booster pack
* @param  display                : lcd_t *
* @param  lcd_clear              : _Bool
* @return  1: Success
*          0: Error
*/
int LCD_Print(lcd_t * display, bool lcd_clear)
// call like LCD_print(&lcd_display[state_active], true); for welcome screen with state_active = 1 from OMM_Modul.h
{
    lcd_t * lcd_t_ptr = display;
    uint8_t index = 0;

    if((lcd_t_ptr && lcd_t_ptr->str) != NULL)
    {
        if(lcd_clear)
        {
            CFAF128128B0145T_clear(LCD_COLOR_BACKGROUND);
        }


        while(lcd_t_ptr->str[index] != NULL) // or \n
        {
            CFAF128128B0145T_text((lcd_t_ptr->x)+index, lcd_t_ptr->y, lcd_t_ptr->str, lcd_t_ptr->color, LCD_COLOR_BACKGROUND, 1, 1);
            index+=10;
        }

        return (1);  // Success
    }
    else
    {
        return (0);  // Error
    }
}

/** @brief Setup LCD-Display on booster pack
* @param  boosterPack_Pos       : 1 : boosterPackPos1
*                               : 2 : boosterPackPos2
* @param  sysClock                  : system clock [Hz]
* @param  spiClock                  : spi clock [Hz]
* @return  1: Success
*          0: Error
*/
int LCD_Init(uint8_t boosterPack_Pos, uint32_t sysClock, uint32_t spiClock)
{
 if (0 < boosterPack_Pos <= 2)
 {
     CFAF128128B0145T_init(boosterPack_Pos, sysClock, spiClock); // BoosterPack position 2 of the Educational BoosterPack MK II
     // Clear display input
     CFAF128128B0145T_clear(CFAF128128B0145T_color_black);
     //***** LCD Welcome message *****
     CFAF128128B0145T_text(10, 40, "Embedded Systems", CFAF128128B0145T_color_white, CFAF128128B0145T_color_black, 1, 1);
     CFAF128128B0145T_text(10, 50, "Puls-Oximeter", CFAF128128B0145T_color_white, CFAF128128B0145T_color_black, 1, 1);
     CFAF128128B0145T_text(10, 60, "v1.0", CFAF128128B0145T_color_white, CFAF128128B0145T_color_black, 1, 1);
     CFAF128128B0145T_text(10, 70, "Group5", CFAF128128B0145T_color_white, CFAF128128B0145T_color_black, 1, 1);

     return(1);  // success
 }
 else
 {
     return(0);  // Error
 }
}

/** @brief Display active measurement on LCD-Display at booster pack
* @param  puls                  : puls [bpm]
* @param  spo2                  : spo2 [%]
* @return  1: Success
*          0: Error
*/
int LCD_Active(uint32_t puls, uint32_t spo2)
{
 if ((sizeof(puls) && sizeof(spo2)) == sizeof(uint32_t))
 {
     char puls_text[3], sp02_text[3];
     sprintf(puls_text, "%i", puls);
     sprintf(sp02_text, "%i", spo2);
     // Clear display input
     CFAF128128B0145T_clear(CFAF128128B0145T_color_black);
     //***** LCD measurement message *****
     CFAF128128B0145T_text(10, 40, "Active Measure Mode", CFAF128128B0145T_color_white, CFAF128128B0145T_color_black, 1, 1);
     CFAF128128B0145T_text(10, 50, "Puls (bpm): ", CFAF128128B0145T_color_white, CFAF128128B0145T_color_black, 1, 1);
     CFAF128128B0145T_text(23, 50, puls_text, CFAF128128B0145T_color_white, CFAF128128B0145T_color_black, 1, 1);
     CFAF128128B0145T_text(10, 60, "SPO2 (%): ", CFAF128128B0145T_color_white, CFAF128128B0145T_color_black, 1, 1);
     CFAF128128B0145T_text(20, 60, sp02_text, CFAF128128B0145T_color_white, CFAF128128B0145T_color_black, 1, 1);

     return(1);  // success
 }
 else
 {
     return(0);  // Error
 }
}

/** @brief Display inactive measurement on LCD-Display at booster pack
* @return  1: Success
*          0: Error
*/
int LCD_Inactive(void)
{
 if (true)
 {
     // Clear display input
     CFAF128128B0145T_clear(CFAF128128B0145T_color_black);
     //***** LCD inactive measurement message *****
     CFAF128128B0145T_text(10, 40, "Inactive Mode", CFAF128128B0145T_color_white, CFAF128128B0145T_color_black, 1, 1);
     CFAF128128B0145T_text(10, 50, "No finger detected!", CFAF128128B0145T_color_white, CFAF128128B0145T_color_black, 1, 1);
     CFAF128128B0145T_text(10, 60, "Wait for 5s!", CFAF128128B0145T_color_white, CFAF128128B0145T_color_black, 1, 1);

     return(1);  // success
 }
 else
 {
     return(0);  // Error
 }
}

/** @brief Display eco mode on LCD-Display at booster pack
* @return  1: Success
*          0: Error
*/
int LCD_Eco(void)
{
 if (true)
 {
     // Clear display input
     CFAF128128B0145T_clear(CFAF128128B0145T_color_black);
     //***** LCD inactive measurement message *****
     CFAF128128B0145T_text(10, 40, "Changing to Eco Mode", CFAF128128B0145T_color_white, CFAF128128B0145T_color_black, 1, 1);
     CFAF128128B0145T_text(10, 50, "No finger was detected", CFAF128128B0145T_color_white, CFAF128128B0145T_color_black, 1, 1);
     CFAF128128B0145T_text(10, 60, "within 5s time!", CFAF128128B0145T_color_white, CFAF128128B0145T_color_black, 1, 1);

     return(1);  // success
 }
 else
 {
     return(0);  // Error
 }
}

/** @brief Display error mode on LCD-Display at booster pack
* @param  event            : 2 : event_error_watchdog
*                          : 3 : event_error_diagnostic
*                          : 4 : event_error_proceccingtimeextended
*                          : 5 : event_error_memoryoverflow
* @param  error_code           : error code (400...450)
* @param  error_message        : error message, e.g. watchdog triggerd
* @return  1: Success
*          0: Error
*/
int LCD_Error(uint32_t event, uint32_t error_code, const char *error_message)
{
 if ((1 < event <= 5) && (399 < error_code <= 450))
 {
     char event_text[3], error_text[3];
     sprintf(event_text, "%i", event);
     sprintf(error_text, "%i", error_code);
     // Clear display input
     CFAF128128B0145T_clear(CFAF128128B0145T_color_black);
     //***** LCD measurement message *****
     CFAF128128B0145T_text(10, 40, "Error Mode", CFAF128128B0145T_color_white, CFAF128128B0145T_color_black, 1, 1);
     CFAF128128B0145T_text(10, 50, "Error event occurred: ", CFAF128128B0145T_color_white, CFAF128128B0145T_color_black, 1, 1);
     CFAF128128B0145T_text(32, 50, event_text, CFAF128128B0145T_color_white, CFAF128128B0145T_color_black, 1, 1);
     CFAF128128B0145T_text(10, 60, "Error code: ", CFAF128128B0145T_color_white, CFAF128128B0145T_color_black, 1, 1);
     CFAF128128B0145T_text(22, 60, error_text, CFAF128128B0145T_color_white, CFAF128128B0145T_color_black, 1, 1);
     CFAF128128B0145T_text(10, 70, error_message, CFAF128128B0145T_color_white, CFAF128128B0145T_color_black, 1, 1);

     return(1);  // success
 }
 else
 {
     return(0);  // Error
 }
}

/** @brief Test function for LCD-Display on booster pack
* @param  state            : 0 : active_state
*                          : 1 : inactive_state
*                          : 2 : eco_state
*                          : 3 : error_state
* @param  event            : 0 : event_no_finger_detected
*                          : 1 : event_finger_detected
*                          : 2 : event_error_watchdog
*                          : 3 : event_error_diagnostic
*                          : 4 : event_error_proceccingtimeextended
*                          : 5 : event_error_memoryoverflow
* @param  error_code           : error code (400...450)
* @param  error_message        : error message, e.g. watchdog triggerd
* @return  1: Success
*          0: Error
*/
int LCD_Test(uint32_t state, uint32_t event, uint32_t error_code, const char *error_message)
{
    if(0 < state < 4)
    {
        // Setup booster pack lcd display
        // Select: 2 boosterPack_Pos, 120000000 Hz g_ui32SysClock, 20000000 Hz spiClock
        LCD_Init(2, g_ui32SysClock, 20000000);

        if(state == state_active)
        {
            // Display active measurement state with values for puls and spo2
            // Select: 90 puls, 99 spo2
            LCD_Active(90, 99);
        }

        if(state == state_inactive)
        {
            // Display inactive measurement state
            LCD_Inactive();
        }

        if(state == state_eco)
        {
            // Display eco mode state
            LCD_Eco();
        }

        if((state == state_error) && ((1 < event <= 5)))
        {
        // Display error mode state with values for event, error code and error message
        LCD_Error(event, error_code, error_message);
        }

        return(1);  // success
    }
    else
    {
        return(0);  // Error
    }

}
