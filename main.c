/*
    ------------------------------------------------------------------------
    #   This program is to fade an led using pwm
    #   here the pwm is generated just using program not using timers
    #
    #
    #
*/
#ifndef __AVR_ATmega328P__ 
    #define __AVR_ATmega328P__
#endif
#define F_CPU 8000000UL
/* PWM Learning Codes */
#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */

#define duratation 20

void pwmgenerator(uint8_t dutycycle)
{
    
    uint8_t i = 0;
    for(i =0; i < 255; i++)
        {
        if (i >= dutycycle)
        {
            PORTB = 0;
        }
        else
        {
            PORTB = 0xff;
        }
        
        _delay_us(duratation);
        }
}



int main()
{
                
    DDRB = 0xff; // Set the DDRB port in OUTPUT mode
    uint8_t direction = 1;
    uint8_t brightness = 0;
        while (1)
    {   
    
        if(brightness == 0) direction = 1;
        if(brightness == 255) direction= -1;
        brightness += direction; 
        pwmgenerator(brightness);
    }

    return (0);
}
