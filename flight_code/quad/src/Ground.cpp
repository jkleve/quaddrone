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

void ground::Ground::sendRegister(registers::Address reg, uint8_t value)
{
    Message message;
    message.msgType = REGISTER;

    uint8_t data[2];
    data[0] = reg;
    data[1] = value;
    message.data = data;

    message.nData = 2;

    comms_.sendMessage(message);
}

void ground::Ground::sendTwiMessage(uint8_t twi_message)
{
    Message message;
    message.msgType = TWI_MESSAGE;

    uint8_t data[1];
    data[0] = twi_message;
    message.data = data;

    message.nData = 1;

    comms_.sendMessage(message);
}

void ground::Ground::sendString(const char* string)
{
    Message message;
    message.msgType = STRING;

    message.nData = strlen(string);

    uint8_t* data = (uint8_t*) malloc( sizeof(uint8_t) );

    message.data = (uint8_t*) memcpy( data,
                                      string,
                                      sizeof(data[0]) * message.nData );

    comms_.sendMessage(message);

    free(data);
}
