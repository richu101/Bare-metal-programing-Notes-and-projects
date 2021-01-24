/*

#  This part is to define the board that we are using 
#  You can see all  the board list that are availabele in the ave/io.h lib by 
#  peacking to the header just select the avr/io.h in the #include part and press F12
#  press ctrl + f and search for the board that u are looking for
#  If your board is available then u can see the board name unde __AVR_your-board__
#  Here am using Atmega328p SO   __AVR_ATmega328P__ 

*/  

#ifndef __AVR_ATmega328P__ 
    #define __AVR_ATmega328P__
#endif
#define F_CPU 16000000UL
#define threshold 12000
#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include<avr/power.h>
#include"USART_liberry/usart.h"
volatile int cycle_count ;



ISR(PCINT2_vect)
{
    cycle_count++; //charge cycle counter
    DDRD |= (1<<PD4);
    _delay_us(1);
    DDRD |= ~(1<<PD4);
    

}
void pcint_enable()
{
    PCICR |= (1<<PCIE2); // Pin change intrrepts enables to PORTD pins
    // PCIE2 is PORTD pins
    PCMSK2 |= (1<<PCINT19); // pin change intrrept enable for PD4 pin  
    
}

int main(void)
{
    clock_prescale_set(clock_div_1);
    pcint_enable();
    serialbegin();
    MCUCR |=(1<<PUD);
    DDRB   = 0xff;
    PORTD |= (1<<PD4);
    
    

    while(1)
    {
    cycle_count = 0; // reset the charge cycle counter
    DDRD |= (1<<PD4); //when it is in output mode the cap starts charging bcs we set the port as high alredy 
    sei();
    _delay_ms(200);
    cli(); //disable the global intrrept vect
    if(cycle_count == threshold)
    {
        PORTB = 0xff;
    }
    else
    {
        PORTB = 0;
    }
    serialwriteint(cycle_count);
    }
return (0);

}

