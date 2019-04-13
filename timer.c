
#include "stm32f030x6.h"

void timer_init(void)
{

    // TIM3 1mS tick

    // 48MHz / 48000 = 1000
    TIM3->PSC = 48000;
    TIM3->ARR = 0xffff;

    // Init and update generation
    TIM3->EGR |= TIM_EGR_UG;
    // Enable timer
    TIM3->CR1 |= TIM_CR1_CEN;
}


void delay_ms(uint16_t t)
{
    uint16_t start = TIM3->CNT;

    while( (TIM3->CNT - start) < t)
    {}
}
