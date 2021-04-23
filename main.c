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
    
}

int main(void)          
{
    initUSART();
    while(1)
    {
    }
    return (0);

}
