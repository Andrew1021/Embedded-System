

#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

// Values for offset and initial of dac
#define DCVppHigh          200     // 2000, 200
#define DCVppLow           100     // 1800, 100


/** @brief Timer-specific IDs and values for configuration  */
typedef struct{
    uint32_t base;      //ID vom timer
    uint32_t subtimer;  //ID vom subtimer
    uint32_t inttimer;  //ID vom Intterupt für Timer0A
    uint32_t timeout;   //Flag welches gesetzt wird wenn Timer auslÃ¤uft (0,1,2,3,....)
    uint32_t periphery; //Zur Prüfung ob entsprechende Periphery vom uC freigeschalten wurde
} timer;

/** @brief Initialize the passed timer
* @param  timer       : timer
* @param  period_duration    : period duration when the timer runs out of time
* @return  void
*/

void Timer_Init (timer timer, uint32_t period_duration);


/** @brief Initialize the interrupt for passed timer
* @param  timer       : timer
* @param  priority    : priority of the passed timer
* @return  void
*/
void TimerInterrupt_Init (timer timer, uint8_t priority);

/** @brief Passes the struct of needed timer
* @param  TimerID       : 0 : timer0
*                       : 1 : timer1
*                       : 2 : timer2
* @return  timer
*/

timer GetTimer(int TimerID);

/** @brief The interrupt handler for the for timer0 interrupt
*/

void Timer0IntHandler(void);

/** @brief The interrupt handler for the for timer1 interrupt
*/

void Timer1IntHandler(void);

/** @brief The interrupt handler for the for timer2 interrupt
*/

void Timer2IntHandler(void);

#endif /* TIMER_H_ */
