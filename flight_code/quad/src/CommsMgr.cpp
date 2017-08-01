//
// Created by jesse on 2/14/17.
//

#include "CommsMgr.h"

extern "C" {
#include <avr/io.h>
}

#include "ArduinoWrapper.h"
using namespace serial;

comms::CommsMgr::CommsMgr() : buffer_()
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

void comms::CommsMgr::putChar(uint8_t byte)
{
    while ((UCSR0A & (1 << UDRE0)) == 0);	// Wait for empty buffer TODO need timeout
    UDR0 = byte; /* USART I/O Data Register */
}

comms::CommsMgr &comms::CommsMgr::reference()
{
    static comms::CommsMgr ref;
    return ref;
}

uint8_t comms::CommsMgr::getChar(void)
{
    while ((UCSR0A & (1 << RXC0)) == 0);	// Wait for empty buffer TODO need timeout
    uint8_t byte = (uint8_t) UDR0;
    return byte;
}

bool comms::CommsMgr::received()
{
    return (UCSR0A & (1 << RXC0)) != 0; // receive complete flag in UART0 controller & status register A
}

void comms::CommsMgr::sendMessage(const uint8_t* data, uint8_t nData)
{
    for (uint8_t i = 0; i < nData; i++) {
        putChar(data[i]);
    }

    putChar( getChecksum(data, nData) );
}

uint8_t comms::CommsMgr::getChecksum(const uint8_t* data, uint8_t nData)
{
    uint8_t checksum = 0;
    for (uint8_t i = 0; i < nData; i++)
    {
        checksum += data[i];
    }
    return ~checksum;
}

uint8_t comms::CommsMgr::getMessage(uint8_t* data, uint8_t timeout)
{
    uint8_t nBytes = 0; // Total bytes received
    uint8_t nData = 0;  // Number of data bytes received

    uint8_t c = getChar();
    buffer_[0] = c;
    nBytes += 1;
    Serial.print("Received:");
    Serial.print(buffer_[0], HEX);

    switch (c) {
        case UPLINK_HEADER:
            nData = getChar();
            buffer_[1] = nData;
            nBytes += 1 + nData; // 1 for the nData byte + nData
            Serial.print("Received:");
            Serial.print(buffer_[1], HEX);
            break;
        default:
            break;
    }

    for (uint8_t i = 0; i < nData; i++) {
        buffer_[i+2] = getChar();
        Serial.print("Received:");
        Serial.print(buffer_[i+2], HEX);
    }

    uint8_t checksum = getChar();

    if (checksum == getChecksum(buffer_, nBytes)) {
        //Serial.print("Received data!");
        //Serial.print(buffer_[2], HEX);
        // Transfer from buffer_ to data
        for (uint8_t i = 0; i < nBytes; i++) {
            data[i] = buffer_[i];
        }
    }
    else {
        Serial.print("Failed checksum");
        Serial.print(checksum, HEX);
    }

    return nBytes;
}

