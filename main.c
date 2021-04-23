#ifndef __AVR_ATmega328P__ 
    #define __AVR_ATmega328P__
#endif
#define F_CPU 16000000UL

#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include"liberaries/USART_liberry/usart.c"
void init_timer1()
{
    TCCR1B |= (1<<CS11) | (1<<CS10);
    // set the clock speed 1MHz / 64
}

int main(void)          
{
    initUSART();
    while(1)
    {
    }
    return (0);

}
