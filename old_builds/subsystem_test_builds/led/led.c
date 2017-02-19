/*
 * led.c
 *
 * Created: 6/6/2016
 *  Author: Jesse
 */ 



/***********************
* Includes
0b11111111
0b11101111

0b01111111
0b11101111 & (turn on)
0b01101111

0b01111111 PORTA
0b11101111 | (0x08) (turn off)

************************/
#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

#include "led.h"

int main(void)
{
  DDRA = (1 << DDA3) | (1 << DDA4) | (1 << DDA5); // set as outputs
  //PORTA = (1 << PA3) | (1 << PA4) | (1 << PA5);   // port pin is driven high
//  PORTA = (1 << PA3);
  PORTA = 0xFF;
  PORTA &= ~(0x20); // turns on
  //PORTA = (1 << PA3);
//  PORTA = 0b11110111;

//  _delay_ms(1000);

  while(1) {
    _delay_ms(1000);
    PORTA |= (0x20);
    //PINA = (0 << PINA3);
  }

  return 0;
}
