
#include "stm32f030x6.h"

void uart_init(void)
{
    // Configure GPIO
    // PA10 USART1 RX (AF1 Alternate Function 1)
    // PA9 USART1 TX (AF1 Alternate Function 1)
    GPIOA->AFR[1] |= (1 << GPIO_AFRH_AFSEL9_Pos);
    GPIOA->AFR[1] |= (1 << GPIO_AFRH_AFSEL10_Pos);

    // MODER9[1:0] = 10 = Alternate function mode
    GPIOA->MODER |= GPIO_MODER_MODER9_1;
    GPIOA->MODER |= GPIO_MODER_MODER10_1;

    // Baude rate
    // 48e6 / 115200 = 416.666 = 0x1a1
    USART1->BRR = 0x1a1;

    // Configure USART
    // OVER8 = 0 = oversampleing by 16
    USART1->CR1 |=  (USART_CR1_TE |     // Tx Enable
                     USART_CR1_RE |     // Rx Enable
                     USART_CR1_UE );    // USART Enable
}

void uart_putc(uint8_t c)
{
    // Wait for data to be transferred to shift register.
    while(0 == (USART1->ISR & USART_ISR_TXE))
    {}
    USART1->TDR = c;
}
