/**
* \brief Library for booster pack LCD-Display usage
*
* \mainpage LCD-Display
*
* \section intro_sec Introduction
* This library provides functions for the booster pack LCD-Display usage
*
* \section license_sec License
* Property of Group 5.\n
* <a href="HTWG GitLab Embedded Systems Group 5">https://https://gitlab.ei.htwg-konstanz.de/es/ws2021/group5/-/tree/main</a>
*
* \section usage_sec Using the LCD library
* sample test code within the libray (function LCD_Test())
*
*
*
* Example code for the use of the booster pack lcd display
* \code{.c}
*
*
* void main(void)
* {
*
*    // Setup booster pack lcd display
*    // Select: 2 boosterPack_Pos, 120000000 Hz g_ui32SysClock, 20000000 Hz SPI-Clock
*    LCD_Init(2, g_ui32SysClock, 20000000);
*
*    // Display active measurement state with value for puls and spo2
*    // Select: 90 puls, 99 spo2
*    LCD_Active(90, 99);
*
*    while(1){}
*
* }
*
* \endcode
*
*
* \section history_sec Revision History
* Version  | Description
* ---------| -------------
* 0.0.0.1  | Initial version
*
* \section author_sec Author
* Andreas Roth, Kevin Schultz, Sebastian Hofmaier
*/

/**  @file LCD_Modul.h */
#ifndef HEADER_LCD_H_
#define HEADER_LCD_H_

/** @brief Highest available LCD display states, x, y, string length and color  */
#define LCD_STATES              5
#define LCD_X_MAX               128
#define LCD_Y_MAX               128
#define LCD_str_MAX             108
#define LCD_line_MAX            10
#define LCD_COLOR_TEXT          CFAF128128B0145T_color_white
#define LCD_COLOR_BACKGROUND    CFAF128128B0145T_color_black

/** @brief lcd-specific coordinates, text and color  */
typedef struct{
    unsigned int                     x;             //!< x coordinate, e.g. 10
    unsigned int                     y;             //!< y coordinate, e.g. 10
    const char       str[LCD_line_MAX];             //!< string, e.g. {"text1", "text2", "text3", ...
    unsigned int                 color;             //!< color, e.g. CFAF128128B0145T_color_white
} lcd_t;


/** @brief Setup lcd display on booster pack
* @param  boosterPack_Pos       : 1 : boosterPackPos1
*                               : 2 : boosterPackPos2
* @param  sysClock                  : system clock [Hz]
* @param  spiClock                  : spi clock [Hz]
* @return  1: Success
*          0: Error
*/
int LCD_Init(unsigned char boosterPack_Pos, unsigned int sysClock, unsigned int spiClock);


/** @brief Display state on lcd display at booster pack
* @param  display                : lcd_t *
* @param  lcd_clear              : _Bool
* @return  1: Success
*          0: Error
*/
int LCD_Print(lcd_t * display, _Bool lcd_clear);


/** @brief Display active measurement on lcd display at booster pack
* @param  puls                  : puls [bpm]
* @param  spo2                  : spo2 [%]
* @return  1: Success
*          0: Error
*/
int LCD_Active(unsigned int puls, unsigned int spo2);


/** @brief Display inactive measurement on lcd display at booster pack
* @return  1: Success
*          0: Error
*/
int LCD_Inactive(void);


/** @brief Display eco mode on lcd display at booster pack
* @return  1: Success
*          0: Error
*/
int LCD_Eco(void);


/** @brief Display error mode on lcd display at booster pack
* @param  event            : 2 : event_error_watchdog
*                          : 3 : event_error_diagnostic
*                          : 4 : event_error_proceccingtimeextended
*                          : 5 : event_error_memoryoverflow
* @param  error_code           : error code (400...450)
* @param  error_message        : error message, e.g. watchdog triggerd
* @return  1: Success
*          0: Error
*/
int LCD_Error(unsigned int event, unsigned int error_code, const char *error_message);


/** @brief Test function for lcd display on booster pack
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
int LCD_Test(unsigned int state, unsigned int event, unsigned int error_code, const char *error_message);

#endif /* HEADER_LCD_H_ */
