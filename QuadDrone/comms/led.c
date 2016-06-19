/*
 * led.c
 *
 * Created: 6/7/2016
 *  Author: Jesse
 */ 
#include <avr/io.h>

#include "clock_speed.h" /* needed for util/delay.h */
#include <util/delay.h>

#include "led.h"

void blink_a( void )
{
  PORTA = 0b11110111;
	_delay_ms(50);
  PORTA = 0b11111111;
}

void blink_b( void )
{
  PORTA = 0b11101111;
	_delay_ms(50);
  PORTA = 0b11111111;
}

void triple_b( void )
{
  PORTA = 0b11101111;
	_delay_ms(50);
  PORTA = 0b11111111;
	_delay_ms(50);
  PORTA = 0b11101111;
	_delay_ms(50);
  PORTA = 0b11111111;
	_delay_ms(50);
  PORTA = 0b11101111;
	_delay_ms(50);
  PORTA = 0b11111111;
}

void blink_c( void )
{
  PORTA = 0b11011111;
	_delay_ms(50);
  PORTA = 0b11111111;
}

void comms_init( void )
{
  PORTA = 0b11011111;
	_delay_ms(200);
  PORTA = 0b11001111;
	_delay_ms(200);
  PORTA = 0b11100111;
	_delay_ms(200);
  PORTA = 0b11110111;
	_delay_ms(200);
  PORTA = 0b11111111;
}
