
/*
  Quick and dirty functions that make serial communications work.

  Note that receiveByte() blocks -- it sits and waits _forever_ for
   a byte to come in.  If you're doing anything that's more interesting,
   you'll want to implement this with interrupts.

   initUSART requires BAUDRATE to be defined in order to calculate
     the bit-rate multiplier.  9600 is a reasonable default.

  May not work with some of the older chips:
    Tiny2313, Mega8, Mega16, Mega32 have different pin macros
    If you're using these chips, see (e.g.) iom8.h for how it's done.
    These old chips don't specify UDR0 vs UDR1.
    Correspondingly, the macros will just be defined as UDR.
*/

#include <avr/io.h>
#include "usart.h"
#include <util/setbaud.h>
#ifndef F_CPU 
    #define F_CPU 16000000
#endif
#define BAUD 9600
#define UBBR_VAL ((F_CPU/16/BAUD)-1)
const char* serialStr[];

void serialbegin()
{
	UCSR0B = (1<<TXEN0) | (1<<RXEN0) ;
	UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);
	UBRR0L = UBBR_VAL;
	UBRR0H = UBBR_VAL >> 8;
}
void transmitByte(uint8_t data) {
                                     /* Wait for empty transmit buffer */
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = data;                                            /* send data */
}

uint8_t receiveByte(void) {
  loop_until_bit_is_set(UCSR0A, RXC0);       /* Wait for incoming data */
  return UDR0;                                /* return register value */
}

void printInt(uint16_t num)
{
uint8_t str[5];
int i = 0;
if (num == 0)
{
  str[i] = '0';
  i++;
}
while (num > 0)
{
  str[i] = num%10;
  num = num/10;
  i++;

}


for (int j = i-1; j>=0; j--)
{
  transmitByte(str[j]+48);
}
}
 /* Here are a bunch of useful printing commands */

void printString(const char myString[]) {
  uint8_t i = 0;
  while (myString[i]) {
    transmitByte(myString[i]);
    i++;
  }
}

const char* readString(uint8_t maxLength) {
  char response;
  char serialStr[maxLength];
  uint8_t i;
  i = 0;
  while (i <= (maxLength - 1)) {                   /* prevent over-runs */
    response = receiveByte();
    transmitByte(response);                                    /* echo */
    if (response == '\n') {                     /* enter marks the end */
      break;
    }
    else {
     serialStr[i] = response;                       /* add in a letter */
      i++;
    }
  }
  serialStr[i] = 0;                          /* terminal NULL character */
  return *serialStr;
}

/*
int readInt()
{

}
*/


