/*
 * main.c
 *
 * Created: 6/7/2016
 *  Author: Jesse
 *
 *-----------------------------------------------------------
 * APM 2.6
 *
 *  Connecting to APM 2.6 via SPI connections
 *
 *    Analog connections on APM 2.6
 *     A0                   A11 SPI
 *    _______________________________
 *    | . . . . . . . . . . . . 1 2 | -    1: MISO 2:  VCC
 *    | . . . . . . . . . . . . 3 4 | +    3:  SCK 4: MOSI
 *    | . . . . . . . . . . . . 5 6 | s    5:  RST 6:  GND
 *    -------------------------------
 *
 *   NOTE: VCC is for SPI connected devices to see voltage.
 *         This does not provide voltage. A 5V supply will
 *         need to be supplied. Connecting battery to BEC
 *         then to APM will do. You may be able to use
 *         EXT PWR on AVR dragon but I have never looked
 *         into this.
 *
 *  Connecting to APM 2.6 via JTAG connections
 *
 *    Analog connections on APM 2.6
 *     A0      A4 .. A7     A11 SPI
 *    _______________________________
 *    | . . . . . . . . . . . . . 4 | -    1: TCK         2: GND (Not used)
 *    | . . . . . . . . . . . . . . | +    3: TDO         4: VREF
 *    | . . . . 1 5 3 9 . . . . 6 10| s    5: TMS         6: RESET
 *    -------------------------------      7: (Not used)  8: (Not used)
 *                                         9: TDI        10: GND
 *
 *   NOTE: VREF is for JTAG connected devices to see voltage.
 *         This does not provide voltage. A 5V supply will
 *         need to be supplied. Connecting battery to BEC
 *         then to APM will do. You may be able to use
 *         EXT PWR on AVR dragon but I have never looked
 *         into this.
 *
 *  Connecting external MPU to APM 2.6
 *
 *   I2C pins on APM 2.6 board
 *     PM
 *    _____
 *    | - |  I2C
 *    | - | _____
 *    | - | | 1 |   1: 3.3 V
 *    | - | | 2 |   2: SCL 1
 *    | - | | 3 |   3: SDA 1
 *    | - | | 4 |   4: Unused
 *    ----- -----
 *
 *   NOTE: This is only here because I was having issues talking
 *         with my internal MPU 6050 and bought an external MPU
 *         6050 to test.
 *
 *-----------------------------------------------------------
 * AVR DRAGON
 *
 *  Connection to AVR dragon via SPI/JTAG connections
 *
 *                    /\
 *                    ||  To PC connection
 *                    ||
 *   |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 *   |                                       |
 *   |                                       |
 *   | EXT PWR                               |
 *   | . . .                                 |
 *   | . . .                                 |
 *   |                                       |
 *   | 2 4 6 8 10  2 4 6  .................. |
 *   | 1 3 5 7 9   1 3 5  .................. |
 *   |    JTAG      SPI                      |
 *   | ....................................  |
 *   | ....................................  |
 *   |  O                                O   |
 *   | ....................................  |
 *   | .........................             |
 *   |                                       |
 *   | .........................             |
 *   | ....................................  |
 *   -----------------------------------------
 *
 *-----------------------------------------------------------
 *  To load hex onto APM:
 *    avrdude -p <mpu> -c <isp> -P <port> -e -v -U flash:w:<name>.hex
 *          <mpu>:  chip on APM (atmega2560)
 *          <isp>:  programmer  (dragon_isp)
 *          <port>: port        (usb)
 *          <name>: name of file/program
 *-----------------------------------------------------------
 *  To debug avr microcontroller via MkII (Dragon) programmer:
 *
 *  1. Start avarice server
 *   sudo avarice --dragon --jtag usb :<port>
 *          <port>: port to use (4242)
 *
 *  2. Connect avr-gdb:
 *   avr-gdb <program>.elf
 *    target remove localhost:<port>
 *          <port>: port used when avarice was started
 *
 *   NOTE: You must build the program with -g or -ggdb flag
 *-----------------------------------------------------------
 */

#include "QuadMgr.h"

int main( void )
{
    // Initialize
    Quad::QuadMgr quad;
    quad.start();

    // Process loop
    quad.loop();

    return 0;
}

