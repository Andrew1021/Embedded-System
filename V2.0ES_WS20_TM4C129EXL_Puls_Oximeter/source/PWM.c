/*
 * PWM.c
 *
 *  Created on: 20.12.2020
 *      Author: Andreas Roth, Kevin Schultz, Sebastian Hofmaier
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"          // for several predefined macros like "GPIO_PORTN_BASE"
#include "inc/hw_ints.h"            // Macros that define the interrupt assignment on Tiva C Series MCUs (e.g. "INT_TIMER0A")
#include "driverlib/sysctl.h"       // clock
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"         // for gpio access
#include "driverlib/pwm.h"          // for pwm access
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "../header/PWM.h"
#include "../header/OMM_Modul.h"

// The system clock speed.
extern uint32_t g_ui32SysClock;
// The system state variable.
extern uint8_t state;

static const pwm_t pwmInfo[PWMINT_ID_MAX + 1] =
        {
             {SYSCTL_PERIPH_PWM0, PWM0_BASE, INT_PWM0_0, PWM_GEN_0, PWM_INT_GEN_0, GPIO_PF1_M0PWM1, GPIO_PIN_1, PWM_OUT_1_BIT, PWM_OUT_0},  // PWM0_GEN0
             {SYSCTL_PERIPH_PWM0, PWM0_BASE, INT_PWM0_1, PWM_GEN_1, PWM_INT_GEN_1, GPIO_PF2_M0PWM2, GPIO_PIN_2, PWM_OUT_2_BIT, PWM_OUT_1},  // PWM0_GEN1
             {SYSCTL_PERIPH_PWM0, PWM0_BASE, INT_PWM0_2, PWM_GEN_2, PWM_INT_GEN_2, GPIO_PG1_M0PWM5, GPIO_PIN_3, PWM_OUT_3_BIT, PWM_OUT_2},  // PWM0_GEN2
        };



/** @brief Setup pwm for periodic interrupt
* @param  pwmID       : 0 : PWM0_GEN0
*                     : 1 : PWM0_GEN1
* @param  period          : pwm period [Hz]
* @param  duty_cycle      : duty cycle periode [Hz]
* @return  1: Success
*          0: Error
*/
int PWM_Init(uint8_t pwmID, uint32_t period, uint32_t duty_cycle)
{
    if(pwmID <= PWMINT_ID_MAX)
    {
        // Enable PWM peripherals:
        // The PWM peripheral must be enabled for use.
        SysCtlPeripheralEnable(pwmInfo[pwmID].peripheral_id);

        // Enable the GPIO port that is used for the PWM output.
        if (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF) && !SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOG))
        {
            SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
            SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
        }

        // Check if the peripheral access is enabled. (Wait for PWMx module to become ready)
        while(!(SysCtlPeripheralReady(pwmInfo[pwmID].peripheral_id) && SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF) && SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOG))){}

        // Configure the GPIO pad for PWM function on pins PF1 and PF2.
        GPIOPinConfigure(pwmInfo[pwmID].gpio_pf);
        GPIOPinTypePWM(GPIO_PORTF_BASE, pwmInfo[pwmID].gpio_pin);


        // Set the PWM clock
        // Set the PWM clock to be SysClk / 8.
        PWMClockSet(pwmInfo[pwmID].base_id, PWM_SYSCLK_DIV_8);

        // Use a local variable to store the PWM clock rate which will be
        // 120 MHz / 8 = 15 MHz. This variable will be used to set the
        // PWM generator period.
        uint32_t ui32PWMClockRate = g_ui32SysClock / 8;


        // Configure the 32-bit periodic PWM generators
        // Configure PWM0 to count down without synchronization.
        PWMGenConfigure(pwmInfo[pwmID].base_id, pwmInfo[pwmID].pwm_gen_id,
                            PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

        // Set the PWM0 period to 500Hz. To calculate the appropriate parameter
        // use the following equation: N = (1 / f) * PWMClk.  Where N is the
        // function parameter, f is the desired frequency, and PWMClk is the
        // PWM clock frequency based on the system clock.
        PWMGenPeriodSet(pwmInfo[pwmID].base_id, pwmInfo[pwmID].pwm_gen_id, (ui32PWMClockRate / period)); // for Standard 2000us => 500 Hz
        // Set PWM0 to a duty cycle of 11%.  You set the duty cycle as a function
        // of the period.  Since the period was set above, you can use the
        // PWMGenPeriodGet() function.  For this example the PWM will be high for
        // 220us of the time off PWM Period.
        PWMPulseWidthSet(pwmInfo[pwmID].base_id, pwmInfo[pwmID].pwm_out, (ui32PWMClockRate / duty_cycle)); // for Standard 220us => 4545.4545454545 Hz


        // Configure and enable PWM interrupts
        // PWM0_GEN0
        //IntPrioritySet(PWM_INT_GEN_0, priority);  // set interrupt priority for PWM0_GEN0
        // Allow PWM0 generated interrupts.  This configuration is done to
        // differentiate fault interrupts from other PWM0 related interrupts.
        PWMIntEnable(pwmInfo[pwmID].base_id, pwmInfo[pwmID].interupt_genfault_id);

        // Enable the PWM0 LOAD interrupt on PWM Gen 0.
        PWMGenIntTrigEnable(pwmInfo[pwmID].base_id,  pwmInfo[pwmID].pwm_gen_id, PWM_INT_CNT_LOAD);

        // Enable the interrupt for PWM Gen 0 on the processor (NVIC).
        IntEnable(pwmInfo[pwmID].interrupt_id);

        return(1);  // success
    }
    else
    {
        return(0);  // Error
    }
}

