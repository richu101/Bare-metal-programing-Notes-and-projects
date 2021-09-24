/* 
-------------------------------------------------------------------------------
|   
|   Just a basic blink code
|   
|   This code works fine with mcu workin in 16Mhz clk freequency
|   
|
|   
|   
|
--------------------------------------------------------------------------------
*/
#ifndef __AVR_ATmega8A__ 
    #define __AVR_ATmega8A__
#endif
#define F_CPU 16000000UL

#include<avr/io.h>
#include<util/delay.h>

int main()
{
        DDRB = (1<<PB5); // Set the DDRB port in OUTPUT mode
        while(1)
        {
                PORTB ^= (1<<PB5); // Toggle the PB5 port in every sec
                _delay_ms(1000);
        }
return (0);
}
