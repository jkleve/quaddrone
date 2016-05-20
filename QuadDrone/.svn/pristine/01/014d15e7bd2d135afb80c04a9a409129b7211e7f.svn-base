/*
 * QuadDrone.c
 *
 * Created: 8/15/2015 6:51:07 PM
 *  Author: Jesse
 */ 



/***********************
* Includes
************************/
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

#include "macros.h"
#include "functions.h"
#include "uart.h"
#include "communication.h"

#define STEP_C 67
//int volatile pre_step_c = 1;

int main(void)
{
	usart_comm_init();	// timer5: initialize usart0 for communication w/ gs
	put_char(0x30);
	sei();				// enable global interrupts
	//DDRA = (1<<PA3) | (1<<PA4) | (1<<PA5); /* initialize ABC lights */
	//PORTA = 0b11011111;
	//while (pre_step_c);
	//PORTA = 0b11111111;
	init_pulse();		// start pulsing @ 1/2 Hz
	
	
	//lights_slow();
	
	while(1)
	{
		
		//OCR1B += 10;
		//OCR1A += 10;
		/*if (OCR1B > 255) {
			OCR1B = 10;
			OCR1A = 10;
		}*/
	}
	
	return 0;
}

/*******************************
* Interrupt Handling
********************************/

/* pulse */
ISR(TIMER5_COMPA_vect)
{
	put_char(0x30);
}

/* received rx transmission */
ISR(USART0_RX_vect)
{
	//PORTA = 0b11101111;
	int rec = get_char();
	switch (rec)
	{
		case ARM_C:
			put_char(ARM);
			break;
		case CONNECT_C:
			/*if (pre_step_c) { // if pre c, send roger and go past pre c. otherwise ignore.
				put_char(ROGER);
				pre_step_c = 0;
			} else {
				// make comm macro for DENY
			}*/
			break;
		default:
			put_char(rec);
			break;
	}
}

/* timer 1 overflow vector */
/*ISR(TIMER1_OVF_vect)
{
	//OCR1A = 0xF0;
	PORTA = 0x00;
	//OCR1B += 1;
}*/