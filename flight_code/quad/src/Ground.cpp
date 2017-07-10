//
// Created by jesse on 6/30/17.
//

#include "Ground.h"

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

void ground::Ground::sendRegister(reg::Address reg, uint8_t value)
{
    uint8_t data[REGISTER_MSG_LEN];
    data[0] = REGISTER;
    data[1] = reg;
    data[2] = value;

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

void ground::Ground::test()
{
    sendString("Hello World");
    sendTwiMessage(0x08);
    sendRegister(reg::TWI_CONTROL, 0x00);
}
