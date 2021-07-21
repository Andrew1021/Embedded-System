/*
 * Button.h
 *
 *  Created on: 13.01.2021
 *      Author: Andreas Roth, Kevin Schultz, Sebastian Hofmaier
 */

#ifndef HEADER_BUTTON_H_
#define HEADER_BUTTON_H_

/** @brief Map Left button to the GPIO Pin 0 of the button port. */
#define LEFT_BUTTON GPIO_PIN_0

/** @brief Map Right button to the GPIO Pin 1 of the button port. */
#define RIGHT_BUTTON GPIO_PIN_1

//*******************************************************
// \brief Initialize the button on booster pack
// \param void
// \return int : 1 : Success
//             : 0 : Error
//*******************************************************
int Button_Init(void);

//*******************************************************
// \brief The button action function
// \param void
// \return int : 1 : Success
//             : 0 : Error
//*******************************************************
int Button_Action(void);

#endif /* HEADER_BUTTON_H_ */
