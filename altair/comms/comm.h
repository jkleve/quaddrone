/*
 * communication.h
 *
 * Created: 8/16/2015 8:27:55 PM
 *  Author: Jesse
 */ 

#include <avr/interrupt.h>

#ifndef COMM_H
# define COMM_H

# define USART_BAUD	38400UL		// Define Baud rate

# define PULSE 0x30 // heartbeat
# define ROGER 0x31 // copy that

void usart_comm_init( void );
void init_pulse( void );
int put_char( int );	// Tx character char

#endif /* COMM_H */
