/*
 * main.c
 *
 * Created: 6/7/2016
 *  Author: Jesse
 *
 *-----------------------------------------------------------
 * APM 2.6
 *
 *  Connecting to APM 2.6 via SPI connections
 *
 *    Analog connections on APM 2.6
 *     A0                   A11 SPI
 *    _______________________________
 *    | . . . . . . . . . . . . 1 2 | -    1: MISO 2:  VCC
 *    | . . . . . . . . . . . . 3 4 | +    3:  SCK 4: MOSI
 *    | . . . . . . . . . . . . 5 6 | s    5:  RST 6:  GND
 *    -------------------------------
 *
 *   NOTE: VCC is for SPI connected devices to see voltage.
 *         This does not provide voltage. A 5V supply will
 *         need to be supplied. Connecting battery to BEC
 *         then to APM will do. You may be able to use
 *         EXT PWR on AVR dragon but I have never looked
 *         into this.
 *
 *-----------------------------------------------------------
 * AVR DRAGON
 *
 *  Connection to AVR dragon via SPI connections
 *
 *                    /\
 *                    ||  To PC connection
 *                    ||
 *   |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 *   |                                       |
 *   |                                       |
 *   | EXT PWR                               |
 *   | . . .                                 |
 *   | . . .                                 |
 *   |                                       |
 *   | . . . . .   2 4 6  .................. |
 *   | . . . . .   1 3 5  .................. |
 *   |    JTAG      SPI                      |
 *   | ....................................  |
 *   | ....................................  |
 *   |  O                                O   |
 *   |  ...................................  |
 *   |  ........................             |
 *   |                                       |
 *   |  ........................             |
 *   |  ...................................  |
 *   -----------------------------------------
 *
 *-----------------------------------------------------------
 *  To load hex onto APM:
 *    avrdude -p <mpu> -c <isp> -P <port> -e -v -U flash:w:<name>.hex
 *          <mpu>:  chip on APM (atmega2560)
 *          <isp>:  programmer  (dragon_isp)
 *          <port>: port        (usb)
 *          <name>: name of file/program
 *-----------------------------------------------------------
 */

extern "C" {
#include <avr/io.h>
#include <avr/interrupt.h>

//#include "clock_speed.h"
#include <util/delay.h> /* TODO temporary for debugging */
#include <stdint.h>

//#include "led.h"
//#include "comm.h"
}

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "QuadMgr.h"
//#include "CommsMgr.h"
//#include "QuadState.h"
//#include "Eeprom.h"
//#include "InterruptMgr.h"

//#define RX_BUFFER_SIZE 128

struct data {
  int8_t roll;
  int8_t pitch;
  int8_t yaw;
} data_t;

/*char rxBuffer[RX_BUFFER_SIZE];
uint8_t rxReadPos = 0;
uint8_t rxWritePos = 0;

char getChar(void);*/

volatile uint8_t rx = 0;
volatile uint8_t tx = 0;
volatile uint8_t can_tx = 0;
volatile uint8_t received = 0;
//volatile char transmit = 0;

int main( void ) // TODO write a test that read 4 - 5 bytes with a blocking statment
// before you start reading, start a timer, read the bytes, stop the timer, send the time back or 
// write to EEPROM. i want to see if thats feasible to read them all in a row
{
    //Eeprom::EepromMgr eeprom();

    // Initialize
    sei();
    Quad::QuadMgr quadMgr;
    //Quad::QuadState &quadState = Quad::QuadState::reference();
    //Quad::InterruptMgr &intMgr = Quad::InterruptMgr::reference();
    //Comms::CommsMgr comms;

    // Process loop
    quadMgr.start();
}
//    while( !quadState.abort() )
//    {
//        intMgr.pollInterupts();
//
//        if( quadState.received() )
//        {
//            //uint8_t data = comms.getChar();
//        }
//
//        if( quadState.canTx() )
//        {

        //}
//    }

//  INIT_LEDS;
//
//  usart_comm_init();
//
//  sei();									  /* enable global interrupts */
//
//  LED_ON(ORANGE);
//  _delay_ms(1000);
//  LED_OFF(ORANGE);
//
//  while (1)
//  {
//    if ( (UCSR0A & (1<<UDRE0)) ) can_tx = 1; // tx buffer empty
//
//    if ( (UCSR0A & (1<<RXC0)) ) rx = 1; // rx buffer has data
//
//    if (rx) // read data received
//    {
//      received = (uint8_t) UDR0;
//      rx = 0;
//
//      //transmit = received;
//      tx = 1;
//    }
//
//    if (tx && can_tx) // send data
//    {
//      UDR0 = received;
//      //UDR0 = 42;
//      can_tx = 0;
//      tx = 0;
//    }
//
//
//  }
//}

//ISR( USART0_RX_vect )
//{
//  LED_ON(BLUE);
//  _delay_ms(5000);
//  LED_OFF(BLUE);
//}
/*
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
}*/
