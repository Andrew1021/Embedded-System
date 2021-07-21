/*
 * LUT.c
 *
 *  Look up table for ratio values
 *
 *  Created on: 09.01.2021
 *      Author: Andreas Roth, Kevin Schultz, Sebastian Hofmaier
 */

#include <stdbool.h>
#include <stdint.h>
#include "../header/LUT.h"


//*******************************************************
// \brief Look up table for spO2 value to the corresponding ratio
// \param    ratio: float
// \return   spO2 : uint16_t
//*******************************************************
uint16_t LUT_SpO2(float ratio)
{
    uint16_t spO2 = 0;

    if (ratio == 0)
        return 0;
    else if (ratio < 0.55)  //0.53
        spO2 = 99;
    else if (ratio < 0.60)  //0.57
        spO2 = 98;
    else if (ratio < 0.65)  //0.61
        spO2 = 97;
    else if (ratio < 0.67)  //0.63
        spO2 = 96;
    else if (ratio < 0.69)  //0.66
        spO2 = 95;
    else if (ratio < 0.70)  //0.69
        spO2 = 94;
    else if (ratio < 0.72)
        spO2 = 93;
    else if (ratio < 0.75)
        spO2 = 92;
    else if (ratio < 0.78)
        spO2 = 91;
    else if (ratio < 0.81)
        spO2 = 90;
    else if (ratio < 0.84)
        spO2 = 89;
    else if (ratio < 0.87)
        spO2 = 88;
    else if (ratio < 0.90)
        spO2 = 87;
    else if (ratio < 0.92)
        spO2 = 86;
    else if (ratio < 0.95)
        spO2 = 85;
    else if (ratio < 0.98)
        spO2 = 84;
    else if (ratio < 1.00)
        spO2 = 83;
    else if (ratio < 1.03)
        spO2 = 82;
    else if (ratio < 1.05)
        spO2 = 81;
    else if (ratio < 1.08)
        spO2 = 80;
    else if (ratio < 1.11)
        spO2 = 79;
    else if (ratio < 1.13)
        spO2 = 78;
    else if (ratio < 1.16)
        spO2 = 77;
    else if (ratio < 1.18)
        spO2 = 76;
    else if (ratio < 1.21)
        spO2 = 75;
    else if (ratio < 1.24)
        spO2 = 74;
    else if (ratio < 1.26)
        spO2 = 73;
    else if (ratio < 1.29)
        spO2 = 72;
    else if (ratio < 1.31)
        spO2 = 71;
    else if (ratio < 1.33)
        spO2 = 70;
    else if (ratio < 1.36)
        spO2 = 69;
    else if (ratio < 1.38)
        spO2 = 68;
    else if (ratio < 1.40)
        spO2 = 67;
    else if (ratio < 1.42)
        spO2 = 66;
    else if (ratio < 1.45)
        spO2 = 65;
    else if (ratio < 1.47)
        spO2 = 64;
    else if (ratio < 1.49)
        spO2 = 63;
    else if (ratio < 1.51)
        spO2 = 62;
    else if (ratio < 1.54)
        spO2 = 61;
    else if (ratio < 1.56)
        spO2 = 60;
    else if (ratio < 1.58)
        spO2 = 59;
    else if (ratio < 1.60)
        spO2 = 58;
    else if (ratio < 1.63)
        spO2 = 57;
    else if (ratio < 1.66)
        spO2 = 56;
    else if (ratio < 1.69)
        spO2 = 55;
    else if (ratio < 1.72)
        spO2 = 54;
    else if (ratio < 1.75)
        spO2 = 53;
    else if (ratio < 1.78)
        spO2 = 52;
    else if (ratio < 1.81)
        spO2 = 51;
    else if (ratio < 1.84)
        spO2 = 50;
    else if (ratio < 1.87)
        spO2 = 49;
    else if (ratio < 1.90)
        spO2 = 48;
    else if (ratio < 1.94)
        spO2 = 47;
    else if (ratio < 1.97)
        spO2 = 46;
    else if (ratio < 2.00)
        spO2 = 45;
    else if (ratio < 2.04)
        spO2 = 44;
    else if (ratio < 2.08)
        spO2 = 43;
    else if (ratio < 2.11)
        spO2 = 42;
    else if (ratio < 2.15)
        spO2 = 41;
    else if (ratio < 2.19)
        spO2 = 40;
    else if (ratio < 2.22)
        spO2 = 39;
    else if (ratio < 2.27)
        spO2 = 38;
    else if (ratio < 2.31)
        spO2 = 37;
    else if (ratio < 2.34)
        spO2 = 36;
    else
        spO2 = 35;


    return spO2;
}
