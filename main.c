/* 
-------------------------------------------------------------------------------
|   
|   This program create tone signal in PD6 (12 th pin) pin 
|   Here we use the ctc mode of timer 0 (clear timer on compare match)
|   
|   HOW it works .....!
|
|   when the timer value reaches the value in OCRxn register
|   it will togle the OCnx pin
|
--------------------------------------------------------------------------------
*/
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
    
    // enable the counter to work in ctc(clear timer on compare) mode
    TCCR0A |= (1<<COM1A0) | (1<<WGM01);
    // toggle OC0A on compare match
    TCCR0B |= (1<<CS00)| (1<<CS01) ;
    // set the clock speed 16MHz / 64
    // 16/64 tick of the clock will increase the timer value by 1
    
}
static inline void playNote(uint8_t wavelength, uint8_t duration) {

    OCR0A = wavelength;
    DDRD |= (1<<PD6);
    while (duration)
    {
        _delay_ms(1);
        duration--;
    }
    DDRD &= (0<<PD6);
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
        playNote(100,200);
        playNote(200,200);
        playNote(200,100);
        playNote(200,150);
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
