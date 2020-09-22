/*
 * Serial communication liberary.c
 *
 * This is a library for USART communication  (Serial communication). 
 * To initialize the USART communication call the serial begin function. This will initialize with baud rate 9600 . If you want to change the baud rate just the value of BAUD to whatever BAUD you want
 * DATA Frame structure - 1 ( start bit and stop bit ) 8 Bit data frame and no parity is used  
   
 
 
 
 * Created: 28-08-2020 07:02:34 PM
 * Author : RICHU BINI
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000
#include <util/delay.h>


#define BAUD 9600
#define UBBR_VAL ((F_CPU/16/BAUD)-1)
#define buffersize 128

char serialbuffer[buffersize];
char rxdata[buffersize] ;

int rxintdata;
uint8_t txreadpos=0;
uint8_t rxreadpos=0;
uint8_t txwritepos=0;
uint8_t rxgetpos = 0;
char data;

void appendserial(char c);
void writeserial(char c[]);
void serialbegin();
char *rxgetchar ();

int main(void)
{
  serialbegin();
   DDRB = (1<<5);
  sei();
 
  
  // writeserial("World");
  while(1)
  {
	
	 writeserial(rxgetchar());
	 _delay_ms(500);


  }
  return 0;
}

void serialbegin()
{
	UCSR0B = (1<<TXEN0) | (1<<TXCIE0) | (1<<RXEN0) | (1<<RXCIE0);
	UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);
	UBRR0L = UBBR_VAL;
	UBRR0H = UBBR_VAL >> 8;
}




void writeserial(char c[])
{
  
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
  serialbuffer[txwritepos] = c;
  txwritepos++;
  if(txwritepos >= buffersize)
  {
    txwritepos = 0;
  }
}


char rxgetchar (void)
{  
	while(!(UCSR0A & (1<<RXC0)))
	
	return UDR0;
} 


ISR(USART_TX_vect)  
{
	
   if(txreadpos != txwritepos)
  {
    UDR0 = serialbuffer[txreadpos];
    txreadpos++;
  }
  if (txreadpos >= buffersize)
  {
	  txreadpos = 0;
  }
  
  
}

/*

ISR(USART_RX_vect)
{   
	 
	 rxdata[rxreadpos] = UDR0;
	 rxreadpos++;
	// rxdata[rxreadpos] = '/0';	 
	 if (rxreadpos >= (buffersize-1))
	 {
		 rxreadpos = 0;
	 }  	
}

*/