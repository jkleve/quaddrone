/*
 * communication.c
 *
 * Created: 8/16/2015 8:27:46 PM
 *  Author: Jesse
 */ 

#include <avr/io.h>
#include "communication.h"

void usart_comm_init(void)
{	
	/* Asynchronous USART (UMSEL01 & UMSEL00 = 0)				  *
	 * Parity Mode disabled (UPM01 & UPM00 = 0)					  *
	 * stop bits: 1-bit (USBS0 = 0)								  *
	 * Character size: 8-bit (UCSZ02 = 0, UCSZ01 = 1, UCSZ00 = 1) */
	UCSR0A |= (1 << U2X0);							// double speed
	UBRR0 = F_CPU / (8 * USART_BAUD) - 1;			// calc ubrr0
	//UBRR0 = 51; // see table 22-12
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);		// Format 8N1 Asynchronous	
	UCSR0B |= (1 << RXEN0) |  (1 << TXEN0);			// init transmission	
	UCSR0B |= (1 << RXCIE0);						// init RX Complete Interrupt Enable
	//fdevopen((int (*)(char, FILE*))put_char, (int (*)(FILE*))get_char);		// For use with printf and scanf	
}

// must have global interrupts enabled
void init_pulse(void)
{
	/* --- TIMER --- */
	TCCR5B = (1 << WGM52);					  /* Set CTC bit */
	OCR5A = 31250;							  /* trigger interrupt when tcnt = ocr 31250 = 2 sec  15625 = 1 sec */
	TIMSK5 |= (1 << OCIE5A);				  /* enable Output Compare A Match Interrupt */
	TCCR5B |= (1 << CS02) | (1 << CS00);	  /* Prescale mode: 5 (clk/1024) CS52 = 1 CS51 = 0 CS50 = 1 */
	
}

// TX data char through USART
int put_char (int dato){
	while ((UCSR0A & (1 << UDRE0)) == 0);	// Wait for empty buffer
	UDR0 = dato;
	return dato;
}

// Rx data char through USART
int get_char(void){
	int dato;
	while ((UCSR0A & (1<<RXC0)) == 0 );		// Wait for data in buffer
	dato = UDR0;
	return dato;
}