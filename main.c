#ifndef __AVR_ATmega328P__ 
    #define __AVR_ATmega328P__
#endif
#define F_CPU 16000000UL

#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include"liberaries/USART_liberry/usart.c"
static inline void init_timer1()
{   
    // TCCR1A |= (1<<WGM12);
    // enable the counter to work in ctc(clear timer on compare) mode
    TCCR1A |= (1<<COM1A0)  ;
    // toggle OC0A on compare match
    TCCR1B |= (1<<CS10)| (1<<CS11) | (1<<WGM12);
    // set the clock speed 16MHz / 64
    // 16/64 tick of the clock will increase the timer value by 1
    
}
static inline void playNote(uint8_t wavelength, uint8_t duration) {

    OCR1A = wavelength;
    DDRB |= (1<<PB1);
    while (duration)
    {
        _delay_ms(1);
        duration--;
    }
    DDRB &= (0<<PB1);
}
int main(void)          
{   
    // DDRB |= (1<<PB5);
    init_timer1();
    while(1)
    
    {   
//        DDRB |= (1<<PB1);
//        PORTB ^= (1<<PB1);
//        _delay_ms(100);
        playNote(43,20);
        playNote(13,200);
        playNote(13,100);
        playNote(31,150);
        _delay_ms(400);
        playNote(50,200);
        playNote(100,200);
        playNote(60,100);
        playNote(23,150);
        _delay_ms(400);
        playNote(200,140);
        playNote(100,150);
        playNote(130,140);
        playNote(253,105);
        _delay_ms(400);

    }
        
        
    
    return (0);

}
