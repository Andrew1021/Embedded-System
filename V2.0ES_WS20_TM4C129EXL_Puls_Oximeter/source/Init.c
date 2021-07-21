/*
 * Init.c
 *
 *  Created on: 20.12.2020
 *      Author: Andreas Roth, Kevin Schultz, Sebastian Hofmaier
 */

#include <stdint.h>
#include <stdbool.h>

#include "driverlib/watchdog.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/timer.h"

#include "inc/hw_memmap.h"          // for several predefined macros like "GPIO_PORTN_BASE"
#include "inc/hw_ints.h"            // Macros that define the interrupt assignment on Tiva C Series MCUs (e.g. "INT_TIMER0A")
#include "driverlib/sysctl.h"       // clock
#include "driverlib/interrupt.h"
#include "../header/ADC.h"
#include "../header/I2C_MC4728.h"
#include "../header/Init.h"
#include "../header/LCD.h"
#include "../header/PWM.h"
#include "../header/Beeper.h"
#include "driverlib/gpio.h"         // for gpio access
#include "../header/Delay.h"
#include "../header/UART.h"


    // The system clock speed.
    extern uint32_t g_ui32SysClock;

int Init(void)
{
    //***************************
    // Initialize LCD Display
    //***************************
    LCD_Init(2, g_ui32SysClock, 20000000);

    //*********************************************************************************************************
    // Initialize GPIO
    //*********************************************************************************************************
    // Enable the GPIO port that is used for the on-board LED.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);

    // Enable the GPIO pin for the LED (PN0) as an output.
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);


    //*********************************************************************************************************
    // Watchdog
    //*********************************************************************************************************

        // Enable the Watchdog 0 peripheral
        SysCtlPeripheralEnable(SYSCTL_PERIPH_WDOG0);
        // Wait for the Watchdog 0 module to be ready.
        while(!SysCtlPeripheralReady(SYSCTL_PERIPH_WDOG0)){ }

        // Enable processor interrupts.
        //
        //ROM_IntMasterEnable();

        // Enable the watchdog interrupt.
        //
        ROM_IntEnable(INT_WATCHDOG);

        // Set the period of the watchdog timer to 5 seconds
        //
        ROM_WatchdogReloadSet(WATCHDOG0_BASE, g_ui32SysClock * 5);

        // Enable reset generation from the watchdog timer.
        //
        ROM_WatchdogResetEnable(WATCHDOG0_BASE);

        // Enable the watchdog timer.
        //
        ROM_WatchdogEnable(WATCHDOG0_BASE);


    //*********************************************************************************************************
    // Initialize Timer 0 - IR light
    //*********************************************************************************************************
    timer0.base = TIMER0_BASE;              //ID vom timer
    timer0.subtimer = TIMER_A;              //ID vom subtimer
    timer0.inttimer = INT_TIMER0A;          //ID vom Intterupt für Timer0A
    timer0.timeout = TIMER_TIMA_TIMEOUT;    //Flag welches gesetzt wird wenn Timer ausläuft (0)
    timer0.periphery = SYSCTL_PERIPH_TIMER0; //Zur Prüfung ob entsprechende Periphery vom uC freigeschalten wurde

    Timer_Init(timer0, (g_ui32SysClock/500));    //initializes and enables the timer + Periodendauer (Wann soll Interrupt getriggert werden)
    TimerInterrupt_Init(timer0, 0xE0);                     //initializes the interrupt for the respective timer

    // Delay 540us zwischen start beider Timer
    Delay(DELAY_540US);

    //*********************************************************************************************************
    // Initialize Timer 1 - Red light
    //*********************************************************************************************************
    timer1.base = TIMER1_BASE;              //ID vom timer
    timer1.subtimer = TIMER_A;              //ID vom subtimer
    timer1.inttimer = INT_TIMER1A;          //ID vom Intterupt für Timer1A
    timer1.timeout = TIMER_TIMA_TIMEOUT;    //Flag welches gesetzt wird wenn Timer ausläuft (0)
    timer1.periphery = SYSCTL_PERIPH_TIMER1; //Zur Prüfung ob entsprechende Periphery vom uC freigeschalten wurde

    Timer_Init(timer1, (g_ui32SysClock/500));    //initializes and enables the timer + Periodendauer (Wann soll Interrupt getriggert werden)
    TimerInterrupt_Init (timer1, 0xE0);                     //initializes the interrupt for the respective timer


    //*********************************************************************************************************
    // Initialize Timer 2 - OMM
    //*********************************************************************************************************
    timer2.base = TIMER2_BASE;              //ID vom timer
    timer2.subtimer = TIMER_A;              //ID vom subtimer
    timer2.inttimer = INT_TIMER2A;          //ID vom Intterupt für Timer1A
    timer2.timeout = TIMER_TIMA_TIMEOUT;    //Flag welches gesetzt wird wenn Timer ausläuft (0)
    timer2.periphery = SYSCTL_PERIPH_TIMER2; //Zur Prüfung ob entsprechende Periphery vom uC freigeschalten wurde


    //*********************************************************************************************************
    // Initialize PWM0 Gen. 0 module in Continuous Pulse mode, PWM0 Gen. 0 controls Red LED switch
    //*********************************************************************************************************
    // Select: PWMINT_ID_PWM0_GEN1, 500 Hz period, 4545.4545454545 Hz duty_cycle
    PWM_Init(PWM_ID_PWM0_GEN0, 5000, 4545);

    //*********************************************************************************************************
    // Initialize PWM0 Gen. 1 module in Continuous Pulse mode, PWM0 Gen. 1 controls IR LED switch
    //*********************************************************************************************************
    // Select: PWMINT_ID_PWM0_GEN0, 500 Hz period, 4545.4545454545 Hz duty_cycle
    PWM_Init(PWM_ID_PWM0_GEN1, 5000, 4545);


    //*********************************************************************************************************
    // Initialize Beeper module in booster pack with initialization of PWM0 Gen. 2 module for generation of tone
    //*********************************************************************************************************
    Beeper_Init();


    //*********************************************************************************
    // Initialize ADC for sampling values
    //*********************************************************************************
    // ADC0
    ADC_Init(ADC_ID_ADC0);
    ADC_Enable(ADC_ID_ADC0);

    // ADC0
    ADC_Init(ADC_ID_ADC1);
    ADC_Enable(ADC_ID_ADC1);


    //*********************************************************************************
    // Initialize I2C for communicating with external DAC
    //*********************************************************************************
    DAC_Init();

    //*****************************************************************************
    // Initialize MCP4728 DAC Output values
    //*****************************************************************************
    uint32_t DAC_IRLed_intensity = initial_DAC_IRLed_intensity;      // (DAC-A) DAC output voltage for controlling IR LED current, 2000=1.0V (@1.5V IR)
    uint32_t DAC_RedLed_intensity = initial_DAC_RedLed_intensity;    // (DAC-B) DAC output voltage for controlling Red LED current, 1500=0.75V (@1.5V Red)

    //Address Byte for MCP4728: 1100 000 0, DeviceCode=1100, AddressBits=000, R/nW=0(write)
    uint8_t FirstByte = 0xc0;

    uint8_t ThirdByte_A = 0x80 + (DAC_IRLed_intensity>>8 & 0x0f);
    uint8_t FourthByte_A = DAC_IRLed_intensity & 0x00ff;

    uint8_t ThirdByte_B = 0x80 + (DAC_RedLed_intensity>>8 & 0x0f);
    uint8_t FourthByte_B = DAC_RedLed_intensity & 0x00ff;

    uint8_t ThirdByte_C = 0x80 + (dc_offset>>8 & 0x0f);             // (DAC-C) DC offset value for the second stage amplier
    uint8_t FourthByte_C = dc_offset & 0x00ff;

    uint8_t ThirdByte_D = 0x40;                                     // (DAC-D) Channel D is disabled
    uint8_t FourthByte_D = 0x00;

    //Multi-Write Command for DAC Input Register of selected channel only, EEPROM not affected.
    uint8_t SecondByte_MultiWrite_A = 0b01000000;   //Channel A
    uint8_t SecondByte_MultiWrite_B = 0b01000010;   //Channel B
    uint8_t SecondByte_MultiWrite_C = 0b01000100;   //Channel C
    uint8_t SecondByte_MultiWrite_D = 0b01000110;   //Channel D

    DAC_Write(FirstByte, SecondByte_MultiWrite_A, ThirdByte_A, FourthByte_A);
    DAC_Write(FirstByte, SecondByte_MultiWrite_B, ThirdByte_B, FourthByte_B);
    DAC_Write(FirstByte, SecondByte_MultiWrite_C, ThirdByte_C, FourthByte_C);
    DAC_Write(FirstByte, SecondByte_MultiWrite_D, ThirdByte_D, FourthByte_D);


#ifdef UART  // Check if UART Modul is defined
    //*****************************************************************************************
    // Initialize UART1 module for outputing serial data or displaying waveform, 115200/8-N-1
    //*****************************************************************************************
    InitConsole();
#endif

    return (1); // Success
}
