/*
 * main.c
 *
 * Created: 6/7/2016
 *  Author: Jesse
 */
#include <avr/io.h>
#include <avr/interrupt.h>

#include "clock_speed.h"
#include <util/delay.h> /* TODO temporary for debugging */

#include "led.h"
#include "comm.h"

#define RX_BUFFER_SIZE 128

char rxBuffer[RX_BUFFER_SIZE];
uint8_t rxReadPos = 0;
uint8_t rxWritePos = 0;

char getChar(void);

int main( void )
{
  INIT_LEDS;

  blink_c(); /* RED */

  _delay_ms(1000);

  usart_comm_init();
  triple_b();
  _delay_ms(1000);

  //comms_init(); TODO This does nothing but blink lights

	sei();									  /* enable global interrupts */
	//init_pulse();
  A_ON;

  while (1)
  {
    /*char c = getChar();
    blink_c();
    if (c) {
      put_char(c);
    }

    if (c == '1')
    {
      blink_a();
    }
    else if (c == '0')
    {
      blink_b();
    }*/
  }
}

ISR( TIMER5_COMPA_vect )
{
  //blink_a();
	//put_char(ROGER);
}

ISR( USART0_RX_vect )
{
  //blink_a();
  A_OFF;
  _delay_ms(500);
  int i = (int) UDR0;
  put_char(i);
  /*rxBuffer[rxWritePos] = UDR0;

  rxWritePos++;

  if (rxWritePos >= RX_BUFFER_SIZE)
  {
    rxWritePos = 0;
  }*/
}

char peekChar(void)
{
  char ret = '\0';

  if (rxReadPos != rxWritePos)
  {
    ret = rxBuffer[rxReadPos];
  }

  return ret;
}

char getChar(void)
{
  char ret = '\0';

  if (rxReadPos != rxWritePos)
  {
    ret = rxBuffer[rxReadPos];

    rxReadPos++;

    if (rxReadPos >= RX_BUFFER_SIZE)
    {
      rxReadPos = 0;
    }
  }

  return ret;
}
