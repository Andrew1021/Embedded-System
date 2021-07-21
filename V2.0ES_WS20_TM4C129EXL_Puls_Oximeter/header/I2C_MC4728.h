/**
* \brief Library for DAC MCP4728 communication via I2C
*
* \mainpage I2C_MC4728
*
* \section intro_sec Introduction
* This library provides functions for DAC MCP4728 communication via I2C
*
* \section license_sec License
* Property of Group 5.\n
* <a href="HTWG GitLab Embedded Systems Group 5">https://https://gitlab.ei.htwg-konstanz.de/es/ws2021/group5/-/tree/main</a>
*
* \section usage_sec Using the I2C_Modul library
* sample test code within the library (function DAC_test())
*
*
*
* Example code for the use of periodic interrupts
* \code{.c}
*
*
* void main(void)
* {
*
*    // Setup I2C bus communication between TM4C129EXL (master) and DAC MCP4728 (slave)
*    DAC_Init(void);
*
*    // Write data to DAC MCP4728 (slave)
*    DAC_write(uint8_t _1stByte, uint8_t _2ndByte, uint8_t _3rdByte, uint8_t _4thByte)
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

#ifndef HEADER_I2C_MC4728_H_
#define HEADER_I2C_MC4728_H_

//*****************************************************************************
// Number of I2C data packets to send.
//*****************************************************************************
#define NUM_I2C_DATA 4

//*****************************************************************************
// Set the address for slave module. This is a 7-bit address sent in the
// following format:
//                      [A6:A5:A4:A3:A2:A1:A0:RS]
// A zero in the "RS" position of the first byte means that the master
// transmits (sends) data to the selected slave, and a one in this position
// means that the master receives data from the slave.
//*****************************************************************************
#define SLAVE_ADDRESS 0xc0 // Address Byte for MCP4728: 1100 000 0, DeviceCode = 1100, AddressBits = 000, R/nW=0(write)

/** @brief Setup communication to DAC MCP4728 over I2C
* @return  1: Success
*          0: Error
*/
int DAC_Init(void);

/** @brief Write data from the TM4C129EXL to the DAC MCP4728 over I2C
* @param  _1stByte    : uint8_t
* @param  _2ndByte    : uint8_t
* @param  _3rdByte    : uint8_t
* @param  _4thByte    : uint8_t
* @return  1: Success
*          0: Error
*/
int DAC_Write(uint8_t _1stByte, uint8_t _2ndByte, uint8_t _3rdByte, uint8_t _4thByte);

/** @brief Calibrate IR LED intensity
* @return MeterState  : unsigned char
*/
unsigned char Calibrate_IR(void);

/** @brief Calibrate Red LED intensity
* @return MeterState  : unsigned char
*/
unsigned char Calibrate_Red(void);

#endif /* HEADER_I2C_MC4728_H_ */
