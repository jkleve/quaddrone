#include <avr/io.h>
#include <avr/interrupt.h>

#include "clock_speed.h"
#include <util/delay.h>

#include "comm.h"
#include "led.h"
#include "MPU6050.h"
#include "twi_master.h"
#include "usart.h"

int main (void)
{
    int i;
    INIT_LEDS;

    _delay_ms(3000);
    
    cli();
    usart_comm_init();
    TWI_Master_Initialise();
    
    sei();                    /* enable global interrupts */
    imu_init();

    // read mpu address
    int addr = 0x42;
    TWI_Read(MPU6050_RA_WHO_AM_I, &addr, 1);

    LINE_START
    put_char(addr);
    LINE_END

    for (i = 0; i < 127; i++)
    {
        
    } 

    return 0;
}
