/*
 * quad.c
 *
 * Created: 10/14/2015 8:04:31 PM
 * Author : sport
 */ 

/***********************
* Includes
************************/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "macros.h"
#include "functions.h"
#include "uart.h"
#include "communication.h"

#define STEP_C 67
//int volatile pre_step_c = 1;

#include <avr/io.h>

int main(void)
{
    usart_comm_init();	// timer5: initialize usart0 for communication w/ gs
	//put_char(0x30);
	sei();				// enable global interrupts
	//DDRA = (1<<PA3) | (1<<PA4) | (1<<PA5); /* initialize ABC lights */
	//PORTA = 0b11000111;
	//while (pre_step_c);
	//_delay_ms(1000);
	//PORTA = 0b11111111;
	init_pulse();		// start pulsing @ 1/2 Hz
	
	
	//lights_slow();
	
	while(0)
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
