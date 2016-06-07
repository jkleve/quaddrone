/*
 * led.c
 *
 * Created: 6/6/2016 6:51:07 PM
 *  Author: Jesse
 */ 



/***********************
* Includes
************************/
#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

int main(void)
{
  DDRA = (1 << PA3) | (1 << PA4) | (1 << PA5);

  while (1) {
    PORTA = 0b11011111;
	  _delay_ms(1000);
    PORTA = 0b11111111;
	  _delay_ms(1000);
    PORTA = 0b11101111;
	  _delay_ms(1000);
    PORTA = 0b11111111;
	  _delay_ms(1000);
    PORTA = 0b11110111;
	  _delay_ms(1000);
    PORTA = 0b11111111;
	  _delay_ms(1000);
  }

  return 0;
}
