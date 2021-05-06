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
#include"musicnote.h"

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
        playNote(G3,200);
        playNote(F3,200);
        playNote(E3,100);
        playNote(Gx2,150);
        _delay_ms(G1;
        playNote(E1,200);
        playNote(A0,200);
        playNote(Ax0,100);
        playNote(Ax2,150);
        _delay_ms(400);
        playNote(B0,140);
        playNote(B1,150);
        playNote(Ax2,140);
        playNote(Ax1,105);
        _delay_ms(400);

    }
        
        
    
    return (0);

}
