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
/*
#ifndef __AVR_ATmega328P__     
    #define __AVR_ATmega328P__
#endif
#define F_CPU 16000000UL

#include<avr/io.h>
#include<util/delay.h>
#include<liberaries/USART_liberry/usart.c>
void init_Timers(uint8_t i)
{
   DDRB |= (1 << DDB1);
   DDRB |= (1 << DDB2);
   // PB1 and PB2 as output
   OCR1A = i;
   OCR1B = OCR1A;
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
   while (1)
   {
     PORTB ^= (1<<PB5);
    printString("enter the duty cycle :");
    _delay_us(5000);
    i += direction;
    if (i==255)direction = -1;
    if (i==0)direction = 1;
   init_Timers(i);
   }
}

*/

/* _________________________________________________

    reaction time game using timer 1
    
    _________________________________________________
*/

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
    TCCR1B |= (1<<CS11) | (1<<CS10);
    // set the (clk i/o) clock speed 16MHz / 64
    // 16/64 tick of the clock will increase the timer value by 1
}

int main(void)          
{   
    char byte;
    uint16_t timerval;
    initUSART();
    init_timer1();
    DDRB = (1<<PB5);
    while(1)
    
    {

        printString("ready .... \n");
        byte = receiveByte();
        PORTB |= (1<<PB5);
        _delay_ms(500);
        PORTB = 0;
        printString("Go >>");
        TCNT1 = 0;
        if(bit_is_set(PIND,PD2))
        {
            printString("no cheeting..\n    ");
        }
        else
        {   
            loop_until_bit_is_set(PIND,PD2);
            timerval = TCNT1;
            TCNT1 = 0;
            printString("your reaction time is .....");
            printInt(timerval);
            transmitByte(13); // clear the terminal set the curser to 0 th position
        }
        
        
    }
    return (0);

}
