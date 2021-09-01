/*
    | ------------------------------------------------------------------------
    |   This program is to ffade an led using hardware pwm 
    |   Here we are using ttimer 1 & 2 runnin in ctc mode 
    |   The counter counts from BOTTOM to TOP then restarts from BOTTOM. 
    |   In non-inverting compare output mode, the output compare (OC1x) 
    |   is cleared on the compare match between TCNT1 and OCR1x, and set at BOTTOM
*/
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif
#define F_CPU 8000000UL
/* PWM Learning Codes */
#include <avr/io.h>     /* Defines pins, ports, etc */
#include <util/delay.h> /* Functions to waste time */

#define duratation 20

void timer1init(uint8_t dutycycle)
{
// Timer 1 (16 bit timer) initilazation

    TCCR1B |= (1<<WGM12) ; // | fast pwm with 8 bit
    TCCR1A |= (1<<WGM10) ; // | fast pwm with 8 bit
    TCCR1B |= (1<<CS11);   // | clk prescalr div / 8
    TCCR1A |= (1<<COM1A1); // | Clear OC1A on compare match when up-counting
    TCCR1A |= (1<<COM1B1); // | Clear OC1B on compare match when up-counting
// Timer 2 (8 bit timer) initilazation

    TCCR2A |= (1<<WGM20) ; // | fast pwm with 8 bit
    TCCR2A |= (1<<WGM21) ; // | fast pwm with 8 bit
    TCCR2B |= (1<<CS21);   // | clk prescalr div / 8
    TCCR2A |= (1<<COM2A1); // | Clear OC2A on compare match, set OC2A at BOTTOM,(non-inverting mode).
    
}

int main()
{
    DDRB
    return (0);
}
