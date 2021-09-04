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
// #include"timers/timer audio/musicnote.h"
// #include"liberaries/USART_liberry/usart.c"

int main(void)
{
   DDRB |= (1 << DDB1);
   // PB1 as output
   OCR1A = 100;
   // set PWM for 50% duty cycle at 10bit
   TCCR1A |= (1 << COM1A1);
   // set non-inverting mode(clear on comapre match)
   TCCR1A |= (1 << WGM11) | (1 << WGM10);
   // set 10bit phase corrected PWM Mode
   TCCR1B |= (1 << CS11);
   // set prescaler to 8 and starts PWM
   while (1)
   {
    PORTB ^=(1<<PB5);
    _delay_ms(200); 
   }
}