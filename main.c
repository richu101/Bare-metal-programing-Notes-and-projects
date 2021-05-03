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
    TCCR0A |= (1<<WGM01);
    
    TCCR1B |= (1<<CS11) | (1<<CS10);
    // set the clock speed 16MHz / 64
    // 16/64 tick of the clock will increase the timer value by 1
}
void playnote(uint8_t pitch, uint8_t duratation)
{
    for(int8_t i = 0;i<=pitch;i++)
    {
        PORTB ^= (1<<5);
        for(int8_t i = 0;i<=duratation;i++)
            _delay_ms(1);
    }
}
int main(void)          
{   
    DDRB |= (1<<5);
    while(1)
    
    {   
        playnote(159,200);
        _delay_ms(100);
        playnote(59,210);
        _delay_ms(100);
        playnote(90,110);
        _delay_ms(100);
        playnote(54,169);

        
    }
        
        
    
    return (0);

}
