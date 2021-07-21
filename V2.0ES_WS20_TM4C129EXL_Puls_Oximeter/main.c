/*******************************************************************

              Group 5 Pulse Oximeter Main Code

********************************************************************
 FileName:        Main.c
 Description:     Pulse Oximeter Main Code
 Processor:       tm4c129exl
 Compiler:        TI v20.2.3.LTS
 Institution:     HTWG Konstanz
 Author:          Kevin Schultz, Sebastian Hofmaier, Andreas Roth

********************************************************************
 SOFTWARE COPYRIGHT NOTICE:

********************************************************************
 MEDICAL DEMO WARNINGS, RESTRICTIONS AND DISCLAIMER:

 This project is intended solely for evaluation and development purposes.
 It is not intended for medical diagnostic use.

********************************************************************
 Change History:

 Author             Rev   Date         Description
 K.S., S.M., A.R.   0.1   21.12.2020   Create Project
 K.S., S.M., A.R.   1.0   21.02.2020   Finish Version 1 of Project

********************************************************************
 Additional Note:

*******************************************************************/


//*****************************************************************************
// Include and Header files
//*****************************************************************************
#include <stdint.h>                                 // standard int input types
#include <stdbool.h>                                // standard bool types
#include "inc/hw_memmap.h"                          // for several predefined macros like "GPIO_PORTN_BASE"
#include "inc/hw_ints.h"                            // Macros that define the interrupt assignment on Tiva C Series MCUs (e.g. "INT_TIMER0A")
#include "driverlib/sysctl.h"                       // clock
#include "driverlib/interrupt.h"                    // hw interrupts
#include "driverlib/gpio.h"                         // for gpio access
#include "driverlib/pwm.h"                          // for pwm access
#include "driverlib/pin_map.h"                      // Mapping of peripherals to pins for all parts
#include "driverlib/rom.h"                          // Macros to facilitate calling functions in the ROM
#include "driverlib/rom_map.h"                      // when they are available and in flash otherwise
#include "booster_pack_display/CFAF128128B0145T.h"  // Boosterpack display lib
#include "header/ADC.h"                             // ADC modul with ADC0 and ADC1 for analog value sampling
#include "header/Beeper.h"                          // Beeper modul for puls sound from beeper of Boosterpack
#include "header/Delay.h"                           // Delay modul for specified delay periods
#include "header/I2C_MC4728.h"                      // DAC modul for I2C communication with DAC MCP4728
#include "header/Init.h"                            // Init modul for initialization of board peripheral hardware
#include "header/LCD.h"                             // LCD modul for displaying messages on the boosterpack LCD-Display
#include "header/PWM.h"                             // PWM modul with PWM0 and Gen. 0,1,2 for LED pulse generation
#include "header/UART.h"                            // UART modul
#include "header/Timer.h"                           // Timer modul with Timer0, Timer1 and Timer2 for main program functionality
#include "header/OMM_Modul.h"                       // OMM modul with state maschine for different operation modes
#include "header/Calculation.h"                     // Calculation modul for calculationg the values for puls and spo2
#include "header/Processing.h"                      // Processing modul for processing raw input data form the ADC measurements
#include "header/Safety_Modul.h"                    // Saftey modul with watchdog functionality
#include "header/Fifo.h"                     // Fifo modul for storage and processing of the values form ADC measurements

//*****************************************************************************
// The error routine that is called if the driver library encounters an error.
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

//*****************************************************************************
// Global Definitions
//*****************************************************************************
//#define TOGGLE_RATE_HZ      4       //-->Toggle Rate für den periodischen TimerX --> Zahl sthe für x mal pro Sekunde
#define Nop() asm volatile ("nop" ::)


//*****************************************************************************
// Global Variables
//*****************************************************************************
uint32_t g_ui32SysClock; // The variable g_ui32SysClock contains the system clock frequency in Hz.

// DAC
signed int Baseline_Upper_Limit, Baseline_Lower_Limit, Baseline_ambient;
unsigned int DAC_IRLed_intensity, DAC_RedLed_intensity;
signed int CH0_ADRES_IR, CH0_ADRES_Red;
unsigned char RedReady=0, IRReady=0;
unsigned char Meter_State=0;
uint8_t FirstByte, SecondByte_MultiWrite_A, ThirdByte_A, FourthByte_A, SecondByte_MultiWrite_B, ThirdByte_B, FourthByte_B;
//*****************************************************************************
// Local Function Prototypes
//*****************************************************************************


/****************************************************************************
*
* MAIN FUNCTION
*
*****************************************************************************/
int main(void)
{
    // Run from the PLL at 120 MHz.     (SW-TM4C-DRL-UG-....pdf)
    g_ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                         SYSCTL_OSC_MAIN |
                                         SYSCTL_USE_PLL |
                                         SYSCTL_CFG_VCO_480), 120000000);

    //********** Initialization **********
    Init();

    //********** Enable OC1 & OC2 ouputs for IR & Red LED's on/off switch **********
    // Timer0 starten
    //Deklaration des Timers 0
    //extern timer timer0;

    // Delay 540us zwischen start beider Timer
    //Delay(DELAY_540US);

    // Timer1 starten
    //Deklaration des Timers 1
    //extern timer timer1;
//    Timer_Init(timer1, (g_ui32SysClock/TOGGLE_RATE_HZ));    //initializes and enables the timer + Periodendauer (Wann soll Interrupt getriggert werden)

    //********** Main Loop **********
    while(true)
    {
        StateMachine(GetTimer(2), g_ui32SysClock);
    }

}
