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

#include "comm.h"
#include "DCM.h"
#include "led.h"
#include "MPU6050.h"
#include "PID.h"
#include "twi_master.h"
#include "usart.h"

#define CUT_OFF_PWM 120

#define T_SAMPLE 10
const int T_CNT = T_SAMPLE * 1000L/64.0;  // Number count temp2.  1 Count Temp1 64us => T_sample = Value_CNT1 = ms/64us
int vch3_zero = 0;

struct data {
  int8_t roll;
  int8_t pitch;
  int8_t yaw;
} data_t;

volatile uint8_t rx = 0;
volatile uint8_t tx = 0;
volatile uint8_t can_tx = 0;
volatile int8_t received = 0;

unsigned char t_sample;                  // Save TCNT2 for sample timer

void timer2_init(void);

int main( void ) // TODO write a test that read 4 - 5 bytes with a blocking statment
// before you start reading, start a timer, read the bytes, stop the timer, send the time back or 
// write to EEPROM. i want to see if thats feasible to read them all in a row
{
  double vch1, vch2, vch4;          // Remapped channels from volatile int  
  int vch3;                  // Remapped channel form volatile int  

  int outpitch = 0;              // Out regulator PID control Motor Pitch    
  int outroll = 0;              // Out regulator PID control Motor Roll
  int outyaw = 0;                // Out regulator PID control Motor Yaw

  // Pitch (Inclination)                      
  double up = 0;                // Array process input u(k)
  double spp = 0;                // Set point process sp(k)
  double ypp[2] = {0};            // Array process out yp(k), yp(k-1)
  double iterm_p = 0;              // Integer terminus balancer  
      
  // Roll (Alabeo)  
  double ur = 0;                // Array process input u(k)
  double spr = 0;                // Set point process sp(k)
  double yrp[2] = {0};            // Array process out yp(k), yp(k-1)
  double iterm_r = 0;              // Integer terminus balancer
  
  // Yaw
  double uy = 0;                // Array process input u(k)
  double spy = 0;                // Set point process sp(k)
  double yyp[2] = {0};            // Array process out yp(k), yp(k-1)
  double iterm_y = 0;              // Integer terminus balancer

  INIT_LEDS;

  _delay_ms(3000);

  cli();
  usart_comm_init();
  TWI_Master_Initialise();

  timer2_init();            // Initialize timer2 for time system by 64us  
  sei();                    /* enable global interrupts */
  imu_init();
  // read mpu address
  int addr = 0x42;
  TWI_Read(MPU6050_RA_WHO_AM_I, &addr, 1);						// Gyro meters			
  LINE_START
  put_char(addr);
  LINE_END

  gyro_offset();

  LED_ON(ORANGE);
  _delay_ms(1000);
  LED_OFF(ORANGE);

  while (1)
  {

    if (TCNT2 >= T_CNT)                // Attitude calculates Read IMU (Accel and Gyro) Execute in 2.3ms
    {
      BLINK(BLUE);
      _delay_ms(1000);
      t_sample = TCNT2;                // Catch sample time for integer angle gyro  
      TCNT2 = 0;                    // Restart sample time                                  
      //wdt_reset();                  // Reset watchdog
      sample_meters();                // Samples read IMU
      matrix_update(t_sample, gyro);          // Send t_sample and command yaw for DCM matrix
      normalize();
      drift_correction();                  
      //t_control++;
      euler_angles();

      vch1 = 1500;        // Remap vch[0]. Roll (1). Mapped from 1000 - 2000 to (-42º) - (42º) Centered in (0º)
      vch3 = 1500;                  // Remap vch[1]. Throttle (3)
      vch2 = 1500;        // Remap vch[2]. Pitch (2). Mapped from 1000 - 2000 to (-42º) - (42º) Centered in (0º) 
      vch4 = 1500;    // Remap vch[3]. Yaw (4). Mapped from 1000 - 2000 to -500 - +500

      // PID process Roll process
      spr = vch1;                            // Set point
      yrp[0] = a_result[1];                      // Process out y(k).
      if (vch3 > (CUT_OFF_PWM + vch3_zero)){
        ur = PID(spr, yrp, &iterm_r, KPr, KIr, KDr, OUT_MAX_RP, I_MAX_RP);
      }      
      outroll = ur;
      
      // PID process Pitch process
      spp = vch2;                            // Set point
      ypp[0] = a_result[0];                      // Process out y(k).
      if (vch3 > (CUT_OFF_PWM + vch3_zero)){
        up = PID(spp, ypp, &iterm_p, KPp, KIp, KDp, OUT_MAX_RP, I_MAX_RP);
      }
      outpitch = up;
            
      // PID  Yaw process (Only Giro)            
      if ( (a_result[2] < -30) && (vch4 > 15)) vch4 = 0;          // Limit Command Set Point Yaw
        else if ( (a_result[2] > 30) && (vch4 < 15)) vch4 = 0;  
      if ((vch4 > 15) | (vch4 < -15)) gyro = -(vch4 / 250.0);        // Move direction reference 0 for Set point Yaw Process.                          
        else gyro = 0;                          // Gyro select rate yaw. Reduce constant value for increase rate

      spy = 0;                              // Set point
      yyp[0] = a_result[2];                        // Process out y(k).
      if (vch3 > (CUT_OFF_PWM + vch3_zero)){
        uy = PID(spy, yyp, &iterm_y, KPy, KIy, KDy, OUT_MAX_Y, I_MAX_Y);
      }
      outyaw = uy;

      tx = 1;
      // TODO send imu values to gs
      // try connecting apm to laptop/gs via usb to narrow down issue
      // can test imu program without usart if usb works
    }

    if ( (UCSR0A & (1<<UDRE0)) ) can_tx = 1; // tx buffer empty

    // if ( (UCSR0A & (1<<RXC0)) ) rx = 1; // rx buffer has data
    // 
    // if (rx) // read data received
    // {
    //   received = get_char();
    //   rx = 0;
    //   tx = 1;
    // }

    if (tx && can_tx) // send data
    {
      //put_char('s');
      //put_float(outroll);
      //put_float(outpitch);
      //put_float(outyaw);
      //put_char('e');
      can_tx = 0;
      tx = 0;
    }
  }
}

// Timer count for samples. 1 count = 64us. Max = 256 * 64us = 16ms
void timer2_init(void)
{
  TCCR2A = 0;                        // Normal Mode
  TCCR2B = (1 << CS22) | (1 << CS20) | (1 << CS21);    // Prescaler = 1024 Normal Mode
}