/** @brief Enable periodic pwm interrupt
* @param  pwmID       : 0 : PWM0_GEN0
*                     : 1 : PWM0_GEN1
* @return  1: Success
*          0: Error
*/
int PWM_Enable(uint8_t pwmID)
{

    if(pwmID <= PWMINT_ID_MAX)
    {
        //Set PWM Signal 0 on
        // Enable the PWM Out Bit 1 (PF1) output signal.
        PWMOutputState(pwmInfo[pwmID].base_id, pwmInfo[pwmID].pwm_out_bit, true);
        // Enable the PWM generator block.
        PWMGenEnable(pwmInfo[pwmID].base_id, pwmInfo[pwmID].pwm_gen_id);

        return(1);  // success
    }
    else
    {
        return(0);  // Error
    }
}

/** @brief Disable periodic pwm interrupt
* @param  pwmID       : 0 : PWM0_GEN0
*                     : 1 : PWM0_GEN1
* @return  1: Success
*          0: Error
*/
int PWM_Disable(uint8_t pwmID)
{

    if(pwmID <= PWMINT_ID_MAX)
    {
        // disable PWM0_GEN0
        // Disable the PWM Out Bit 1 (PF1) output signal.
        PWMOutputState(pwmInfo[pwmID].base_id, pwmInfo[pwmID].pwm_out_bit, false);
        PWMGenDisable(pwmInfo[pwmID].base_id, pwmInfo[pwmID].pwm_gen_id);

        return(1);  // success
    }
    else
    {
        return(0);  // Error
    }
}


