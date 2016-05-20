/*
 * USART_Test.c
 *
 * Created: 8/16/2015 5:18:43 PM
 *  Author: Jesse
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>
//#include "usart.h"			
#include "communication.h" // messages & comm initialization

int main()
{
	usart_comm_init();
	
	sei();									  /* enable global interrupts */
	//init_pulse();
    while(1)
    {
        //TODO:: Please write your application code 
    }
}

ISR(TIMER5_COMPA_vect)
{
	put_char(0x30);
}