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

struct data {
  int8_t roll;
  int8_t pitch;
  int8_t yaw;
} data_t;

char rxBuffer[RX_BUFFER_SIZE];
uint8_t rxReadPos = 0;
uint8_t rxWritePos = 0;

char getChar(void);

int main( void )
{
  INIT_LEDS;

  BLINK(RED);

  _delay_ms(1000);

  usart_comm_init();

  _delay_ms(1000);

  //comms_init(); TODO This does nothing but blink lights

	sei();									  /* enable global interrupts */
	//init_pulse();
  LED_ON(BLUE);

  while (1)
  {
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
  //A_OFF;
  //_delay_ms(500);
//  char i = (char) UDR0;
  put_char(UDR0);
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
