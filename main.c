/* 
-------------------------------------------------------------------------------
|   
|   Just a basic blink code
|   
|   This code works fine with mcu workin in 16Mhz clk freequency
|   
|   
|   
|   
|
--------------------------------------------------------------------------------
*/
#ifndef __AVR_ATmega328P__ 
    #define __AVR_ATmega328P__
#endif
#define F_CPU 16000000UL

#include<avr/io.h>
#include<util/delay.h>
void i2c_init()
{
	TWBR = 0x62;		//--- Baud rate is set by calculating the of TWBR see Details for Reference
	TWCR = (1<<TWEN);	//--- Enable I2C
	TWSR = 0x00;		//--- Prescaler set to 1
}
void i2c_start_transmit(){
        TWCR = 0x4A;
        while(!(TWCR & (1<<TWINT))); 
}

void i2c_stop_transmit(){
        TWCR = 0x49;
        while(!(TWCR & (1<<TWINT))); 
}

void i2ctransmit_data(unsigned int a){
        TWCR = 0x48;
        TWDR = a;

        while(!(TWCR & (1<<TWINT)));
}

void i2caddr (uint8_t a, uint8_t b  )
{
        // The value of b = 1 for (READ) b = 0 (WRITE)
        if (b == 0) a |=(0<<1);
        if (b == 1) a |=(1<<1);
        i2ctransmit_data(a);              
}

int main()
{
        DDRB = (1<<PB5); // Set the DDRB port in OUTPUT mode
        while(1)
        {       
                i2c_start_transmit();
                i2caddr(8,0);
                
                PORTB ^= (1<<PB5); // Toggle the PB5 port in every sec
                _delay_ms(1000);
                
        }
return (0);
}
