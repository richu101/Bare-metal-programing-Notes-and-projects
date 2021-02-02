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

#ifndef BAUD
#define BAUD 9600
#endif

#define UBBR_VAL ((F_CPU/16/BAUD)-1)


void serialbegin(); // This function is to initilize the hardware uart w

void transmitbyte(uint8_t data);
uint8_t receivebyte();

void serialwritechar(unsigned char data);
void serialwriteint(uint16_t data);

void  serialwritestr(unsigned char a[20]);
unsigned char serialreadchar();
int serialreadint();
	
