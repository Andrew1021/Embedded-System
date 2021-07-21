/*
 * LUT.h
 *
 *  Look up table for ratio values
 *
 *  Created on: 09.01.2021
 *      Author: Andreas Roth, Kevin Schultz, Sebastian Hofmaier
 */

#ifndef HEADER_LUT_H_
#define HEADER_LUT_H_

//*******************************************************
// \brief Look up table for spO2 value to the corresponding ratio
// \param    ratio: float
// \return   spO2 : uint16_t
//*******************************************************
uint16_t LUT_SpO2(float ratio);

#endif /* HEADER_LUT_H_ */
