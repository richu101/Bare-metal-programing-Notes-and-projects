#ifndef __AVR_ATmega328P__ 
    #define __AVR_ATmega328P__
#endif
#define F_CPU 16000000UL

#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include"liberaries/USART_liberry/usart.c"
void init_timer1()
{
    TCCR1B |= (1<<CS11) | (1<<CS10);
    // set the clock speed 16MHz / 64
    // 16/64 tick of the clock will increase the timer value by 1
}

int main(void)          
{   
    char byte;
    uint16_t timerval;
    initUSART();
    init_timer1();
    DDRB = (1<<PB5);
    printString("get ready ..\n");
    while(1)
    {

        printString("get reade .... \n");
        PORTB |= (1<<PB5);
        byte = receiveByte();
        _delay_ms(500);
        PORTB = 0;
        transmitByte(13);
        printString("start noww...");
        TCNT1 = 0;
        if(bit_is_set(PIND,PD2))
        {
            printString("no cheeting..\n    ");
        }
        else
        {   
            loop_until_bit_is_set(PIND,PD2);
            timerval = TCNT1;
            TCNT1 = 0;
            printString("your reaction time id .....");
            printInt(timerval);
            transmitByte(13); // clear the terminal set the curser to 0 th position
        }
        
        
    }
    return (0);

}
