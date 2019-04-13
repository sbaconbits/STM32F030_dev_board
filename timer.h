
#include "stm32f030x6.h"

void timer_init(void);

inline uint16_t timer_tick(void) { return TIM3->CNT; }

void delay_ms(uint16_t t);
