/*
 * DAC_MCP4728.c
 *
 *  Created on: 12.01.2021
 *      Author: Andreas Roth, Kevin Schultz, Sebastian Hofmaier
 */
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "../header/I2C_MC4728.h"

// The system clock speed.
extern uint32_t g_ui32SysClock;

// DAC
extern signed int Baseline_Upper_Limit, Baseline_Lower_Limit, Baseline_ambient;
extern unsigned int DAC_IRLed_intensity, DAC_RedLed_intensity;
extern signed int CH0_ADRES_IR, CH0_ADRES_Red;
extern unsigned char RedReady, IRReady;
extern unsigned char Meter_State;
extern uint8_t FirstByte, SecondByte_MultiWrite_A, ThirdByte_A, FourthByte_A, SecondByte_MultiWrite_B, ThirdByte_B, FourthByte_B;

/** @brief Setup communication to DAC MCP4728 over I2C
* @return  1: Success
*          0: Error
*/
int DAC_Init(void)
{
    if(!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C0))
    {
        // The I2C0 peripheral must be enabled before use.
        SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);

        // Wait for the I2C0 module to be ready.
        while(!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C0)) {}

        // For I2C0 PortB[3:2] is used. GPIO port B needs to be enabled so these pins can
        // be used.
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

        // Wait for the GPIO Port B to be ready.
        while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)) {}

        // Configure the pin muxing for I2C0 functions on port B2 and B3.
        // This step is not necessary if your part does not support pin muxing.
        GPIOPinConfigure(GPIO_PB2_I2C0SCL);
        GPIOPinConfigure(GPIO_PB3_I2C0SDA);

        // Select the I2C function for these pins.  This function will also
        // configure the GPIO pins pins for I2C operation, setting them to
        // open-drain operation with weak pull-ups.  Consult the data sheet
        // to see which functions are allocated per pin.
        GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
        GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);

        // Enable loopback mode.  Loopback mode is a built in feature that is
        // useful for debugging I2C operations.  It internally connects the I2C
        // master and slave terminals, which effectively let's you send data as
        // a master and receive data as a slave.
        // NOTE: For external I2C operation you will need to use external pullups
        // that are stronger than the internal pullups.  Refer to the datasheet for
        // more information.
        // I2CLoopbackEnable(I2C0_BASE);

        // Enable and initialize the I2C0 master module.  Use the system clock for
        // the I2C0 module.  The last parameter sets the I2C data transfer rate.
        // If false the data rate is set to 100kbps and if true the data rate will
        // be set to 400kbps.  For this example we will use a data rate of 100kbps.
        I2CMasterInitExpClk(I2C0_BASE, g_ui32SysClock, false);

        // Enable the I2C0 master module.
        I2CMasterEnable(I2C0_BASE);

        // Set the slave address to SLAVE_ADDRESS.  In loopback mode, it's an
        // arbitrary 7-bit number (set in a macro above) that is sent to the
        // I2CMasterSlaveAddrSet function.
        //I2CSlaveInit(I2C0_BASE, SLAVE_ADDRESS);

        // Tell the master module what address it will place on the bus when
        // communicating with the slave.  Set the address to SLAVE_ADDRESS
        // (as set in the slave module).  The receive parameter is set to false
        // which indicates the I2C Master is initiating a writes to the slave.  If
        // true, that would indicate that the I2C Master is initiating reads from
        // the slave.
        I2CMasterSlaveAddrSet(I2C0_BASE, SLAVE_ADDRESS, false);

        return(1); // Success
    }
    else
    {
        return(0); // Error
    }
}

