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

#define BUAD 9600
#define UBBR_VAL ((F_CPU/16/BUAD)-1)

#define buffersize  128
char serialbuffer [buffersize];
uint8_t readpos = 0;
uint8_t writepos = 0;

void appendserial(char c);
void writeserial(char c[]); 

uint8_t Read_val = 0;
 void serialbegin();
 
int main(void)
{
 serialbegin();
 uint8_t i;
 sei();
 
 writeserial("Hello/n/r");
 writeserial("WorLdD/n/r");
    while (1) 
    {
		
    }
	return 0;
}

 void serialbegin()
 {
	 UCSR0B = (1<<TXEN0) | (1<<TXCIE0) ;
	 UCSR0C = (1<<UCSZ00)| (1<<UCSZ01) ;
	 UBRR0L = UBBR_VAL;
	 UBRR0H = UBBR_VAL >> 8;
 }
 /*
 void writeserial(char c[])
 {
 }
 */
void writeserial(char c[])
{
	if (i=0;i<10;i++)
	{
		appendserial(c[i]);
	}
	if (UCSR0A & (1<<UDRE0))
	{
		UDR0 = 0;
	}
}

void appendserial(char c)
{
	serialbuffer[writepos] = c;
	writepos++;
	if (writepos >= buffersize)
	{
		writepos =0;
	}
}
ISR(USART_TX_vect)
{
	if (readpos != writepos)
	{
		UDR0 = serialbuffer[readpos];
		readpos++;
		if (readpos <= buffersize)
		{
			readpos++;
		}
	}
	
}
