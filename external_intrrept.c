#ifndef __AVR_ATmega328P__ 
    #define __AVR_ATmega328P__
#endif
#define F_CPU 16000000UL

#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include"liberaries/USART_liberry/usart.h"

unsigned char str[75] = "good morning  angela mummy   ";
unsigned char str2[50] = "mummy i can arrange a light show for you mummy";


int main(void)
{
    DDRB = 0xff; 
    while(1)
    {
        _delay_ms(3000);
        serialbegin();
        for(int i = 0;i<=75;i++)
        {
        serialwritechar(str[i]);
        // serialwritechar(10);

        }
        serialwritechar(10); // ASCII 10 = /n = new line
        _delay_ms(2000);
        

        _delay_ms(100);
        (PORTB ^= 0xff);
        _delay_ms(100);
        (PORTB ^= 0xff);
       _delay_ms(100);
        (PORTB ^= 0xff);
       _delay_ms(100);
        (PORTB ^= 0xff);
       _delay_ms(100);
        (PORTB ^= 0xff);
       _delay_ms(400);
        (PORTB ^= 0xff);
       _delay_ms(100);
        (PORTB ^= 0xff);
       _delay_ms(200);
        (PORTB ^= 0xff);
       _delay_ms(100);
        (PORTB ^= 0xff);
        _delay_ms(100);
        (PORTB ^= 0xff);
        _delay_ms(100);
        (PORTB ^= 0xff);
       _delay_ms(100);
        (PORTB ^= 0xff);
       _delay_ms(100);
        (PORTB ^= 0xff);
       _delay_ms(100);
        (PORTB ^= 0xff);
       _delay_ms(400);
        (PORTB ^= 0xff);
       _delay_ms(100);
        (PORTB ^= 0xff);
       _delay_ms(200);
        (PORTB ^= 0xff);
       _delay_ms(100);
        (PORTB ^= 0xff);
        _delay_ms(100);
        (PORTB ^= 0xff);
        _delay_ms(100);
        (PORTB ^= 0xff);
       _delay_ms(100);
        (PORTB ^= 0xff);
       _delay_ms(100);
        (PORTB ^= 0xff);
       _delay_ms(100);
        (PORTB ^= 0xff);
       _delay_ms(400);
        (PORTB ^= 0xff);
       _delay_ms(100);
        (PORTB ^= 0xff);
       _delay_ms(200);
        (PORTB ^= 0xff);
       _delay_ms(1000);
        (PORTB ^= 0xff);


    }
    return (0);

}
