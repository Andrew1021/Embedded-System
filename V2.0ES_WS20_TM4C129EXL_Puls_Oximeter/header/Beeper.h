/*
 * Beeper_Modul.h
 *
 *  Created on: 20.12.2020
 *      Author: Andreas Roth, Kevin Schultz, Sebastian Hofmaier
 */

#ifndef HEADER_BEEPER_H_
#define HEADER_BEEPER_H_

/** @brief Beeper tone in Hz   */
#define BEEPER_TONE 2930  // Hz


/** @brief Init beeper on booster pack
* @param   void
* @return  1: Success
*          0: Error
*/
int Beeper_Init(void);


/** @brief Play beeper tone on booster pack
* @param   void
* @return  1: Success
*          0: Error
*/
int Beeper_Tone(void);


/** @brief Close beeper on booster pack
* @param   void
* @return  1: Success
*          0: Error
*/
int Beeper_Close(void);


#endif /* HEADER_BEEPER_H_ */
