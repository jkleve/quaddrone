//
// Created by jesse on 2/13/17.
//

#ifndef COMMS_EEPROM_H
#define COMMS_EEPROM_H

#include <stdint.h>

namespace Eeprom {
    class EepromMgr {
        public:
            static EepromMgr& reference();
            void write(uint8_t);
        private:
            EepromMgr();
            uint8_t writeAddress;
            uint8_t writeData;
    };
}


#endif //COMMS_EEPROM_H
