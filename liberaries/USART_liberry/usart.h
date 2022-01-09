/* Functions to initialize, send, receive over USART

   initUSART requires BAUD to be defined in order to calculate
     the bit-rate multiplier.
 */

#ifndef BAUD                          /* if not defined in Makefile... */
#define BAUD  9600                     /* set a safe default baud rate */
#endif

                                  /* These are defined for convenience */
#define   USART_HAS_DATA   bit_is_set(UCSR0A, RXC0)
#define   USART_READY      bit_is_set(UCSR0A, UDRE0)




/* Takes the defined BAUD and F_CPU,
   calculates the bit-clock multiplier,
   and configures the hardware USART                   */
void serialbegin();
/* Blocking transmit and receive functions.
   When you call receiveByte() your program will hang until
   data comes through.  We'll improve on this later. */
void transmitByte(uint8_t data);
 // transmitt 8 bit value through usart
uint8_t receiveByte(void);
// recieve 8 bit value from usart

void printString(const char myString[]);
             /* Utility function to transmit an entire string from RAM */
const char* readString(uint8_t maxLength);
/* Define a string variable, pass it to this function
   The string will contain whatever you typed over serial */

void printInt(uint16_t num);

// print numbers using usart ( 16 bit value maximun )
