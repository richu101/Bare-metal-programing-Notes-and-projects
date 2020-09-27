#include<avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

unsigned char string[20];
#define BAUD 9600
#define UBBR_VAL ((F_CPU/16/BAUD)-1)


void serialbegin()
{
	UCSR0B = (1<<TXEN0) | (1<<RXEN0) ;
	UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);
	UBRR0L = UBBR_VAL;
	UBRR0H = UBBR_VAL >> 8;
}

//Transmit character through UART
void serialwritechar(unsigned char data)
{
	//put the data to be transmitted into the UDR register
	UDR0 = data;

	//wait until the transmission is completed
	while(!(UCSR0A&(1<<UDRE0)));
}
void * serialwritestr(unsigned char a[20])
{
	unsigned char * ptrval;
	ptrval = a;
	serialwriteptr(ptrval);


}

//Transmit string through UART
void serialwriteptr(unsigned char *str)
{
	while(*str)
	{
		UDR0 = *str++;
		while(!(UCSR0A&(1<<UDRE0)));
	}
}

	//Receive a character through UART
	unsigned char serialreadchar()
	{
		//wait for the charater
		while(!(UCSR0A & (1<<RXC0)));

		//return the received charater
		return(UDR0);
	}

	//Receive string through UART
	unsigned char * serialreadstr()
	{
		unsigned char  x, i = 0;

		//receive the characters until a null value is seceived
		while((x = serialreadchar()) != 0)
		{
			//and store the received characters into the array string[] one-by-one
			string[i++] = x;
		}

		//insert NULL to terminate the string
		string[i] = '\0';

		//return the received string
		return(string);
	}

	int main()
	{
		//initialize the UART circuitry
	    serialbegin();

		//Transmit the Received string onto the UART again
		while(1)
		{
			serialwriteptr("hello");
			_delay_ms(500);
		}
		return 0;
		
	}	