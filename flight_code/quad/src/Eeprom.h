//
// Created by jesse on 2/13/17.
//

#ifndef COMMS_EEPROM_H
#define COMMS_EEPROM_H

namespace Eeprom {
    class EepromMgr {
        EepromMgr();

        ~EepromMgr();

        void write(char *d);
    };
}


#endif //COMMS_EEPROM_H
