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
    
        if(bit_is_set(PIND,PD2))
        {
        transmitByte(12);
        printString("on");
        PORTB ^= 0xff;        
        _delay_ms(30);
        }
        else
        {
            transmitByte(12);
            printString("off");
        }
        



    }
    return (0);

}
