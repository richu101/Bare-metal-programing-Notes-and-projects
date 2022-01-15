#ifndef _i2c_h
#include<string.h>
#endif

uint8_t ack = 0;

void i2c_write_addr(uint8_t addr){


  TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
  while((TWCR & (1<<TWINT)) == 0);  //TWINT bit set (changing the bit to 0) by hardware when the TWI has finished
  while((TWSR&0xF8) != 0x08); // check the status register weater the start condition is send or not

  TWDR=(addr<<1);
  TWCR=(1<<TWINT)|(1<<TWEN);
  while((TWCR&(1<<TWINT))==0);
  if((TWSR&0xF8)==0x18)ack=1;

}


void i2c_write(unsigned char Data){
  
  if((TWSR&0xF8)==0x18)ack=1;
  
  if(ack){
    TWDR=Data;
    TWCR=(1<<TWINT)|(1<<TWEN);
    while((TWCR&(1<<TWINT))==0);
  }
  
}

void i2c_transmit_str(char str[] )
{
 uint8_t Count;

int siz = strlen(str);
 

  for(Count=0;Count<=siz;Count++ )
  {
    i2c_write(str[Count]);
  
  }
}


void i2c_stop()

{
  TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
  while(TWCR&(1<<TWSTO)); // wait until the twint bit to clear
  ack=0;

}



void i2c_init()
{

	TWBR = 0x48;	  	       // --- Baud rate is set by calculating the of TWBR see Details for Reference

}


