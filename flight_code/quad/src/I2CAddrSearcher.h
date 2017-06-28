extern "C" {
#include <avr/io.h>
}

#include <stdint.h>
#include "I2CDriver.h"

namespace test {

    struct I2CMatches {
        uint8_t nMatches;
        uint8_t addresses[127];
    };

    class I2CAddrSearcher {
    public:
        I2CAddrSearcher();
        I2CMatches search();
    private:
        i2c::AVRI2CDriver i2cDriver;
    };
}
