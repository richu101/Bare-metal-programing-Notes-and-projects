/* 
-------------------------------------------------------------------------------
|   
|   This progtam is to create a pwm signal using the timer 1 
|   and it's duty cycle is cntrolled by the input we given via USART 
|   
|   In this the pwm is generated using the fast pwm mode
|   
|   The freequency of the pwm can be calculatedd using this equatation
|                
|    fOCnxPCPWM =  f_clk_IO /  N * 256
--------------------------------------------------------------------------------
*/


#ifndef __AVR_ATmega328P__     
    #define __AVR_ATmega328P__ 
#endif
#define F_CPU 16000000UL

#include<avr/io.h>
#include<util/delay.h>
#include<USART_liberry/usart.c>
void init_Timers(void)
{
  /*
      This function initilze the the pin's OC1A & OC1B in 8 bit fast PWM mode
      Timer 1 is a  16bit timer we only need it to work in 8 bit we can set this 
      by setting the WGM10 - WGM13 register
      Set the prescaler =  8  

  */
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
  serialbegin();
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
   }
}

