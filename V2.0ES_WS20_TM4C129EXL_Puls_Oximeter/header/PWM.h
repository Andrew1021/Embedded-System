/**
* \brief Library for periodic PWM interrupt usage
*
* \mainpage PWM
*
* \section intro_sec Introduction
* This library provides functions for periodic PWM interrupt usage
*
* \section license_sec License
* Property of Group 5.\n
* <a href="HTWG GitLab Embedded Systems Group 5">https://https://gitlab.ei.htwg-konstanz.de/es/ws2021/group5/-/tree/main</a>
*
* \section usage_sec Using the PWM library
* sample test code within the library (function PWM_Test())
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
*    // Setup periodic PWM interrupt
*    // Select: PWMINT_ID_PWM0_GEN0, 5000 Hz period, 4545 Hz duty_cycle
*    PWM_Init(PWMINT_ID_PWM0_GEN0, 500, 4545.4545454545);
*
*    // Enable processor interrupts.
*    IntMasterEnable();
*
*    // Start periodic PWM interrupt
*    // Select: PWMINT_ID_PWM0_GEN0 pwmID, 5000 Hz period, 4545 Hz duty_cycle
*    PWM_Enable(PWMINT_ID_PWM0_GEN0);
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
* 0.0.0.2  | Support for PWM0 Generator 2 added
* 0.0.0.3  | Retractor of function and variables names
*
* \section author_sec Author
* Andreas Roth, Kevin Schultz, Sebastian Hofmaier
*/

/**  @file PWM_Modul.h */
#ifndef HEADER_PWM_H_
#define HEADER_PWM_H_

/** @brief Available PWM-IDs    */
#define PWM_ID_PWM0_GEN0     0                  //!< PWM0_GEN0
#define PWM_ID_PWM0_GEN1     1                  //!< PWM0_GEN1
#define PWM_ID_PWM0_GEN2     2                  //!< PWM0_GEN2

/** @brief Highest available PWM-ID   */
#define PWMINT_ID_MAX           2

/** @brief PWM-specific ids/addresses  */
typedef struct {
    unsigned int        peripheral_id;          //!< peripheral_id, e.g. SYSCTL_PERIPH_PWM0
    unsigned int        base_id;                //!< base_id, e.g. PWM0_BASE
    unsigned int        interrupt_id;           //!< interrupt_id, e.g. PWM_INT_GEN_0
    unsigned int        pwm_gen_id;             //!< pwm_gen_id, e.g. PWM_GEN_0
    unsigned int        interupt_genfault_id;   //!< interupt_genfault_id, e.g. PWM_INT_GEN_0
    unsigned int        gpio_pf;                //!< gpio_pf, e.g. GPIO_PF1_M0PWM1
    unsigned int        gpio_pin;               //!< gpio_pin, e.g. GPIO_PIN_1
    unsigned int        pwm_out_bit;            //!< pwm_out_bit, e.g. PWM_OUT_1_BIT
    unsigned int        pwm_out;                //!< pwm_out, e.g. PWM_OUT_0
    } pwm_t;

/** @brief Setup pwm for periodic interrupt
* @param  pwm_id      : 0 : PWM0_GEN0
*                     : 1 : PWM0_GEN1
*                     : 2 : PWM0_GEN2
* @param  period          : pwm period [Hz]
* @param  duty_cycle      : duty cycle periode [Hz]
* @return  1: Success
*          0: Error
*/
int PWM_Init(unsigned char pwm_id, unsigned int period, unsigned int duty_cycle);

/** @brief Enable periodic pwm interrupt
* @param  pwm_id      : 0 : PWM0_GEN0
*                     : 1 : PWM0_GEN1
*                     : 2 : PWM0_GEN2
* @return  1: Success
*          0: Error
*/
int PWM_Enable(unsigned char pwm_id);

/** @brief Disable periodic pwm interrupt
* @param  pwm_id      : 0 : PWM0_GEN0
*                     : 1 : PWM0_GEN1
*                     : 2 : PWM0_GEN2
* @return  1: Success
*          0: Error
*/
int PWM_Disable(unsigned char pwm_id);

/** @brief Stop pwm and free resources connected to periodic pwm interrupt
* @param  pwm_id      : 0 : PWM0_GEN0
*                     : 1 : PWM0_GEN1
*                     : 2 : PWM0_GEN2
* @return  1: Success
*          0: Error
*/
int PWM_Close(unsigned char pwm_id);

/** @brief The interrupt handler for the for PWM0 Gen. 0 interrupt
*/
void PWM0Gen0IntHandler(void);

/** @brief The interrupt handler for the for PWM0 Gen. 1 interrupt
*/
void PWM0Gen1IntHandler(void);

/** @brief The interrupt handler for the for PWM0 Gen. 2 interrupt
*/
void PWM0Gen2IntHandler(void);

/** @brief PWM test function
* @param  pwm_id      : 0 : PWM0_GEN0
*                     : 1 : PWM0_GEN1
*                     : 2 : PWM0_GEN2
* @return  1: Success
*          0: Error
*/
int PWM_Test(unsigned char pwm_id);

#endif /* HEADER_PWM_H_ */
