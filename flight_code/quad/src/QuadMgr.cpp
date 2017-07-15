//
// Created by jesse on 2/15/17.
//

extern "C" {
#include <avr/interrupt.h>
#include <avr/io.h> // TODO remove when done
#include <util/delay.h>
}

#include "QuadMgr.h"
#include "MPU6050.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Timer3.h"
#include "Timer5.h"

Quad::QuadMgr::QuadMgr() :
    ledMgr( led::LedMgr::reference() ),
    commsMgr( comms::CommsMgr::reference() ),
    quadState( Quad::QuadState::reference() ),
    interruptMgr( Quad::InterruptMgr::reference() ),
    eepromMgr( Eeprom::EepromMgr::reference() ),
    timer3_( timer::Timer3() ),
    timer5_( timer::Timer5() ),
    ground_( ground::Ground::reference() ),
    mpu( MPU6050(ground_) )
{
    timer::setMillisTimer(timer5_);

	_delay_ms(1000);
    //sei();
}

void Quad::QuadMgr::start()
{
    bool dmpReady = false;  // set true if DMP init was successful
    uint8_t mpuIntStatus = 0;   // holds actual interrupt status byte from MPU
    uint8_t devStatus = 0;      // return status after each device operation (0 = success, !0 = error)
    uint16_t packetSize = 0;    // expected DMP packet size (default is 42 bytes)

    ledMgr.toggle(led::BLUE);

    ground_.sendString("Testing");
    ground_.test();
    ground_.sendString("Done Testing");

    _delay_ms(1000);
    ledMgr.toggle(led::BLUE);

    mpu.initialize();

    // verify connection
    ground_.sendString("Testing device connections...");
    ground_.sendString(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    //mpu.setXGyroOffset(220);
    //mpu.setYGyroOffset(76);
    //mpu.setZGyroOffset(-85);
    //mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        Serial.println("Enabling DMP...");
        mpu.setDMPEnabled(true);

        // enable Arduino interrupt detection
        Serial.println("Enabling interrupt detection (Arduino external interrupt 0)...");
        //attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        Serial.println("DMP ready! Waiting for first interrupt...");
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        Serial.print("DMP Initialization failed (code ");
        Serial.print(devStatus, DEC);
        Serial.println(")");
    }

    ground_.sendByte(mpuIntStatus);
    ground_.sendByte(dmpReady);
    ground_.sendWord(packetSize);

//    timer::Timer5 timer5;
//
//    timer5.setNormalMode();
//    timer5.disableOutputCompare();
//    timer5.setPrescaler(timer::PRESCALE256);
//
//    //I2C i2c(ground_, timer5);
//    //uint8_t response = i2c.read(0x68, 0x75, 1);
//    uint8_t data[10];
//    int8_t response = I2Cdev::readByte(0x68, 0x75, data);
//    ground_.sendString("Reading 0x75 from 0x68. Response:");
//    ground_.sendByte(response);
//
//   if (response > 0) {
//        for (int8_t i = 0; i < response; i++) {
//            ground_.sendString("Received");
//            ground_.sendByte(data[i]);
//        }
//    }
    //i2c.scan();

    //twiMgr.writeByte(0x68, 0x6B, 1);

    ledMgr.toggle(led::RED);

    // loop
    loop();
}

void Quad::QuadMgr::loop() {
//    do {
//        interruptMgr.pollInterupts();
//
//        // Processesing to be done at 20Hz.
//        // TODO add error for if we are taking too long
//        if( quadState.getstate( MainProcessesing ) )
//        {
//            // need to move stuff here after debugging
//            if( quadState.received() )
//            {
//                uint8_t d = commsMgr.getChar();
//                commsMgr.putChar(d);
//                quadState.unset( State::ReceivedMsg );
//            }
//
//            quadState.unset(MainProcessesing);
//        }
//
//        if( quadState.getstate( OneHzTimer ) )
//        {
//            ledMgr.toggle( led::RED );
//            quadState.unset(OneHzTimer);
//        }
//
//        if( quadState.abort() )
//        {
//            // de-init
//            break;
//        }
//    } while (true);
}
