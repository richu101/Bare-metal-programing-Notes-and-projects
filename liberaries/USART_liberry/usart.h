/*
 * USART.c
 *
 * This is a library for USART communication  (Serial communication). 
 * To initialize the USART communication call the serial begin function. This will initialize with baud rate 9600 . If you want to change the baud rate just the value of BAUD to whatever BAUD you want
 * DATA Frame structure - 1 ( start bit and stop bit ) 8 Bit data frame and no parity is used 
  
 
  ------------------------------------------------------------------------------------------------------------------------------------------
 |                                                                                                                                           |
 |    How USART communication work's ...................?                                                                                    |
 |                                                                                                                                           |
 |  The main part of the USART communication is a register named UDR                                                                         |
 |  For receving a data we sending the data to the UDR register and reading it.                                                              |
 |  For sending a data we write the vlue to  the UDR register and the avr shift out the value according to the data frame we set             |
 |                                                                                                                                           |
  -------------------------------------------------------------------------------------------------------------------------------------------
_______________________________________________________________________________________________________________________________________________
 ....... How to use the functions in this liberary .......

    serialbegin()      - This functon initilise the usart communication with 9600 BAUD rate , 8 bit dataframe and no paritty Bit
    
    serialreadchar()   - This function return a single charector that u send through serial monitor

    serialreadint()    - This function return an integer num that u send through serial monitor

    serialreadstr()    - This function return string that u send through serial monitor

    serialwritechar()  - This print a single character that you send ... eg serialwritechar('a');

    serialwriteint()   - This print integer value that you send ... eg serialwritechar(200);

    serialwritestr()   - This print the string that you send ... eg serialwritechar("hello");

_______________________________________________________________________________________________________________________________________________


 * Created: 28-08-2020 07:02:34 PM
 * Author : RICHU BINI
 */ 


#include<avr/io.h>
 // #define F_CPU 16000000
#ifndef __AVR_ATmega328P__ 
    #define __AVR_ATmega328P__
#endif

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

//Transmit string through UART
void serialwriteptr(unsigned char *str)
{
	while(*str)
	{
		UDR0 = *str++;
		while(!(UCSR0A&(1<<UDRE0)));
	}
}
void serialnewline()
{
	UDR0 = 10; //10 is the ascie for " /n "
	//wait until the transmission is completed
		while(!(UCSR0A&(1<<UDRE0)));

}

//Transmit integer through UART
void serialwriteint(int data)
{	
	int rev=0;
	char d;
	while(data>0)
	{
		rev=(rev*10)+data%10;
		data=data/10;
	}
	//put the data to be transmitted into the UDR register
	while (rev>0)
	{
<<<<<<< HEAD
	// most of the serial moniters are reading the data as char so to print a an integer we need to send that integer as charectors
	
		d = data%10 + '0' ; // this will convert the int num to correspointing char ascii
=======
		d = rev%10 + '0' ;
>>>>>>> 6231a0d849ed7ddfe9388585535edde9801df062
		UDR0 = d;
		//wait until the transmission is completed
		while(!(UCSR0A&(1<<UDRE0)));
		rev = rev/10;
	}
	
		
}
void  serialwritestr(unsigned char a[20])
{
	unsigned char *ptrval;
	ptrval = a;
	serialwriteptr(ptrval);
}



	//Receive a character through UART
	unsigned char serialreadchar()
	{
		//wait for the charater
		while(!(UCSR0A & (1<<RXC0)));

		//return the received charater
		return(UDR0);
	}
	//Receive a integer through UART
	int serialreadint()
	{
		//wait for the value
		while(!(UCSR0A & (1<<RXC0)));

		//return the received integer
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
