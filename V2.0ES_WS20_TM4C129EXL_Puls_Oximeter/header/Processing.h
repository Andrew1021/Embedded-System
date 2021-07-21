/*
 * Processing.h
 *
 * For processing the ADC values
 *
 *  Created on: 09.01.2021
 *      Author: Andreas Roth, Kevin Schultz, Sebastian Hofmaier
 */

#ifndef HEADER_PROCESSING_H_
#define HEADER_PROCESSING_H_

#include <stdbool.h>
#include <stdint.h>

//*******************************************************
// \enum led_t
// \brief Different LED types//
//*******************************************************
typedef enum {
    LED_RED_ON,
    LED_IR_ON,
    LED_OFF,
} led_t;

//*******************************************************
// \brief Executes the processing routine
// \param    led: ledType
// \return   void
//*******************************************************
void ExecuteProcessing(led_t led);


#endif /* HEADER_PROCESSING_H_ */
