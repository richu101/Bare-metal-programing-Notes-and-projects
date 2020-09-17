/*
 * Serial communicatation liberary.c
 *
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

uint8_t txreadpos=0;
uint8_t rxreadpos=0;
uint8_t txwritepos=0;
uint8_t rxgetpos = 55;
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


char *rxgetchar (void)
{  
	
		if (rxdata[0] == '0')
		{
		    DDRB = (1<<5);
			PORTB = (1<<5);
		}
		return rxdata;
		
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


ISR(USART_RX_vect)
{   
	for (int *ptr = rxdata; ptr < &rxdata[buffersize]; ptr++)
    *ptr = UDR0;
	
}
