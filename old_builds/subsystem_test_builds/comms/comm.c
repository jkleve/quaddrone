/*
 * communication.c
 *
 * Created: 8/16/2015
 *  Author: Jesse
 */ 

#include <avr/io.h>
#include "clock_speed.h"
#include "comm.h"

void usart_comm_init( void )
{	
	/* Asynchronous USART (UMSEL01 & UMSEL00 = 0)				  *
	 * Parity Mode disabled (UPM01 & UPM00 = 0)					  *
	 * stop bits: 1-bit (USBS0 = 0)								  *
	 * Character size: 8-bit (UCSZ02 = 0, UCSZ01 = 1, UCSZ00 = 1) */

  /* USART Control and Status Register A pg. 219         *
   * setting U2X0 to 1 enables double speed.             *
   * see pg. 223 for error in baud rate and double speed */
	UCSR0A |= (1 << U2X0);

  /* USART Control and Status Register B pg. 220  *
   * ***disabled temporarily to try using RXCn.*** enable RX Complete Interrupt Enable (RXCIE0) *
   * enable Receiver Enable (RXEN0)               *
   * enable Transmitter Enable (TXEN0)            */
	UCSR0B |= (0 << RXCIE0) | (0 << TXCIE0) | (0 << UDRIE0) | (1 << RXEN0) |
            (1 << TXEN0)  | (0 << UCSZ02) | (0 << TXB80);

	/* USART Control and Status Register C  *
   * Format 8N1 Asynchronous pg. 222      */
	UCSR0C = (0 << UMSEL01) | (0 << UMSEL00) | (0 << UPM01)  | (0 << UPM00) | 
           (0 << USBS0)   | (1 << UCSZ01)  | (1 << UCSZ00) | (0 << UCPOL0);

  /* USART Baud Rate Register pg. 222 *
   * see pg. 203 for the formula      */
	UBRR0 = F_CPU / (8 * USART_BAUD) - 1;
}

/* must have global interrupts enabled */
void init_pulse( void )
{
	/* --- TIMER --- */
	TCCR5B = (1 << WGM52);               /* Set CTC bit (Clear timer on compare) */
  OCR5A = 976;
	//OCR5A = 31250;                     /* trigger interrupt when tcnt = ocr 31250 = 2 sec  15625 = 1 sec */
	TIMSK5 |= (1 << OCIE5A);             /* enable Output Compare A Match Interrupt */
	TCCR5B |= (1 << CS52) | (1 << CS50); /* Prescale mode: 5 (clk/1024) CS52 = 1 CS51 = 0 CS50 = 1 */
  /* page 156. ICNC5 ICES5 - WGM53 WGM52 CS52 CS51 CS50 */
}

/* TX data char through USART */
/* TODO should we check if the RX/TX register is empty first? */
int put_char ( int dato ){
	while ((UCSR0A & (1 << UDRE0)) == 0);	// Wait for empty buffer
	UDR0 = dato; /* USART I/O Data Register */
	return dato;
}
