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

ISR(INT0_vect)
{
    if(bit_is_clear(PIND,PIND2))
    {
        PORTB = 0;
        _delay_ms(1000);
    }

}
void external_intrrept_init()
{
    EIMSK |= (1<<INT0);
    EICRA |= (1<<ISC01);  //The falling edge of INT0 generates an interrupt request.
    sei();  // enable all  the intrrept
}

int main(void)
{
    
    DDRB = 0xff;
    DDRD |= (0<<PD2);  //setting PD2 pin as output mode
    PORTD |= (1<<PD2); //enabling the internal pull up
    external_intrrept_init();
    
    while(1)
    {
    PORTB = 0xff;
    _delay_ms(1000);
    PORTB = (0<<5);
    _delay_ms(100);

    }
return (0);

}
