/* 
-------------------------------------------------------------------------------
|   
|   This progtam is to create a pwm signal using the timer 1 
|   16 bit timer 
|   in this the pwm is generated using the fast pwm mode
|   
|   
|   The freequency of the pwm can be calculatedd using this equatation
|                
|    fOCnxPCPWM =  f_clk_IO / 2 * prescaler divider * TOP 
|   
|   
--------------------------------------------------------------------------------
*/


#ifndef __AVR_ATmega328P__     
    #define __AVR_ATmega328P__
#endif
#define F_CPU 16000000UL

#include<avr/io.h>
#include<util/delay.h>
#include<liberaries/USART_liberry/usart.c>
void init_Timers(void)
{
   DDRB |= (1 << DDB1);
   DDRB |= (1 << DDB2);
   // PB1 and PB2 as output
   
   TCCR1A |= (1 << COM1A1);
   TCCR1A |= (1 << COM1B1);
   // set non-inverting mode(clear on comapre match)
   TCCR1A |= (1 << WGM10);
   TCCR1B |= (1<<WGM12);
   // set 8bit fast PWM Mode
   TCCR1B |= (1 << CS11);
   // set prescaler to 8 and starts PWM

     
}
int main(void)
{
  uint8_t i = 0 ;
  uint8_t direction = 0;
  initUSART();
  init_Timers();
  OCR1A = 0;
  OCR1B = 0;

   while (1)
   {
     PORTB ^= (1<<PB5);
   printString("enter the duty cycle :");
   i = receiveByte();
    _delay_us(5000);
    i += direction;
    if (i==255)direction = -1;
    if (i==0)direction = 1;
   OCR1B = OCR1A;
   OCR1A = i;
   }
}

