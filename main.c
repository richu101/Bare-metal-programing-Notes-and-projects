#ifndef __AVR_ATmega328P__ 
    #define __AVR_ATmega328P__
#endif
#define F_CPU 8000000UL
/*
#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include"liberaries/USART_liberry/usart.c"

static inline void init_timer1()
{   
    
    // enable the counter to work in ctc(clear timer on compare) mode
    TCCR0A |= (1<<COM1A0) | (1<<WGM01);
    // toggle OC0A on compare match
    TCCR0B |= (1<<CS00)| (1<<CS01) ;
    // set the clock speed 16MHz / 64
    // 16/64 tick of the clock will increase the timer value by 1
}
*/
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

static inline void initTimer0(void) {
  TCCR0A |= (1 << WGM01);                                  /* CTC mode */
  TCCR0A |= (1 << COM0B0);            /* Toggles OC0B(PD5) pin  each time through */
  TCCR0B |= (1 << CS00);              /* Clock at CPU frequency, ~8MHz */
  OCR0A = COUNTER_VALUE;                          /* carrier frequency */
}

static inline void initTimer1(void) {
  TCCR1B |= (1 << WGM12);                                  /* CTC mode */
  TCCR1B |= (1 << CS11);            /* Clock at CPU/8 frequency, ~1MHz */
  TIMSK1 |= (1 << OCIE1A);          /* enable output compare interrupt */
}

ISR(TIMER1_COMPA_vect) {                 /* ISR for audio-rate Timer 1 */
  ANTENNA_DDR ^= (1 << ANTENNA);          /* toggle carrier on and off */
}

static inline void transmitBeep(uint16_t pitch, uint16_t duration) {
  OCR1A = pitch;                               /* set pitch for timer1 */
  sei();                                         /* turn on interrupts */
  do {
    _delay_ms(1);                            /* delay for pitch cycles */
    duration--;
  } while (duration > 0);
  cli();                  /* and disable ISR so that it stops toggling */
  ANTENNA_DDR |= (1 << ANTENNA);               /* back on full carrier */
}

int main(void) {
  // -------- Inits --------- //

  // clock_prescale_set(clock_div_1);                  /* CPU clock 8 MHz */
  initTimer0();
  initTimer1();

  // ------ Event loop ------ //
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
