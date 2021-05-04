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
    // enable the counter to work in ctc(clear timer on compare) mode
    TCCR0A |= (1<<COM0A0);
    // toggle OC0A on compare match
    TCCR1B |= (1<<CS11) | (1<<CS10);
    // set the clock speed 16MHz / 64
    // 16/64 tick of the clock will increase the timer value by 1
    
}
void playNote(uint16_t wavelength, uint16_t duration) {

    DDRD |= (1<<PD6);
    OCR0A = wavelength;
    while (duration)
    {
        _delay_ms(1);
        duration--;
    }
  
}
int main(void)          
{   
    DDRB |= (1<<PB5);
    while(1)
    
    {   
        playNote(25,3000);
    }
        
        
    
    return (0);

}
