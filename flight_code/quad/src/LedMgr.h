//
// Created by jesse on 2/17/17.
//

#ifndef EEPROM_CMAKE_TEST_LEDMGR_H
#define EEPROM_CMAKE_TEST_LEDMGR_H


namespace LED {

    enum LED {
        RED,
        BLUE,
        YELLOW
    };

    class LedMgr {
        public:
            static LedMgr& reference();
            void toggle(LED);
        private:
            LedMgr();
    };
}


#endif //EEPROM_CMAKE_TEST_LEDMGR_H
