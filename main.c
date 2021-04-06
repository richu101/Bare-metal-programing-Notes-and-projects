#ifndef __AVR_ATmega328P__ 
    #define __AVR_ATmega328P__
#endif
#define F_CPU 16000000UL

#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include"liberaries/USART_liberry/usart.c"


volatile uint8_t i;

ISR(INT0_vect)
{
    // falling edge will trigger this intrrept
    if(bit_is_set(PIND,PIND2))
    {
        PORTB ^= (0xff);
        if (PORTB)
        {
            transmitByte(12);
            printString("on");
        }
        if (PORTB==0)
        {
            transmitByte(12);
            printString("off");
        }
        
    }


}
void external_intrrept_init()
{
    EIMSK |= (1<<INT0);
    EICRA |= (1<<ISC01);
    EICRA |= (1<<ISC00);  //Any logic change in int0 will trigger the intrrept 
    sei();
}
int main(void)          
{
    DDRB = 0xff; 
    initUSART();
    DDRD |= (0<<PD2);  //setting PD2 pin as output mode
    external_intrrept_init();
    while(1)
    {
    
    }
    return (0);

}
