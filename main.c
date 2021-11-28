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


uint8_t ack=0;
void I2C_Init()
{
  TWBR=0x48;
}

void i2c_init()
{

	TWBR = 0x48;	  	       // --- Baud rate is set by calculating the of TWBR see Details for Reference
	// TWCR = (1<<TWEN);       // --- Enable I2C
	// TWSR = 0x00;	       // --- Prescaler set to 1
}

void i2c_start_transmit()
{

      TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
      while((TWCR & (1<<TWINT))); 
      while((TWSR&0xF8) != 0x08); // check the status register weater the start condition is send or not
      
}
void I2C_Start()
{
      TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
      while((TWCR&(1<<TWINT))==0);
      while((TWSR&0xF8)!=0x08);
}



void i2c_write_data(unsigned char a ){
        if(ack){
        TWDR = a;
        TWCR=(1<<TWINT)|(1<<TWEN);
        while((TWCR & (1<<TWINT)) == 0);
        }

}

void I2C_Write_Data(unsigned char Data){
  if(ack){
    TWDR=Data;
    TWCR=(1<<TWINT)|(1<<TWEN);
    while((TWCR&(1<<TWINT))==0);
  }
}


void i2c_write_addr (uint8_t a, uint8_t b  )  
{
/*
| 1st ardument is the 7bit slave addr
| 
| 2nd argument  is the read or write bit b = 1 for (READ) b = 0 (WRITE)
|
|
*/
        if (b == 0) a = (a<<1);
        if (b == 1) a = (a<<1) | (1<<0);
        TWCR=(1<<TWINT)|(1<<TWEN);
        TWDR = a;
        while((TWCR & (1<<TWINT)) == 0);     
        if((TWSR&0xF8) != 0x18)ack = 1;         
}

void I2C_Write_Addr(unsigned char Addr){
  TWDR=(Addr<<1);
  TWCR=(1<<TWINT)|(1<<TWEN);
  while((TWCR&(1<<TWINT))==0);
  if((TWSR&0xF8)==0x18){
    ack=1;
  }
}
void I2C_Stop(){
  TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
  while(TWCR&(1<<4));
  ack=0;
}
int main()
{
       
        I2C_Init();
        while(1)
        {       
                    I2C_Start();
                    I2C_Write_Addr(0x08);
                    I2C_Write_Data(30);
                  //  i2ctransmit_data(60);
                    I2C_Stop();
                    _delay_ms(5000);
                
        }
return (0);
}

