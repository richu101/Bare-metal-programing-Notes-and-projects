/*

#  This part is to define the board that we are using 
#  You can see all  the board list that are availabele in the ave/io.h lib by 
#  peacking to the header just select the avr/io.h in the #include part and press F12
#  press ctrl + f and search for the board that u are looking for
#  If your board is available then u can see the board name unde __AVR_your-board__
#  Here am using Atmega328p SO   __AVR_ATmega328P__ 

*/  

#ifndef __AVR_ATmega328P__ 
    #define __AVR_ATmega328P__
#endif
#define F_CPU 16000000UL
#define threshold 12000
#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include<avr/power.h>
#include"USART_liberry/usart.c"
int status = 0;
int main(void)
{   
    DDRB = 0xff;
    DDRD = (0<<2);
    initUSART();
    while (1)
    {
    if(bit_is_clear(PIND,PIND2))
    {
        status = !status;
        PORTB = (status<<PB5);
    }
    
    if (status == 1)
    {
        printString("off");
    }
    else
    {
        printString("on");
    }
    while (bit_is_clear(PIND,PIND2));
    _delay_ms(500);
    }
    return (0);
}
