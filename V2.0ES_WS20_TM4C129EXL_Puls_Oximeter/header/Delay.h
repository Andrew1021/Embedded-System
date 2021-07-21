/*********************************************************************
 *
 *                    Header for Simple Delay Routines
 *
 *********************************************************************
 * FileName:        Delay.h
 * Processor:       tm4c129exl
 * Compiler:        TI v20.2.3.LTS
 *
 * Institution:     HTWG Konstanz
 *
 * Authors                                         Date      Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Andreas Roth, Kevin Schultz, Sebastian Hofmaier 21.20.2020 Define prototype delay functions
 * Andreas Roth, Kevin Schultz, Sebastian Hofmaier 12.01.2020 Adapted delay function for TM4C platform
 ********************************************************************/

#ifndef HEADER_DELAY_H_
#define HEADER_DELAY_H_

/** @brief Import Frequency of system clock */
extern uint32_t g_ui32SysClock;

/** @brief Define Frequency to system clock 120 MHz */
#define Fcy   g_ui32SysClock

/** @brief Static defined delays */
/** @brief seconds */
#define DELAY_1S    (1 * Fcy) / 3
#define DELAY_2S    (2 * Fcy) / 3
#define DELAY_5S    (5 * Fcy) / 3
#define DELAY_10S   (10 * Fcy) / 3

/** @brief milliseconds */
#define DELAY_1MS   (1 * (Fcy / 3 / 1000))
#define DELAY_2MS   (2 * (Fcy / 3 / 1000))
#define DELAY_5MS   (5 * (Fcy / 3 / 1000))
#define DELAY_10MS  (10 * (Fcy / 3 / 1000))

/** @brief microseconds */
#define DELAY_1US     (1 * (Fcy / 3 / 1000000))
#define DELAY_2US     (2 * (Fcy / 3 / 1000000))
#define DELAY_5US     (5 * (Fcy / 3 / 1000000))
#define DELAY_10US    (10 * (Fcy / 3 / 1000000))
#define DELAY_110US    (110 * (Fcy / 3 / 1000000))
#define DELAY_160US    (160 * (Fcy / 3 / 1000000))
#define DELAY_220US   (220 * (Fcy / 3 / 1000000))
#define DELAY_320US   (320 * (Fcy / 3 / 1000000))
#define DELAY_540US   (540 * (Fcy / 3 / 1000000))
#define DELAY_1780US  (1780 * (Fcy / 3 / 1000000))

//*******************************************************
// \brief Delay for specified time
// \param  ui32time : uint32_t
// \return int  : 1 : Success
//              : 0 : Error
//*******************************************************
int Delay(uint32_t ui32time);

//*******************************************************
// \brief Delay for specified milliseconds
// \param  ui32ms  : uint32_t
// \return int : 1 : Success
//             : 0 : Error
//*******************************************************
int Delay_Ms(uint32_t ui32ms);

//*******************************************************
// \brief Delay for specified microseconds
// \param  ui32us  : uint32_t
// \return int : 1 : Success
//             : 0 : Error
//*******************************************************
int Delay_Us(uint32_t ui32us);

#endif /* HEADER_DELAY_H_ */
