#ifndef __AVR_ATmega328P__ 
    #define __AVR_ATmega328P__
#endif
#define F_CPU 16000000UL

#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include"liberaries/USART_liberry/usart.c"


int main(void)
{
    DDRB = 0xff; 
    initUSART();
    while(1)
    {
        _delay_ms(100);
        transmitByte(8);
        printInt(627);
        _delay_ms(3000);
    }
    return (0);

}
