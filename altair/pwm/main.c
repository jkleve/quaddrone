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

//#define RX_BUFFER_SIZE 128

/*char rxBuffer[RX_BUFFER_SIZE];
uint8_t rxReadPos = 0;
uint8_t rxWritePos = 0;

char getChar(void);*/

/* comms */
volatile uint8_t rx = 0;
volatile uint8_t tx = 0;
volatile uint8_t can_tx = 0;
volatile uint8_t received = 0;
volatile int8_t motor_val = 0;

int main( void )
{
  INIT_LEDS;

  usart_comm_init();
	sei();									  /* enable global interrupts */

  /* PWM */
  DDRE = (1 << DDE3); // set PE3 as output

  /* 
   * Fast PWM, 8-bit: Mode 14 pg. 145
   *  WGM33:0 0b1110
   * Compare Output Mode: Clear OC3Aon compare, set at BOTTOM pg. 155
   *  COM3A1:0 0b10
    */

  /* Timer/Counter 3 Control Register A */
  TCCR3A = (1 << COM3A1) | (0 << COM3A0) |
           (0 << COM3B1) | (0 << COM3B0) |
           (0 << COM3C1) | (0 << COM3C0) |
           (1 << WGM31)  | (0 << WGM30);

  /* Timer/Counter 3 Control Register B 
   *  No prescaler on clock pg. 157
   *   CS32:0 0b001                       */
  TCCR3B =  (0 << ICNC1) | (0 << ICES1) |
            (1 << WGM33) | (1 << WGM32);
  /* Timer/Counter 3 Interrupt Mask Register
   *  enable Timer/Counter, Overflow Interrupt pg. 162
   *   TOIE3 0b1 */
  TIMSK3 = (1 << TOIE3);
  ICR3 = 19999; // 50 Hz
  //OCR3A = 17999; // 100 %
  OCR3A = 1999; // 100% ?? (note: not 100% sure on that)

  TCCR3B |= (0 << CS32) | (1 << CS31) | (0 << CS30); // set prescaler clk/8 0b010 pg. 157, starting clock

  BLINK(RED); /* INITIALIZED */

  while (1)
  {
    if ( (UCSR0A & (1<<UDRE0)) ) can_tx = 1; // tx buffer empty

    if ( (UCSR0A & (1<<RXC0)) ) rx = 1; // rx buffer has data
    
    if (rx) // read data received
    {
      if (UCSR0A & (1<<FE0)) BLINK(BLUE); // added to show errors
      if (UCSR0A & (1<<DOR0)) BLINK(ORANGE); // added to show overrun errors
      received = (int8_t) UDR0;
      rx = 0;
      tx = 1;

      /* update pwm */
      motor_val = -1*(received+1)*4;
      OCR3A = 1200 + (motor_val*10);
      //OCR3A = 18999 - (received*10);
    }

    if (tx && can_tx) // send data
    {
      //UDR0 = (received>>8);
      //while ( !(UCSR0A & (1<<TXC0)) ); // TODO changed
      UDR0 = (motor_val/-4)-1;
//      UDR0 = 0b00000001;
      can_tx = 0;
      tx = 0;
    }
  }

  return 0;
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
//  blink_b();
  //duty_cycle = (int) UDR0;
  //OCR3A = (int)((duty_cycle/100.0)*255); // TODO are we sure writing floats into OCR3A works?
                                  // TCNT increments by 1 so shouldn't it be an int?
  int r = (int) UDR0;
  LED_ON(RED);
  _delay_ms(10000);
  //OCR3A = (int)((r/100.0)*255);
  put_char(r);
  //BLINK(BLUE);
  /*rxBuffer[rxWritePos] = UDR0;

  rxWritePos++;

  if (rxWritePos >= RX_BUFFER_SIZE)
  {
    rxWritePos = 0;
  }*/
}

/*char peekChar(void)
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
}*/
