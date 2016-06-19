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

int duty_cycle = 0; // TODO int or double ??

int main( void )
{
  INIT_LEDS;

  blink_c(); /* RED */

  _delay_ms(1000);

  usart_comm_init();
  triple_b();
  _delay_ms(1000);

  //comms_init(); TODO This does nothing but blink lights

  A_ON;
  _delay_ms(500);
	sei();									  /* enable global interrupts */
  A_OFF;
  triple_b();

  /* PWM */
  DDRE = (1 << DDE3); // set PE3 as output
  //PORTE = (1 << PE3) // enable pull-up resistor

  /* 
   * Fast PWM, 8-bit: Mode 5 pg. 145
   *  WGM33:0 0b0101
   * Compare Output Mode: Clear OC3Aon compare, set at BOTTOM pg. 155
   *  COM3A1:0 0b10
    */

  /* Timer/Counter 3 Control Register A */
  TCCR3A = (1 << COM3A1) | (0 << COM3A0) |
           (0 << COM3B1) | (0 << COM3B0) |
           (0 << COM3C1) | (0 << COM3C0) |
           (0 << WGM31)  | (0 << WGM31);

  /* Timer/Counter 3 Control Register B 
   *  No prescaler on clock pg. 157
   *   CS32:0 0b001                       */
  TCCR3B =  (0 << ICNC1) | (0 << ICES1) |
            (0 << WGM33) | (1 << WGM32);
  /* Timer/Counter 3 Interrupt Mask Register
   *  enable Timer/Counter, Overflow Interrupt pg. 162
   *   TOIE3 0b1 */
  TIMSK3 = (1 << TOIE3);
  OCR3A = (duty_cycle/100.0)*255;

  C_ON;

  TCCR3B |= (0 << CS32) | (0 << CS31) | (1 << CS30); // set prescaler, starting clock


  while (1)
  {

  }
}

ISR(TIMER3_OVF_vect)
{
  // timer 3 overflow isr
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
  _delay_ms(500);
  duty_cycle = (int) UDR0;
  OCR3A = (duty_cycle/100.0)*255; // TODO are we sure writing floats into OCR3A works?
                                  // TCNT increments by 1 so shouldn't it be an int?
  put_char(duty_cycle);
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
