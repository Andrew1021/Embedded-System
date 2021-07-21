/*
 * Calculation.c
 *
 * For calculation of pulse and spO2
 *
 *  Created on: 20.12.2020
 *      Author: Andreas Roth, Kevin Schultz, Sebastian Hofmaier
 */
#include <header/LCD.h>
#include "../header/Calculation.h"
#include "../header/Init.h"
#include "../header/LUT.h"

// wave length 660nm RED
static const float EXTINCT_COEFF_R_Hb       = 3226.56;
static const float EXTINCT_COEFF_R_HbO2     = 319.6;
// wave length 940nm IR
static const float EXTINCT_COEFF_IR_Hb      = 693.44;
static const float EXTINCT_COEFF_IR_HbO2    = 1214.0;

extern uint32_t g_ui32SysClock;

//*******************************************************
// \brief Gets max value of the AC and DC voltage
// \param    fifo_AC: fifo_t*, fifo_DC: fifo_t*,
// \return   measured_voltages : voltage_t
//*******************************************************
static voltage_t Get_AC_DC_Values(fifo_t* fifo_AC, fifo_t* fifo_DC)
{
    // convert to float, because of calculation later on
    voltage_t measured_voltages = { Fifo_Read(fifo_AC), Fifo_Read(fifo_DC)};
    return measured_voltages;
}

//*******************************************************
// \brief Calculates the spO2 ratio
// \param    measuredVal: uint16_t
// \return   spO2 : float
//*******************************************************
static float SpO2_Ratio_Calculation()
{
    float ratio = 0.00;
    uint16_t i = 0; // counter variable for average

    while(Fifo_Get_Level(&buffer_led_red_AC) || Fifo_Get_Level(&buffer_led_red_DC) ||Fifo_Get_Level(&buffer_led_ir_AC) ||Fifo_Get_Level(&buffer_led_ir_DC))
    {
        voltage_t red_led = Get_AC_DC_Values(&buffer_led_red_AC, &buffer_led_red_DC);
        voltage_t ir_led  = Get_AC_DC_Values(&buffer_led_ir_AC, &buffer_led_ir_DC);

        float ac_dc_ratio = (red_led.ac * ir_led.dc) / (red_led.dc * ir_led.ac);
        ratio = (EXTINCT_COEFF_R_Hb - EXTINCT_COEFF_IR_Hb * ac_dc_ratio) / ((EXTINCT_COEFF_R_Hb - EXTINCT_COEFF_R_HbO2) - (EXTINCT_COEFF_IR_Hb - EXTINCT_COEFF_IR_HbO2) * ac_dc_ratio);

        i++;
    }


    ratio =  ratio / ((float)i); // calculating average

    return ratio;
}

//*******************************************************
// \brief Calculates Pulse in bpm
// \param    time_steps_pulse: uint32_t
// \return   pulse : bool
//*******************************************************
static uint32_t Pulse_Calculation(uint32_t time_steps_pulse)
{
    // get timer interrupt frequency
    uint32_t timer_freq = g_ui32SysClock / TOGGLE_RATE_HZ;
    // get timer period
    float timer_period = 1.0/((float)timer_freq);
    // get pulse period out of timer period
    float pulse_period = timer_period * (float)time_steps_pulse;
    // get pulse frequency in beats per minute
    uint32_t pulse = (1.0/pulse_period) * 1000000; // from 1/µs to 1/min

    return pulse;
}

//*******************************************************
// \brief Starts the calculation of pulse and spO2
// \param    time_steps_pulse: uint32_t
// \return   void
//*******************************************************
void Start_Calculation(uint32_t time_steps_pulse)
{
    uint16_t spO2 = LUT_SpO2(SpO2_Ratio_Calculation());
    uint32_t pulse = Pulse_Calculation(time_steps_pulse);
    LCD_Active(pulse, spO2);
}
