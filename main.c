
#include "stm32f030x6.h"

#include "uart.h"
#include "serial.h"
#include "timer.h"

// Setup hardware
void init(void)
{
    // Clock core at 48MHz using external crystal using the following steps:

    // HSI (High Speed Internal) 8MHz RC oscillator, can drive PLL
    // HSIRDY flag indicates HSI RC is stable.
    // HSI switched on/off by HSION in RCC_CR
    // AHB and APB max 48MHz
    // PLL configure before enable
    // PLLRDY
    // PLL output must be set in range 16-48MHz

    // *** HSI enabled by default, assume is already ready. ****

    // RCC_TypeDef
    // Clock configure
    // HSI 8Mhz / 2 = 4MHz -> PLL (x12) -> 48MHz
    RCC->CFGR = RCC_CFGR_PLLMUL12;      // PLLMUL[3:0] = 1010 = PLLinput clock x 12
                                        // PLLSRC[0] = 0 = PLL source HSI/2
                                        // PPRE[2:0] = 0 = PCLK prescaler (APB clock)
                                        // HPRE[7:4] = 0 = HCLK prescaler (AHB clock)
    RCC->CR |= RCC_CR_PLLON;            // PLLON[0] = 1 = Enable the PLL

    // Wait for the PLL to lock
    while(0 == (RCC->CR & RCC_CR_PLLRDY))
    {}

    // Switch to using the PLL now that it's ready
    RCC->CFGR |=    RCC_CFGR_SW_PLL;    // SW[1:0] = 10 = PLL used as system clock

    // ------ System clock now configured --------

    // Enable I/O port A.
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    // Enable USART1
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    // Enable timer 3 for 1mS tick
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
}

void init_io(void)
{
    // GPIO_TypeDef
    // PA4 (LED on dev board)
    // MODER4[1:0] = 01 = General purpose output
    GPIOA->MODER |= GPIO_MODER_MODER4_0;
    // Push-pull (by default)
    // GPIOA->OTYPER
    // Low speed (by default)
    // GPIOA->OSPEEDR
    // No Pullup/down (by default)
    // GPIOA->PUPDR

}

void loop(void)
{
    uint32_t i=0;
    while(1)
    {
        // Toggle LED
        __asm("nop\n");
        __asm("nop\n");
        GPIOA->BSRR |= GPIO_BSRR_BS_4;
        delay_ms(500);
        __asm("nop\n");
        __asm("nop\n");
        GPIOA->BSRR |= GPIO_BSRR_BR_4;
        delay_ms(500);
        print_strh32("Test:",i);
        i++;
    }
}

int main(void)
{
    init();
    init_io();
    uart_init();
    serial_init();
    timer_init();
    loop();
    return 0;
}

