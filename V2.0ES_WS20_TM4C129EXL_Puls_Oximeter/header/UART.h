/*
 * UART_Modul.h
 *
 *  Created on: 20.12.2020
 *      Author: Andreas Roth, Kevin Schultz, Sebastian Hofmaier
 */

#ifndef HEADER_UART_H_
#define HEADER_UART_H_


/** @brief This function sets up UART0 to be used for a console to display information
*/
void InitConsole(void);


/** @brief Display content of "str" on the console.
* @param  str       : char *
* @return  1: Success
*/
int UART_print(char * str);

#endif /* HEADER_UART_H_ */
