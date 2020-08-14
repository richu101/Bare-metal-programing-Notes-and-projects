# <span style="color:lightblue"> Basic logical operatation in c </span> 

## <span style="color:"> Bit Shifting ..... __?__ </span>
 
 A bit shift is a bitwise operation where the order of a series of bits is moved, either to the left or right, to efficiently perform a mathematical operation. Bit shifts help with optimization in low-level programming

 ### Bit shift examples:
 * 0b00001110 >> 3
= 0b00000001 ( Three new zeros were added to the left,and the bits on the right just rolled off the edge. )

*  0b00001110 << 2
= 0b00111000 (Two new bits, both zeros, are rolled in from the right.)

# <span style="color:lightblue"> operatations </span>

 * ###  <span style ="color:orange"> OR ( | ) </span>
  
For each bit position, a bitwise OR returns 1 if
either bit in the comparison is 1. OR returns a 1
if this bit is 1 or that bit is 1. OR returns 0 only
when both bits are 0:

> 1010 | 1100
 
> = 1110


* ### <span style ="color:orange"> AND ( & ) <span>
  
  Bitwise AND compares two bits and returns 1 only
if both of the bits are 1. If either of the bits are
0, AND returns 0:

> 1010
& 1100


>= 1000

* ### <span style ="color:orange"> XOR  ( ^ )<span>
  XOR (or “exclusive or”) returns 1 if only one of the
two bits compared is a 1. If both bits are 1 or if
both bits are 0, XOR returns 0:

>1010
^ 1100

>= 0110
* ### <span style ="color:orange"> NOT  ( ~ ) <span>

NOT takes all the bits and flips their logical sense
—each 1 becomes a 0 and each 0 becomes a 1.
It’s also the only logical operator that takes only
one input:

> ~ 1100

>= 0011

# <span style="color:lightblue"> Bit shift Techniques </span> 

## <span style="color:pink"> Using OR to set bits </span> 

```
PORTB : 0b11000011 // the current PORTB state

(1 << 2) = 0b00000100 // current pins we want to turn on

| = 0b11000111

```
>PORTB = PORTB | (1 << 2);

 ### `OR`
 >PORTB | = (1<<2);

 