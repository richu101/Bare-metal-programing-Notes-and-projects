/* 
------------------------------------------------------------------------------------------------
|   
|   Just a basic blink code
|   
|   This code works fine with mcu workin in 16Mhz clk freequency
|   
|   
|   
|   
|
-----------------------------------------------------------------------------------------------
*/

#ifndef __AVR_ATmega328P__ 
    #define __AVR_ATmega328P__
#endif
#define F_CPU 16000000UL


#include<avr/io.h>
#include<util/delay.h>

void i2c_init()
{

	TWBR = 0x48;	  	       // --- Baud rate is set by calculating the of TWBR see Details for Reference

}

i2c_write_addr(uint8_t a,uint8_t b)
{

TWCR |= (1<<TWSTA)| (1<<TWEN) | (1<<TWINT);
while (TWCR & (1<<TWINT) == 1);
TWCR &= ~(1<<TWSTA);


}


int main()
{
       
          i2c_init();
        while(1)
        {       
           
                    _delay_ms(500);
                
        }
return (0);
}

