//
// Created by jesse on 2/15/17.
//

extern "C" {
#include <avr/interrupt.h>
#include <avr/io.h> // TODO remove when done
#include <util/delay.h>
}

#include "QuadMgr.h"

Quad::QuadMgr::QuadMgr() :
    ledMgr( LED::LedMgr::reference() ),
    commsMgr( Comms::CommsMgr::reference() ),
    quadState( Quad::QuadState::reference() ),
    interruptMgr( Quad::InterruptMgr::reference() ),
    eepromMgr( Eeprom::EepromMgr::reference() ),
    twiMgr( twi::TwiMgr::reference() ),
	i2cDriver( i2c::AVRI2CDriver() )
{
	_delay_ms(1000);
	//i2cDriver.begin();
    sei();
}

void Quad::QuadMgr::start()
{
	//uint8_t data[10] = { 0 };
	//uint8_t stat = 48;
	//uint8_t timeout = 0;
	//bool err = false;
	//while (stat == 48) {
	//	stat = i2cDriver.readRegister(0x68, 0x75, data);
	//	commsMgr.putChar(stat);
	//	if (timeout++ > 20) {
	//		err = true;
	//		break;
	//	}
	//	_delay_ms(500);
	//}
	//if (err)
	//	commsMgr.putChar(0x11);
	//else {
	//	commsMgr.putChar(stat);
	//	for (int i = 0; i < 10; i++) {
	//		commsMgr.putChar(data[i]);
	//	}
	//}
    //uint8_t addresses[] = {0x68,
    //                                  0x69,
    //                                  0xD0, // 0x68 << 1
    //                                  0xD1, // 0x68 << 1 & 0x01
    //                                  0xD2, // 0x69 << 1
    //                                  0xD3}; // 0x69 << 1 & 0x01
    //uint8_t num_addr = 6;

    ledMgr.toggle(LED::BLUE);
    // give some time for initialization
    _delay_ms(2000);
    ledMgr.toggle(LED::BLUE);

    twiMgr.request_read(0x68, 0x75);

    //// init
    //for (uint8_t i = 0; i < 128U; i++) {
    //    commsMgr.putChar(i);
    //    uint8_t addr = i;
    //    //uint8_t addr = addresses[i];
    //    //commsMgr.putChar(addr);
    //    //twiMgr.i2c_start_wait(addr);
    //    twiMgr.test_read(addr);
    //    //uint8_t res = twiMgr.i2c_start(addr);
    //    //commsMgr.putChar(res);
    //    _delay_ms(100);
    //}
    //twiMgr.request_read(0x69, 0x00);

    // loop
    //loop();
}

void Quad::QuadMgr::loop() {
    do {
        interruptMgr.pollInterupts();

        // Processesing to be done at 20Hz.
        // TODO add error for if we are taking too long
        if( quadState.getstate( MainProcessesing ) )
        {
            // need to move stuff here after debugging
            if( quadState.received() )
            {
                uint8_t d = commsMgr.getChar();
                commsMgr.putChar(d);
                quadState.unset( State::ReceivedMsg );
            }

            quadState.unset(MainProcessesing);
        }

        if( quadState.getstate( OneHzTimer ) )
        {
            ledMgr.toggle( LED::RED );
            quadState.unset(OneHzTimer);
        }

        if( quadState.abort() )
        {
            // de-init
            break;
        }
    } while (true);
}