/** @brief Write data from the TM4C129EXL to the DAC MCP4728 over I2C
* @param  _1stByte    : uint8_t
* @param  _2stByte    : uint8_t
* @param  _3stByte    : uint8_t
* @param  _4stByte    : uint8_t
* @return  1: Success
*          0: Error
*/
int DAC_Write(uint8_t _1stByte, uint8_t _2ndByte, uint8_t _3rdByte, uint8_t _4thByte)
{
    //if((_1stByte && _2ndByte && _3rdByte && _4thByte) != false) !I2CMasterBusy(I2C0_BASE)
    if(true)
    {
        // I2C buffer
        uint8_t pui32DataTx[NUM_I2C_DATA];

        // Initialize the data to send.
        pui32DataTx[0] = _1stByte;
        pui32DataTx[1] = _2ndByte;
        pui32DataTx[2] = _3rdByte;
        pui32DataTx[3] = _4thByte;

        // uint32_t ui32Index = 0;
        // Send 4 pieces of I2C data from the master to the slave.
        //for(ui32Index = 0; ui32Index < NUM_I2C_DATA; ui32Index++)
        //{
            // 1. Byte
            // Place the data to be sent in the data register
            I2CMasterDataPut(I2C0_BASE, pui32DataTx[0]);

            // Initiate send of data from the master.
            // When the loopback mode is enabled, the master and slave units are connected
            // allowing us to receive the same data that we sent out.
            I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);

            // Wait until master module is done transferring.
            while(I2CMasterBusy(I2C0_BASE)) {}

            // 2. Byte
            // Place the data to be sent in the data register
            I2CMasterDataPut(I2C0_BASE, pui32DataTx[1]);

            // Initiate send of data from the master.
            // When the loopback mode is enabled, the master and slave units are connected
            // allowing us to receive the same data that we sent out.
            I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);

            // Wait until master module is done transferring.
            while(I2CMasterBusy(I2C0_BASE)) {}

            // 3. Byte
            // Place the data to be sent in the data register
            I2CMasterDataPut(I2C0_BASE, pui32DataTx[2]);

            // Initiate send of data from the master.
            // When the loopback mode is enabled, the master and slave units are connected
            // allowing us to receive the same data that we sent out.
            I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);

            // Wait until master module is done transferring.
            while(I2CMasterBusy(I2C0_BASE)) {}

            // 4. Byte
            // Place the data to be sent in the data register
            I2CMasterDataPut(I2C0_BASE, pui32DataTx[3]);

            // Initiate send of data from the master.
            // When the loopback mode is enabled, the master and slave units are connected
            // allowing us to receive the same data that we sent out.
            I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);

            //old
            // Place the data to be sent in the data register
            //I2CMasterDataPut(I2C0_BASE, pui32DataTx[ui32Index]);

            // Initiate send of data from the master.
            // When the loopback mode is enabled, the master and slave units are connected
            // allowing us to receive the same data that we sent out.
            //I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);

            // Wait until the slave has received and acknowledged the data.
            //while(!(I2C_SLAVE_ACT_RREQ))

            // Wait until master module is done transferring.
            while(I2CMasterBusy(I2C0_BASE)) {}

            if((I2CMasterErr(I2C0_BASE)) != 0)
            {
                uint32_t ErrorCode = I2CMasterErr(I2C0_BASE);
                I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_ERROR_STOP);
            }

            while(I2CMasterBusBusy(I2C0_BASE)) {}

        //}

        return (1);  // Success
    }
    else
    {
        return (0);  // Error
    }
}



/** @brief Calibrate IR LED intensity
* @return MeterState  : unsigned char
*/
unsigned char Calibrate_IR(void)
{
    unsigned char MeterState;

    MeterState = Meter_State;

    if (CH0_ADRES_IR > Baseline_Upper_Limit)
    {
        if (DAC_IRLed_intensity > 0)
        {
            DAC_IRLed_intensity--;
            ThirdByte_A = 0x80 + (DAC_IRLed_intensity>>8 & 0x0f);
            FourthByte_A = DAC_IRLed_intensity & 0x00ff;
            DAC_Write(FirstByte, SecondByte_MultiWrite_A, ThirdByte_A, FourthByte_A);
        }
        IRReady = 0;
    }
    else if (CH0_ADRES_IR < Baseline_Lower_Limit)
    {
        if (DAC_IRLed_intensity < 4095)
        {
            DAC_IRLed_intensity++;
            ThirdByte_A = 0x80 + (DAC_IRLed_intensity>>8 & 0x0f);
            FourthByte_A = DAC_IRLed_intensity & 0x00ff;
            DAC_Write(FirstByte, SecondByte_MultiWrite_A, ThirdByte_A, FourthByte_A);
        }
        IRReady = 0;
    }
    else
    {
        IRReady = 1;
    }

    return(MeterState);
}


/** @brief Calibrate Red LED intensity
* @return MeterState  : unsigned char
*/
unsigned char Calibrate_Red(void)
{
    unsigned char MeterState;

    MeterState = Meter_State;

    if (CH0_ADRES_Red > Baseline_Upper_Limit)
    {
        if (DAC_RedLed_intensity > 0)
        {
            DAC_RedLed_intensity--;
            ThirdByte_B = 0x80 + (DAC_RedLed_intensity>>8 & 0x0f);
            FourthByte_B = DAC_RedLed_intensity & 0x00ff;
            DAC_Write(FirstByte, SecondByte_MultiWrite_B, ThirdByte_B, FourthByte_B);
        }
        RedReady = 0;
    }
    else if (CH0_ADRES_Red < Baseline_Lower_Limit)
    {
        if (DAC_RedLed_intensity < 4095)
        {
            DAC_RedLed_intensity++;
            ThirdByte_B = 0x80 + (DAC_RedLed_intensity>>8 & 0x0f);
            FourthByte_B = DAC_RedLed_intensity & 0x00ff;
            DAC_Write(FirstByte, SecondByte_MultiWrite_B, ThirdByte_B, FourthByte_B);
        }
        RedReady = 0;
    }
    else
    {
        RedReady = 1;
    }

    return(MeterState);
}
