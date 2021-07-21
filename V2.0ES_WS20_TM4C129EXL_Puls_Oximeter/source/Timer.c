#include "../header/PWM.h"
#include "../header/Calculation.h"
#include "../header/Timer.h"
#include "../header/Init.h"
#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"          // for several predefined macros like "GPIO_PORTN_BASE"
#include "inc/hw_ints.h"            // Macros that define the interrupt assignment on Tiva C Series MCUs (e.g. "INT_TIMER0A")

#include "driverlib/sysctl.h"       // clock
#include "driverlib/gpio.h"         // for gpio access
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/pwm.h"          // for pwm access
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "../header/OMM_Modul.h"
#include "../header/I2C_MC4728.h"

//State for calibrated LEDs intensity
extern uint32_t Meter_State;

/** @brief Initialize the interrupt for passed timer
* @param  timer       : timer
* @param  priority    : priority of the passed timer
* @return  void
*/

void TimerInterrupt_Init (timer timer, uint8_t priority)
{
    IntMasterEnable();                                           // Enable the processor interrupts
	
	// Setup the interrupt for the timer timeouts.
    IntPrioritySet(timer.inttimer, priority);                    // set interrupt priority for timerXX (exp. 0A) to 7 (lowest priority) (only upper 3 bits are relevant!)
    IntEnable(timer.inttimer);                                   // enable timerXX (exp. 0A) interrupt
    TimerIntEnable(timer.base, timer.timeout);   		         // enable timer interrupt source: timeout of timerXX (exp. 0A)

}

/** @brief Initialize the passed timer
* @param  timer       : timer
* @param  period_duration    : period duration when the timer runs out of time
* @return  void
*/

void Timer_Init (timer timer, uint32_t period_duration)
{
	//Enable periphal of passed Timer
	SysCtlPeripheralEnable(timer.periphery);                     // enable Timer
	
	// Check if the peripheral access for Timer is enabled. (Wait for Timerx module to become ready)
	while(!SysCtlPeripheralReady(timer.periphery)){ }
	
	// Configure the 32-bit periodic timer.
    TimerConfigure(timer.base, TIMER_CFG_PERIODIC);              // set timer
    TimerLoadSet(timer.base, timer.subtimer, period_duration);   // set timers load value: Load value is frequency divided normally by a specific value --> Timer will be decremented until it is 0
	
	// Start the timer
    TimerEnable(timer.base, timer.subtimer);                     // enable passed timer (timer is not split)
}

/** @brief Passes the struct of needed timer
* @param  TimerID       : 0 : timer0
*                       : 1 : timer1
*                       : 2 : timer2
* @return  timer
*/

timer GetTimer(int TimerID)
{
    timer timerArray[3] = {timer0, timer1, timer2};              // available timers
    return timerArray[TimerID];
}

/** @brief The interrupt handler for the for timer0 interrupt
*/

void Timer0IntHandler(void)
{

    // Clear the timer interrupt.
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);              // clear timer interrupt source

	//Set PWM Signal 1 on
    PWM_Enable(PWM_ID_PWM0_GEN0);

    //Wait X (~110us?!)
    // Delay(DELAY_110US);

	//Trigger Verarbeitung RED_on
	//StartProcessing(Type = LEDon)

	//Wait X (~160us?!)
    // Delay(DELAY_160US);

    // Trigger Helligkeitsmessung
    // ADC0 CH0
	
	//Trigger Verarbeitung RED_off
    //StartProcessing(Type --> LED_off)

    // Acquires Red-DC baseline from Channel 0 (AN0)
    // Baseline_ambient = AC0 Value
    // Acquires Red-AC from Channel 1 (AN1)
    // CH0_ADRES_Red = AC1 Value

    // Adjust DAC values for led red current
    // Baseline_Upper_Limit = Baseline_ambient + DCVppHigh;
    // Baseline_Lower_Limit = Baseline_ambient + DCVppLow;

    // Adjust DAC values for led red current
    Meter_State = Calibrate_Red();

}

/** @brief The interrupt handler for the for timer1 interrupt
*/

void Timer1IntHandler(void)
{

    // Clear the timer interrupt.
    TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);                    // clear timer interrupt source

	//Set PWM Signal 2 on
    PWM_Enable(PWM_ID_PWM0_GEN1);

    //Wait X (~110us?!)
    // Delay(DELAY_110US);

	//Trigger Verarbeitung IR_on
    //StartProcessing(Type = IR_on)

    //Wait X (~110us?!)

    //Trigger Verarbeitung IR_off
    //StartProcessing(Type --> LED_off)

    // Acquires IR-DC baseline from Channel 0 (AN0)
    // Baseline_ambient = AC0 Value
    // Acquires IR-AC from Channel 1 (AN1)
    // CH0_ADRES_IR = AC1 Value

    // Adjust DAC values for led ir current
    // Baseline_Upper_Limit = Baseline_ambient + DCVppHigh;
    // Baseline_Lower_Limit = Baseline_ambient + DCVppLow;

    // Adjust DAC values for led ir current
    Meter_State = Calibrate_IR();
}

/** @brief The interrupt handler for the for timer2 interrupt
*/

void Timer2IntHandler(void)
{
    // Clear the timer interrupt.
    TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);                     // clear timer interrupt source

    //Setting the flag for OMM.c that the timer2 and it´s period of 5s run out of timer ---> in a new state can be switched
    TimeManagerOMM();

    // Disable the timers that it can be started one more time if needed for going into eco state
    TimerDisable(TIMER2_BASE, TIMER_A);                                 // disable timer2,A
    IntDisable(INT_TIMER2A);                                            // disable timer0A interrupt
    TimerIntDisable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);                   // disable timer interrupt source: timeout of timer2,A

    // Enable peripherals:
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);                       // enable Timer2
}
