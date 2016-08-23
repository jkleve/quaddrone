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
#include "twi_master.h"

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

unsigned char t_sample;                  // Save TCNT2 for sample timer

void timer2_init();

int main( void ) // TODO write a test that read 4 - 5 bytes with a blocking statment
// before you start reading, start a timer, read the bytes, stop the timer, send the time back or 
// write to EEPROM. i want to see if thats feasible to read them all in a row
{
  INIT_LEDS;

  cli();
  usart_comm_init();
  TWI_Master_Initialise();
  timer2_init();            // Initialize timer2 for time system by 64us  
  sei();                    /* enable global interrupts */
  imu_init();

  LED_ON(ORANGE);
  _delay_ms(1000);
  LED_OFF(ORANGE);

  while (1)
  {

    if (TCNT2 >= T_CNT){                // Attitude calculates Read IMU (Accel and Gyro) Execute in 2.3ms              
      t_sample = TCNT2;                // Catch sample time for integer angle gyro  
      TCNT2 = 0;                    // Restart sample time                                  
      wdt_reset();                  // Reset watchdog
      sample_meters();                // Samples read IMU
      matrix_update(t_sample, gyro);          // Send t_sample and command yaw for DCM matrix
      normalize();
      drift_correction();                  
      t_control++;  
    if ( (UCSR0A & (1<<UDRE0)) ) can_tx = 1; // tx buffer empty

    if ( (UCSR0A & (1<<RXC0)) ) rx = 1; // rx buffer has data
    
    if (rx) // read data received
    {
      received = (uint8_t) UDR0;
      rx = 0;

      //transmit = received;
      tx = 1;
    }

    if (tx && can_tx) // send data
    {
      UDR0 = received;
      //UDR0 = 42;
      can_tx = 0;
      tx = 0;
    }
  }
}

// Timer count for samples. 1 count = 64us. Max = 256 * 64us = 16ms
void timer2_init(){
  TCCR2A = 0;                        // Normal Mode
  TCCR2B = (1 << CS22) | (1 << CS20) | (1 << CS21);    // Prescaler = 1024 Normal Mode
}
