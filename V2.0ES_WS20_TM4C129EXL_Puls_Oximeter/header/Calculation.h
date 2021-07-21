/*
 * Calculation.h
 *
 *  Created on: 20.12.2020
 *      Author: Andreas Roth, Kevin Schultz, Sebastian Hofmaier
 */

#ifndef HEADER_COMPUTATION_MODULE_H_
#define HEADER_COMPUTATION_MODULE_H_

#include <stdint.h>
#include <stdbool.h>
#include "../header/FIFO.h"

typedef struct {
    float ac;
    float dc;
} voltage_t;

//*******************************************************
// \brief Starts the calculation of pulse and spO2
// \param    time_steps_pulse: uint32_t
// \return   void
//*******************************************************
void Start_Calculation();

#endif /* HEADER_COMPUTATION_MODULE_H_ */
