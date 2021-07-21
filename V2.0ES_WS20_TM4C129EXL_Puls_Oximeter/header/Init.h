/*
 * Init.h
*
*  Created on: 20.12.2020
*      Author: Andreas Roth, Kevin Schultz, Sebastian Hofmaier
*/

#include "../header/Timer.h"
#include "../header/FIFO.h"

#ifndef HEADER_INIT_H_
#define HEADER_INIT_H_

/** @brief Toggle rate for periodical Timer */
#define TOGGLE_RATE_HZ      500

/** @brief Values for offset and initial of dac */
#define dc_offset          440     // 2.048V/4096*400=0.2V, 440=0.22V, 500=0.25V
#define initial_DAC_IRLed_intensity 1700
#define initial_DAC_RedLed_intensity  1700


//Declaration Timers 0
timer timer0;                           // timer0 with struct from von timer (look header Timer.h)
//Declaration Timers 1
timer timer1;                           // timer1 with struct from von timer (look header Timer.h)
//Declaration Timers 2
timer timer2;                           // timer2 with struct from von timer (look header Timer.h)

//*******************************************************
// \brief Buffers for measurements of the LEDS
//*******************************************************
fifo_t buffer_led_red_AC;
fifo_t buffer_led_red_DC;
fifo_t buffer_led_ir_AC;
fifo_t buffer_led_ir_DC;
fifo_t buffer_led_off_AC;
fifo_t buffer_led_off_DC;

/** @brief Initialize the peripheral hardware modules
* @param  void
* @return int : 1 : Success
*             : 0 : Error
*/
int Init(void);

#endif /* HEADER_INIT_H_ */
