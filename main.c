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
    
    TCCR1B |= (1<<CS11) | (1<<CS10);
    // set the clock speed 16MHz / 64
    // 16/64 tick of the clock will increase the timer value by 1
}
void playNote(uint16_t period, uint16_t duration) {
  uint16_t elapsed;
  uint16_t i;
  for (elapsed = 0; elapsed < duration; elapsed +=  period) {
                     /* For loop with variable delay selects the pitch */
    for (i = 0; i < period; i++) {
      _delay_us(1);
    }
    PORTB ^= (1 << PB5);
  }
}
int main(void)          
{   
    DDRB |= (1<<PB5);
    while(1)
    
    {   
        playNote(230,1);
_delay_ms(50);        
        playNote(400,4);
_delay_ms(50);
        playNote(600,3);
_delay_ms(50);
playNote(7000,20);
_delay_ms(50);
playNote(6000,10);
_delay_ms(50);
playNote(5000,1);

_delay_ms(500);

        playNote(43,200);
        _delay_ms(500);

        /* playnote(159,200);
        _delay_ms(100);
        playnote(59,210);
        _delay_ms(100);
        playnote(90,110);
        _delay_ms(100);
        playnote(54,169);
*/
        
    }
        
        
    
    return (0);

}