/** @brief Stop pwm and free resources connected to periodic pwm interrupt
* @param  pwmID       : 0 : PWM0_GEN0
*                     : 1 : PWM0_GEN1
* @return  1: Success
*          0: Error
*/
int PWM_Close(uint8_t pwmID)
{

    if(pwmID <= PWMINT_ID_MAX)
    {
        PWM_Disable(pwmID);

        // Disable Interrupts PWM0_GEN0
        IntDisable(pwmInfo[pwmID].interrupt_id);
        PWMGenIntTrigDisable(pwmInfo[pwmID].base_id, pwmInfo[pwmID].pwm_gen_id, PWM_INT_CNT_LOAD);
        PWMIntDisable(pwmInfo[pwmID].base_id, pwmInfo[pwmID].interupt_genfault_id);

        // enable peripheral again:
        // The PWM peripheral must be enabled for use.
        SysCtlPeripheralEnable(pwmInfo[pwmID].peripheral_id);
        // Enable the GPIO port that is used for the PWM output.
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);

        // Check if the peripheral access is enabled. (Wait for PWMx module to become ready)
        while(!(SysCtlPeripheralReady(pwmInfo[pwmID].peripheral_id) && SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF) && SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOG))) {}

        return(1);  // success
    }
    else
    {
        return(0);  // Error
    }
}



/** @brief The interrupt handler for the for PWM0 Gen. 0 interrupt
*/
void PWM0Gen0IntHandler(void)
    {

        // Clear the PWM0 LOAD interrupt flag.  This flag gets set when the PWM
        // counter gets reloaded.
        PWMGenIntClear(PWM0_BASE, PWM_GEN_0, PWM_INT_CNT_LOAD);

        // disable PWM0
        // Disable the PWM Out Bit 1 (PF1) output signal.
        PWM_Disable(PWM_ID_PWM0_GEN0);


        // change PWM0 period if go into sleep state
//        if(state == state_eco)
//        {
//            PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, (g_ui32SysClock / 0.098039215686275)); // 10s + 2000us
//        }

    }


/** @brief The interrupt handler for the for PWM0 Gen. 1 interrupt
*/
void PWM0Gen1IntHandler(void)
    {
        // Clear the PWM0 LOAD interrupt flag.  This flag gets set when the PWM
        // counter gets reloaded.
        PWMGenIntClear(PWM0_BASE, PWM_GEN_1, PWM_INT_CNT_LOAD);

        // disable PWM0
        // Disable the PWM Out Bit 2 (PF2) output signals.
        PWM_Disable(PWM_ID_PWM0_GEN1);


        // change PWM0 period if go into sleep state
//        if(state == state_eco)
//        {
//            PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, (g_ui32SysClock / 0.098039215686275)); // 10s + 2000us
//        }

    }


/** @brief The interrupt handler for the for PWM0 Gen. 2 interrupt
*/
void PWM0Gen2IntHandler(void)
    {
        // Clear the PWM0 LOAD interrupt flag.  This flag gets set when the PWM
        // counter gets reloaded.
        PWMGenIntClear(PWM0_BASE, PWM_GEN_2, PWM_INT_CNT_LOAD);

        // disable PWM0
        // Disable the PWM Out Bit 2 (PF2) output signals.
        PWM_Disable(PWM_ID_PWM0_GEN2);


        // change PWM0 period if go into sleep state
//        if(state == state_eco)
//        {
//            PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, (g_ui32SysClock / 0.098039215686275)); // 10s + 2000us
//        }

    }


/** @brief PWM_Modul test function - to be defined
* @param  pwmID       : 0 : PWM0_GEN0
*                     : 1 : PWM0_GEN1
* @return  1: Success
*          0: Error
*/
int PWM_Test(uint8_t pwmID)
{
    if(pwmID <= PWMINT_ID_MAX)
    {
        // Setup periodic PWM interrupt
        // Select: PWMINT_ID_PWM0_GEN0, 5000 Hz period, 4545 Hz duty_cycle
        uint8_t status_init = PWM_Init(pwmID, 5000, 4545);

        // Enable processor interrupts.
        IntMasterEnable();

        // Start periodic PWM
        // Select: PWMINT_ID_PWM0_GEN0 pwmID, 5000 Hz period, 4545 Hz duty_cycle
        uint8_t status_enable = PWM_Enable(pwmID);

        // Close periodic PWM
        uint8_t status_close = PWM_Close(pwmID);

        return(1);  // success
    }
    else
    {
        return(0);  // Error
    }
}

