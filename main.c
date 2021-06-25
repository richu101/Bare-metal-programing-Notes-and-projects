#ifndef __AVR_ATmega328P__ 
    #define __AVR_ATmega328P__
#endif
#define F_CPU 8000000UL

#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */
#include <avr/power.h>
#include <avr/interrupt.h>
#include <pindefine.h>
#include <scale16.h>

#define COUNTER_VALUE   3          /* determines carrier frequency */

// From f = f_cpu / ( 2* N* (1 + OCRnx) )
// Good values for the AM band from 2 to 6: pick one that's clear
// Divide by two b/c we're toggling on or off each loop;
//  a full cycle of the carrier takes two loops.
// 8Mhz / (2 * 1 * (1+2)) = 1333 kHz
// 8Mhz / (2 * 1 * (1+3)) = 1000 kHz
// 8Mhz / (2 * 1 * (1+4)) = 800 kHz
// 8Mhz / (2 * 1 * (1+5)) = 670 kHz
// 8Mhz / (2 * 1 * (1+6)) = 570 kHz
// 8Mhz / (2 * 1 * (1+7)) = 500 kHz

int main()
{
  while (1) {

    transmitBeep(E3, 200);
    _delay_ms(100);
    transmitBeep(D3, 200);
    _delay_ms(200);
    transmitBeep(E3, 200);
    _delay_ms(200);
    
    transmitBeep(E3, 200);
    transmitBeep(A3, 200);
    _delay_ms(200);
    transmitBeep(D3, 400);
    _delay_ms(500);
    transmitBeep(E3, 400);

    _delay_ms(250);

  }                                                  /* End event loop */
  return 0;                            /* This line is never reached */
}
