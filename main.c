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
uint8_t ack = 0;


void i2c_stop();



void i2c_init()
{

	TWBR = 0x48;	  	       // --- Baud rate is set by calculating the of TWBR see Details for Reference

}

void i2c_stop()
{
  TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
  while(TWCR&(1<<TWSTO)); // wait until the twint bit to clear
  ack=0;

}


void i2c_write_addr(uint8_t addr){


  TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
  while((TWCR & (1<<TWINT)) == 0);  //TWINT bit set (changing the bit to 0) by hardware when the TWI has finished
  while((TWSR&0xF8) != 0x08); // check the status register weater the start condition is send or not

  TWDR=(addr<<1);
  TWCR=(1<<TWINT)|(1<<TWEN);
  while((TWCR&(1<<TWINT))==0);
  if((TWSR&0xF8)==0x18)ack=1;
 // if ((TWSR & 0xF8) == 0x20) ack = 0;
 // if ((TWSR & 0xF8) == 0x38) ack = 3;


}

void i2c_transmit_data(unsigned char a )
{

  if(ack == 1)
  {
    
    TWDR = a;
    // while (TWCR & (1<<TWINT) == 1); 
    TWCR=(1<<TWINT)|(1<<TWEN);
    while((TWCR&(1<<TWINT)) != 0); // wait until the twint bit to clear

  }
  else if(ack == 3)
  {
    DDRB  = (1<<PB5); // Set the DDRB port in OUTPUT mode
    PORTB = (1<<PB5); // Toggle the PB5 port in every sec
  }
  if (ack == 0)
  {
    DDRB  &= ~(1<<PB5); // Set the DDRB port in OUTPUT mode 
  }
 // I2C Stop condition 
  TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
  while(TWCR&(1<<TWSTO)); // wait until the twint bit to clear
  ack=0;

}
void i2c_transmit_str(char str[] )
{

  uint8_t siz = 0;
  // siz = (sizeof(str[1])/sizeof(str[]))
  // for(uint8_t Count = 0; Count <= siz; Count++ )
  while(str[siz])
  {
    siz++;
    TWDR = str[siz];
    TWCR=(1<<TWINT)|(1<<TWEN);
    while (TWCR & (1<<TWINT) == 0); // wait until the twint bit to clear

  }
  ack = 0;
  i2c_stop();
}









void I2C_Init()
{
  TWBR=0x48;
}

void i2c_start_transmit()
{

      TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
      while((TWCR & (1<<TWINT)) == 0); 
      while((TWSR&0xF8) != 0x08); // check the status register weater the start condition is send or not

}

void I2C_Write_Data(unsigned char Data){
  
  if((TWSR&0xF8)==0x18)ack=1;
  
  if(ack){
    TWDR=Data;
    TWCR=(1<<TWINT)|(1<<TWEN);
    while((TWCR&(1<<TWINT))==0);
  }
  
}



int main()
{

 
       
        I2C_Init();
       uint8_t a = 48;
        while(1)
        {       
          
                    // i2c_start_transmit();
          //          i2c_write_addr(0x08);
                   
        i2c_write_addr(0x08);

        I2C_Write_Data(a++);
        I2C_Write_Data(a++);

        i2c_stop(); 
                    
                   //  I2C_Stop();
                    _delay_ms(500);
                
        }
return (0);
}

 

 /*

void i2c_write_data(unsigned char a ){
        if(ack){
        TWDR = a;
        TWCR=(1<<TWINT)|(1<<TWEN);
        while((TWCR & (1<<TWINT)) == 0);
        }

}

void I2C_Write_Addr(unsigned char Addr)
{

  TWDR=(Addr<<1);
  TWCR=(1<<TWINT)|(1<<TWEN);
  while((TWCR&(1<<TWINT))==0);
  if((TWSR&0xF8)==0x18)
  {
    ack=1;
  }
}

int main()
{
       
          i2c_init();
          uint8_t a = 0;
          DDRB = (1<<PB5); // Set the DDRB port in OUTPUT mode
          PORTB = (1<<PB5); // Toggle the PB5 port in every sec
          _delay_ms(1000);
        while(1)
        {      
          PORTB ^= (1<<PB5); // Toggle the PB5 port in every sec 
          i2c_write_addr(0x08);
          i2c_transmit_data(a++);
          i2c_stop();
          _delay_ms(500);
          // ^= (1<<PB5); // Toggle the PB5 port in every sec
                
        }
return (0);
}
*/