/*
 * communication.h
 *
 * Created: 8/16/2015 8:27:55 PM
 *  Author: Jesse
 */ 

#include <avr/interrupt.h>

#ifndef COMMUNICATION_H_
# define COMMUNICATION_H_

# ifndef F_CPU
#  define F_CPU 16000000UL		// Define Clock AVR
# endif

# define USART_BAUD	38400UL		// Define Baud rate

# define PULSE 0x30 // heartbeat
# define ROGER 0x31 // copy that

void usart_comm_init(void);
void init_pulse(void);
int put_char(int);	// Tx character char

#endif /* COMMUNICATION_H_ */