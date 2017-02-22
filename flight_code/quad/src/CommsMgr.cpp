//
// Created by jesse on 2/14/17.
//

#include "CommsMgr.h"

extern "C" {
#include <avr/io.h>
//#include "clock_speed.h"
}

Comms::CommsMgr::CommsMgr() {
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

void Comms::CommsMgr::putChar(uint8_t byte) {
    while ((UCSR0A & (1 << UDRE0)) == 0);	// Wait for empty buffer
    UDR0 = byte; /* USART I/O Data Register */
}

Comms::CommsMgr &Comms::CommsMgr::reference() {
    static Comms::CommsMgr ref;
    return ref;
}

uint8_t Comms::CommsMgr::getChar(void) {
    uint8_t byte = (uint8_t) UDR0;
    return byte;
}

Comms::Frame Comms::CommsMgr::getFrame(void) {
    return Comms::Frame();
}


