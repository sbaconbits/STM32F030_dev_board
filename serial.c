
#include "stm32f030x6.h"

#include "uart.h"

void serial_init(void)
{
}


void print_putc(uint8_t c)
{
    uart_putc(c);
}

void print_hex_32(uint32_t d)
{
    uint8_t shift = 32;
    uint8_t c;

    do
    {
        shift -= 4;
        c = (d >> shift) & 0xf;
        if((c >= 0xa) && (c <= 0xf))
            print_putc('a'-0xa+c);
        else
            print_putc('0'+c);
    }while(shift);
}

void print_str(char* str)
{
    while(*str != '\0')
        print_putc(*(str++));
}

void print_strh32(char* str, uint32_t d)
{
    print_str(str);
    print_hex_32(d);
    print_str("\r\n");
}
