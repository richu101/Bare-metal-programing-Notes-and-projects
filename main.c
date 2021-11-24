/* 
------------------------------------------------------------------------------------------------
|   
|   Just a basic blink code
|   
|   This code works fine with mcu workin in 16Mhz clk freequency
|   
|   
|   
|   Reffrence https://codenlogic.blogspot.com/2015/07/interfacing-of-pcf-8574-to-atmega16.html
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
      while((TWSR&0xf8) != 0x08); // check the status register weater the start condition is send or not
      if((TWSR&0xf8) != 0x18)ack = 1;
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
        while((TWCR & (1<<TWINT)) == 0);              
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
                    i2c_start_transmit();
                    I2C_Write_Addr(0X08);
                    I2C_Write_Data(40);
              //  i2ctransmit_data(60);
                    I2C_Stop();
                    _delay_ms(5000);
                
        }
return (0);
}

/*
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


//--- I2C Start Condition ---//

void i2c_start()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA);	//--- Start Conditon 
	while (!(TWCR & (1<<TWINT)));				//--- Check for Start condition successful
}

//--- I2C Stop Condition ---//

void i2c_write(char x)
{
	TWDR = x;						//--- Move value to I2C reg
	TWCR = (1<<TWINT) | (1<<TWEN);	//--- Enable I2C and Clear Interrupt
	while (!(TWCR & (1<<TWINT)));	//--- Write Successful with TWDR Empty
}

//--- I2C Read Condition ---//

char i2c_read()
{
	TWCR = (1<<TWEN) | (1<<TWINT);	//--- Enable I2C and Clear Interrupt
	while (!(TWCR & (1<<TWINT)));	//--- Read successful with all data received in TWDR
	return TWDR;
} 

int main(void)
{
	DDRB = 0xFF;			//--- PORTD as OUTPUT
	PORTB = 0xFF;
	i2c_init();				//--- Initiate I2C comm 
	i2c_start();			//--- Start Condition to Slave device
	i2c_write(0x40);		//--- Write address of Slave into I2C to select slave
    while(1)
    {
			i2c_write(0xFF);	//--- Write data to IO Expander
			_delay_ms(1000);	//--- 1sec Delay
			i2c_write(0x00);	//--- Write data to IO Expander
			_delay_ms(1000);	//--- 1sec Delay
    }
}
*/
/*

#define F_CPU 16000000L
#ifndef __AVR_ATmega328P__ 
    #define __AVR_ATmega328P__
#endif
#include<avr/io.h>
#include<util/delay.h>

uint8_t ack=0;

void I2C_Init(){
  TWBR=0x48;
}
void I2C_Start(){
  TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
  while((TWCR&(1<<TWINT))==0);
  while((TWSR&0xF8)!=0x08);
}
void I2C_Write_Addr(unsigned char Addr){
  TWDR=(Addr<<1);
  TWCR=(1<<TWINT)|(1<<TWEN);
  while((TWCR&(1<<TWINT))==0);
  if((TWSR&0xF8)==0x18){
    ack=1;
  }
}
void I2C_Write_Data(unsigned char Data){
  if(ack){
    TWDR=Data;
    TWCR=(1<<TWINT)|(1<<TWEN);
    while((TWCR&(1<<TWINT))==0);
  }
}
void I2C_Stop(){
  TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
  while(TWCR&(1<<4));
  ack=0;
}
int main(void){
  I2C_Init();
while(1){
    I2C_Start();
    
    I2C_Write_Addr(0X3C);
    
    I2C_Write_Data(0X41);
    
    I2C_Write_Data(0X42);

    I2C_Write_Data(0X43);
    
    I2C_Write_Data(0X44);

    I2C_Write_Data(0X50);
    
    I2C_Stop();
    _delay_ms(1000);
}
  
  
}


*/