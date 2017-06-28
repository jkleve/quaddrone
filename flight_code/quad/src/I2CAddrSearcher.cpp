extern "C" {
#include <avr/io.h>
}

#include "I2CAddrSearcher.h"

test::I2CAddrSearcher::I2CAddrSearcher() :
    i2cDriver( i2c::AVRI2CDriver() )
{
    // init
}

test::I2CMatches test::I2CAddrSearcher::search()
{
    uint8_t data[10];
    for (int i = 0; i < 128; i++) {
        // ping each address
        i2cDriver.begin();
        i2cDriver.readRegister(i, 0x75, data);
    }

    return test::I2CMatches();
}
