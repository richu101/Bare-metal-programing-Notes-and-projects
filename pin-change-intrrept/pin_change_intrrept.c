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

#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
volatile int a = 0;
ISR(PCINT2_vect)
{
    if(bit_is_clear(PIND,PIND3))
    {
        a=20;
    }
    else
    {
        a=19;
    }
    

}
void pcint_enable()
{
    PCICR |= (1<<PCIE2); // Pin change intrrepts enables to PORTD pins
    // PCIE2 is PORTD pins
    PCMSK2 |= (1<<PCINT19); // pin change intrrept enable for PD4 pin  
    sei(); // enable the globaol intrrepts
}

int main(void)
{
    
    DDRB = 0xff;
    DDRD |= (0<<PD3);  //setting PD2 pin as output mode
    PORTD |= (1<<PD3); //enabling the internal pull up
    pcint_enable();
    
    while(1)
    {
    PORTB = 0;
    
    if(a==20)
    {
        PORTB = 0xff;
        _delay_ms(2000);
        a--;
    }

    }
return (0);

}
