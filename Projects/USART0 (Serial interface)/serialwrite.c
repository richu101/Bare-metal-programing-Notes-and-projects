/*

 * Serial communicatation liberary.c
 *
 * Created: 28-08-2020 07:02:34 PM
 * Author : RICHU BINI
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 16000000
#define BAUD 9600
#define UBBR_VAL ((F_CPU/16/BAUD)-1)
#define buffersize 128

char serialbuffer[buffersize];
uint8_t readpos=0;
uint8_t writepos=0;
uint8_t Read_val = 0;

void appendserial(char c);
void writeserial(char c[]);
void serialbegin();

int main(void)
{
  serialbegin();
  sei();
  writeserial("Hello");
  writeserial("World");
  while(1)
  {
    //UDRE0 = 0;
  }
  return 0;
}

void serialbegin()
{
  UCSR0B = (1<<TXEN0) | (1<<TXCIE0);
  UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);
  UBRR0L = UBBR_VAL;
  UBRR0H = UBBR_VAL >> 8;
}

void writeserial(char c[])
{
  //for(uint8_t i=0;i<10;i++)
  while(*c != 0)
  {
    appendserial(*c);
    c++;
  }
  appendserial(' ');
  if(UCSR0A & (1<<UDRE0))
  {
    UDR0 = 0;
  }
}

void appendserial(char c)
{
  serialbuffer[writepos] = c;
  writepos++;
  if(writepos >= buffersize)
  {
    writepos = 0;
  }
}

ISR(USART_TX_vect)  
{
  if(readpos != writepos)
  {
    UDR0 = serialbuffer[readpos];
    readpos++;
   // if(readpos <= buffersize)
   // {
    //  readpos++;
   // }
  }
}
