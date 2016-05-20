/*
 * communication.h
 *
 * Created: 8/16/2015 8:27:55 PM
 *  Author: Jesse
 */ 

#ifndef COMMUNICATION_H_
# define COMMUNICATION_H_

# ifndef F_CPU
#  define F_CPU 16000000UL		// Define Clock AVR
# endif

# define USART_BAUD	57600UL		// Define Baud rate 38400

# define PULSE 0x30 // heartbeat
# define ROGER 0x31 // copy that

# define ARM     0x61 // arm
//# define CONNECT 0x43 // connect

/* incoming message codes */
# define ARM_C		65 // arm input from ground station (gs)
# define CONNECT_C  67

void usart_comm_init(void);
void init_pulse(void);
int put_char(int);	// Tx character char
int get_char(void); // Rx character char

#endif /* COMMUNICATION_H_ */