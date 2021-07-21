/**
* \brief Library for ADC trigger usage
*
* \mainpage ADC
*
* \section intro_sec Introduction
* This library provides functions for ADC trigger usage
*
* \section license_sec License
* Property of Group 5.\n
* <a href="HTWG GitLab Embedded Systems Group 5">https://https://gitlab.ei.htwg-konstanz.de/es/ws2021/group5/-/tree/main</a>
*
* \section usage_sec Using the ADC library
* sample test code within the libray (function ADC_Test())
*
*
*
* Example code for the use of ADC trigger conversion
* \code{.c}
*
*
* void main(void)
* {
*
*    // Setup ADC functionality for ADC0
*    // Select: ADC_ID_ADC0 for ADC0 on Port E 3
*    ADC_Init(ADC_ID_ADC0);
*
*    // Enable processor interrupts.
*    IntMasterEnable();
*
*    // Enable ADC Sequence for single sample
*    // Select: ADC_ID_ADC0 for ADC0 on Port E 3
*    ADC_Enable(ADC_ID_ADC0);
*
*    // Trigger ADC conversion for single sample
*    // Select: ADC_ID_ADC0 for ADC0 on Port E 3
*    uint32_t sample = ADC_Trigger(ADC_ID_ADC0)
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

/**  @file ADC_Modul.h */
#ifndef HEADER_ADC_H_
#define HEADER_ADC_H_

/** @brief Available ADC-IDs    */
#define ADC_ID_ADC0     0       //!< ADC0
#define ADC_ID_ADC1     1       //!< ADC1

/** @brief Highest available ADC-ID   */
#define ADC_ID_MAX           1

/** @brief adc-specific ids/addresses  */
typedef struct {
    unsigned int        peripheral_id;         //!< peripheral ID, e.g. SYSCTL_PERIPH_ADC0
    unsigned int        base_id;               //!< base ID, e.g. ADC0_BASE
    unsigned int        interrupt_id;          //!< interrupt ID, e.g.
    unsigned int        adc_ch_id;             //!< adcChID, e.g. ADC_CTL_CH0
    unsigned int        adc_interupt_flag;     //!< adcInteruptFlag, e.g. ADC_CTL_IE
    unsigned int        last_conversion_flag;  //!< lastConversionFlag, e.g. ADC_CTL_END
    unsigned int        gpio_pin;              //!< gpioPin, e.g. GPIO_PIN_2
    unsigned int        sequence;              //!< sequence, e.g. 3
    unsigned int        adc_trigger;           //!< adcTrigger, e.g. ADC_TRIGGER_PROCESSOR
} adc_t;

/** @brief Setup ADC trigger conversion
* @param  adc_id       : 0 : ADC0
*                      : 1 : ADC1
* @return  1: Success
*          0: Error
*/
int ADC_Init(unsigned char adc_id);

/** @brief Enable ADC trigger conversion
* @param  adc_id       : 0 : PWM0_GEN0
*                      : 1 : PWM0_GEN1
* @return  1: Success
*          0: Error
*/
int ADC_Enable(unsigned char adc_id);

/** @brief Trigger ADC conversion
* @param  adc_id       : 0 : ADC0
*                      : 1 : ADC1
* @return  1: Success
*          0: Error
*/
unsigned int ADC_Trigger(unsigned char adc_id);

/** @brief Enable ADC trigger conversion
* @param  adc_id       : 0 : ADC0
*                      : 1 : ADC1
* @return  1: Success
*          0: Error
*/
int ADC_Disable(unsigned char adc_id);

/** @brief Stop adc and free resources connected to ADC trigger conversion
* @param  adc_id       : 0 : ADC0
*                      : 1 : ADC1
* @return  1: Success
*          0: Error
*/
int ADC_Close(unsigned char adc_id);

/** @brief The interrupt handler for the for ADC0
*/
void ADC0IntHandler(void);

/** @brief The interrupt handler for the for ADC1
*/
void ADC1IntHandler(void);

/** @brief ADC_Modul test function
* @param  adc_id       : 0 : ADC0
*                      : 1 : ADC1
* @return  1: Success
*          0: Error
*/
int ADC_Test(unsigned char adc_id);


#endif /* HEADER_ADC_H_ */
