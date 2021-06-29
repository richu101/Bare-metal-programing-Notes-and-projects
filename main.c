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
static inline void init_Timer0()
{
  TCCR0A |= (1<<COM0A0); // Toggle OC0A(PD6) on compare match
  TCCR0A |= (1<<WGM01);
  TCCR0B |= (1<<CS01);
  OCR0A = COUNTER_VALUE;
}
static inline void init_timer1()
{ 
  TIMSK1 |= (1<<OCIE1A); // Intrrept will enable when the timer value reaches the value in OCR1A
  TCCR1B |= (1<<WGM12);  // ctc mode
  TCCR1B |= (1 << CS11);  
}

void transmitBeep(uint16_t pitch,uint16_t duration)
{ 
  OCR1A = pitch;
  sei();
  while(duration >= 1)
  {
    _delay_ms(1);
  }
  cli();

  DDRD |= (1<<PD6);
}
ISR(TIMER1_COMPA_vect)
{
  DDRD ^= (1<<PD6);
}

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
