//
// Created by jesse on 6/30/17.
//

#include "Ground.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ground::Ground::Ground() :
    comms_( comms::CommsMgr::reference() )
{

}

ground::Ground& ground::Ground::reference()
{
    static Ground ref;
    return ref;
}

void ground::Ground::sendRegister(reg::Address reg, uint8_t lowByte, uint8_t highByte)
{
    uint8_t data[REGISTER_MSG_LEN];
    data[0] = REGISTER;
    data[1] = reg;
    data[2] = reg >> 8;
    data[3] = lowByte;
    data[4] = highByte;

    comms_.sendMessage(data, REGISTER_MSG_LEN);
}

void ground::Ground::sendTwiMessage(uint8_t twi_message)
{
    uint8_t data[TWI_MSG_LEN];
    data[0] = TWI_MESSAGE;
    data[1] = twi_message;

    comms_.sendMessage(data, TWI_MSG_LEN);
}

// TODO will I crash if string len is 0?
void ground::Ground::sendString(const char* string)
{
    uint8_t nData = strlen(string);
    uint8_t packetLength = HEADER_LEN + nData + 1;

    // nData + 1 so we can put the string size in the data section of the packet
    uint8_t* packet = (uint8_t*) malloc( sizeof(uint8_t) * packetLength ); // TODO make buffer instead of malloc

    // Copy the header into the packet
    packet[0] = STRING;
    // Copy the size of the packet into data
    packet[1] = nData;

    // Copy the string into the packet
    memcpy( &packet[2],
            string,
            nData );

    comms_.sendMessage(packet, packetLength);

    free(packet);
}

void ground::Ground::sendData(uint8_t *data, uint8_t nData)
{
    uint8_t packetLength = HEADER_LEN + nData + 1; // + 1 so we can put the size in the packet
    buffer_[0] = DATA;
    buffer_[1] = nData;
    for (uint8_t i = 0; i < nData; i++)
    {
        buffer_[i+2] = data[i];
    }

    comms_.sendMessage(buffer_, packetLength);
}

void ground::Ground::sendWord(uint16_t word)
{
    buffer_[0] = WORD;
    buffer_[1] = word;
    buffer_[2] = word >> 8;

    comms_.sendMessage(buffer_, WORD_MSG_LEN);
}

void ground::Ground::sendByte(uint8_t byte)
{
    buffer_[0] = BYTE;
    buffer_[1] = byte;

    comms_.sendMessage(buffer_, BYTE_MSG_LEN);
}

void ground::Ground::send32(uint32_t data)
{
    buffer_[0] = SIZE_32;
    buffer_[1] = data;
    buffer_[2] = data >> 8;
    buffer_[3] = data >> 16;
    buffer_[4] = data >> 24;

    comms_.sendMessage(buffer_, SIZE32_MSG_LEN);
}

void ground::Ground::sendQuaternion(const char* quat)
{
    uint8_t nData = strlen(quat);
    //uint8_t packetLength = HEADER_LEN + nData + 1;

    // nData + 1 so we can put the string size in the data section of the packet
    //uint8_t* packet = (uint8_t*) malloc( sizeof(uint8_t) * packetLength ); // TODO make buffer instead of malloc

    // Copy the header into the packet
    buffer_[0] = QUATERNION;
    // Copy the size of the packet into data
    buffer_[1] = nData;

    // Copy the string into the packet
    memcpy( &buffer_[2],
            quat,
            nData );

    comms_.sendMessage(buffer_, HEADER_LEN + nData + 1);

    //free(packet);
}

ground::Message ground::Ground::getMessage()
{
    uint8_t nBytes = comms_.getMessage(buffer_);
    sendString("Received nBytes:");
    sendByte(nBytes);
    sendString("Received byte:");
    sendByte(buffer_[2]);

    Message message;
    message.msgType = THROTTLE;
    message.data = &buffer_[2];
    message.nData = nBytes;
    return message;
}

void ground::Ground::test()
{
    sendString("Hello World");

    sendString("Sending twi message START");
    sendTwiMessage(0x08);

    sendString("Sending register TWI_CONTROL with value 0");
    sendRegister(reg::TWI_CONTROL, 0x00);

    sendString("Sending data 4 3 2 1");
    uint8_t data[4] = {4, 3, 2, 1};
    sendData(data, 4);

    sendString("Sending word 31250");
    sendWord(31250);

    sendString("Sending empty string");
    sendString("");

    sendString("Sending float number as string");
    char floatString[5] = "test";
    double testFLoat = 3.14;
    sprintf(floatString, "%.2f", testFLoat);
    sendString(floatString);
}

