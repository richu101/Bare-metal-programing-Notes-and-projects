/* 
-------------------------------------------------------------------------------
|   
|   This progtam is to create a pwm signal using the timer 1 
|   16 bit timer 
|   in this the pwm is generated using the phase corrected pwm mode
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
<<<<<<< HEAD
#include<USART_liberry/usart.c>
void init_Timers(void)
=======
#include<usart.c>
void pwm (int i)
>>>>>>> 3775e376ed6c2f8939f66c34b6b2fef4abcf9912
{
   DDRB |= (1 << DDB1);
   // PB1 as output
   OCR1A = i;
   // set PWM duty cycle at 10bit
   TCCR1A |= (1 << COM1A1);
   // set non-inverting mode(clear on comapre match)
   TCCR1A |= (1 << WGM11) | (1 << WGM10);
   // set 10bit phase corrected PWM Mode
   TCCR1B |= (1 << CS11);
   // set prescaler to 8 and starts PWM
}
int main(void)
{
  serialbegin();
<<<<<<< HEAD
  init_Timers();
  OCR1A = 0;
  OCR1B = 0;
  printString("enter the duty cycle : \n");
   while (1)
   {
      PORTB ^= (1<<PB5);
      
      i = receiveByte();
      OCR1B = OCR1A;
      _delay_ms(20);
      printInt(i);
      OCR1A = i;
=======
  printString("plz enter a string");
  int i = 0 ;
  int direction = 1;
  printString(readString(10));
   while (1)
   {
    
    PORTB ^=(1<<PB5);
    _delay_us(900);
    i = i + direction;
    if (i==1023)
    {
      direction = -1;
    }
     if (i==0)
     {
       direction = 1;
     }
     
   pwm(i);
>>>>>>> 3775e376ed6c2f8939f66c34b6b2fef4abcf9912
   }
}