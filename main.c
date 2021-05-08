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
#include"timers/timer audio/musicnote.h"
#include"liberaries/USART_liberry/usart.c"

int  i = 1;
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
        DDRD |= (0<<PD2);
        init_timer1();
        uint8_t buttonstate , ledstate = 1, pstate = 1;

while(1)

{   
        DDRB |= (1<<PB1);
        PORTB ^= (1<<PB1);
//        _delay_ms(100);
buttonstate = PIND & (1<<PD2);
if (buttonstate != pstate)
{
        pstate = buttonstate;
        if (buttonstate)
        {
                DDRB |= (1<<PB5);
                PORTB ^= (1<<PB5);
if (bit_is_set(PORTB,PB5))
{
        playNote(C1,200);
                playNote(C1,200);
                playNote(C1,200);
        playNote(D1,200);
                playNote(D1,200);
                playNote(D1,200);
        playNote(E1,200);
                playNote(E1,200);
                playNote(E1,200);        
        playNote(F1,200);
                playNote(F1,200);
                playNote(F1,200);        
        playNote(G1,200);
                playNote(G1,200);
                playNote(G1,200);
        playNote(A1,200);
                playNote(A1,200);
                playNote(A1,200);
        playNote(B1,200);
                playNote(B1,200);
                playNote(B1,200);
        playNote(C1,200);
                playNote(C1,200);
                playNote(C1,200);

        playNote(C2,200);
                playNote(C2,200);
                playNote(C2,200);
        playNote(B2,200);
                playNote(B2,200);
                playNote(B2,200);
        playNote(A2,200);
                playNote(A2,200);
                playNote(A2,200);
        playNote(G2,200);
                playNote(G2,200);
                playNote(G2,200);
        playNote(F2,200);
                playNote(F2,200);
                playNote(F2,200);
        playNote(E2,200);
                playNote(E2,200);
                playNote(E2,200);
        playNote(D2,200);
                playNote(D2,200);
                playNote(D2,200);
        playNote(C2,200);
                playNote(C2,200);
                playNote(C2,200);

}
        }
}

    }
    return (0);

}
