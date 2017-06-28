//
// Created by jesse on 2/22/17.
//

extern "C" {
#include <avr/io.h>
#include <util/twi.h>
}

#include "Eeprom.h"
#include "TwiMgr.h"

#define TWI_STATUS      (TWSR & 0xF8)
#define cbi(sfr, bit)   (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit)   (_SFR_BYTE(sfr) |= _BV(bit))

twi::TwiMgr::TwiMgr() :
    comms( Comms::CommsMgr::reference() ),
    eeprom( Eeprom::EepromMgr::reference() )
{
    // TWI Bit Rate Register
    TWBR = ((F_CPU / I2C_BAUD) - 16)/2;
    //comms.putChar(TWBR);

    // set bits PortD pins 0 & 1
    sbi(DDRD, 0);
    sbi(DDRD, 1);
    sbi(PORTD, 0);
    sbi(PORTD, 1);

    // Set prescalar to 1 (0x00)
    //TWSR = 0;
    cbi(TWSR, TWPS0);
    cbi(TWSR, TWPS1);
    //TWSR |= (0 << TWPS1) | (0 << TWPS0);

    // enable twi
    TWCR = _BV(TWEN);
}

twi::TwiMgr &twi::TwiMgr::reference( void )
{
    static twi::TwiMgr ref;
    return ref;
}

/** write a single bit in an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to write to
 * @param bitNum Bit position to write (0-7)
 * @param value New bit value to write
 * @return Status of operation (true = success)
 */
//bool twi::TwiMgr::writeBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data)
//{
//    uint8_t b;
//    readByte(devAddr, regAddr, &b);
//    b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
//    return writeByte(devAddr, regAddr, b);
//}
//
///** Write multiple bits in an 8-bit device register.
// * @param devAddr I2C slave device address
// * @param regAddr Register regAddr to write to
// * @param bitStart First bit position to write (0-7)
// * @param length Number of bits to write (not more than 8)
// * @param data Right-aligned value to write
// * @return Status of operation (true = success)
// */
//bool twi::TwiMgr::writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data)
//{
//    //      010 value to write
//    // 76543210 bit numbers
//    //    xxx   args: bitStart=4, length=3
//    // 00011100 mask byte
//    // 10101111 original value (sample)
//    // 10100011 original & ~mask
//    // 10101011 masked | value
//    uint8_t b;
//    if (readByte(devAddr, regAddr, &b) != 0) {
//        uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
//        data <<= (bitStart - length + 1); // shift data into correct position
//        data &= mask; // zero all non-important bits in data
//        b &= ~(mask); // zero all important bits in existing byte
//        b |= data; // combine data with existing byte
//        return writeByte(devAddr, regAddr, b);
//    } else {
//        return false;
//    }
//}
//
///** Write single byte to an 8-bit device register.
// * @param devAddr I2C slave device address
// * @param regAddr Register address to write to
// * @param data New byte value to write
// * @return Status of operation (true = success)
// */
//bool twi::TwiMgr::writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data)
//{
//    return writeBytes(devAddr, regAddr, 1, &data);
//}
//
///** Write multiple bytes to an 8-bit device register.
// * @param devAddr I2C slave device address
// * @param regAddr First register address to write to
// * @param length Number of bytes to write
// * @param data Buffer to copy new data from
// * @return Status of operation (true = success)
// */
//bool twi::TwiMgr::writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t* data)
//{
//    int8_t count = 0;
//    uint8_t buf[128];
//    //int fd;
//
//    //if (length > 127) {
//    //    fprintf(stderr, "Byte write count (%d) > 127\n", length);
//    //    return(FALSE);
//    //}
//
//    //fd = open("/dev/i2c-1", O_RDWR);
//    //if (fd < 0) {
//    //    fprintf(stderr, "Failed to open device: %s\n", strerror(errno));
//    //    return(FALSE);
//    //}
//    //if (ioctl(fd, I2C_SLAVE, devAddr) < 0) {
//    //    fprintf(stderr, "Failed to select device: %s\n", strerror(errno));
//    //    close(fd);
//    //    return(FALSE);
//    //}
//    //buf[0] = regAddr;
//    //memcpy(buf+1,data,length);
//    //count = write(fd, buf, length+1);
//    //if (count < 0) {
//    //    fprintf(stderr, "Failed to write device(%d): %s\n", count, ::strerror(errno));
//    //    close(fd);
//    //    return(FALSE);
//    //} else if (count != length+1) {
//    //    fprintf(stderr, "Short write to device, expected %d, got %d\n", length+1, count);
//    //    close(fd);
//    //    return(FALSE);
//    //}
//    //close(fd);
//
//    return false;
//}
//
/** Read single byte from an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to read from
 * @param data Container for byte value read from device
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
 * @return Status of read operation (true = success)
 */
int8_t twi::TwiMgr::readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint16_t timeout)
{
    return readBytes(devAddr, regAddr, 1, data, timeout);
}

///** Read multiple bytes from an 8-bit device register.
// * @param devAddr I2C slave device address
// * @param regAddr First register regAddr to read from
// * @param length Number of bytes to read
// * @param data Buffer to store read data in
// * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
// * @return Number of bytes read (-1 indicates failure)
// */
//int8_t twi::TwiMgr::readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data, uint16_t timeout)
//{
//    int8_t count = 0;
//    //int fd = open("/dev/i2c-1", O_RDWR);
//
//    //if (fd < 0) {
//    //    fprintf(stderr, "Failed to open device: %s\n", strerror(errno));
//    //    return(-1);
//    //}
//    //if (ioctl(fd, I2C_SLAVE, devAddr) < 0) {
//    //    fprintf(stderr, "Failed to select device: %s\n", strerror(errno));
//    //    close(fd);
//    //    return(-1);
//    //}
//    //if (write(fd, &regAddr, 1) != 1) {
//    //    fprintf(stderr, "Failed to write reg: %s\n", strerror(errno));
//    //    close(fd);
//    //    return(-1);
//    //}
//    //count = read(fd, data, length);
//    //if (count < 0) {
//    //    fprintf(stderr, "Failed to read device(%d): %s\n", count, ::strerror(errno));
//    //    close(fd);
    //    return(-1);
    //} else if (count != length) {
    //    fprintf(stderr, "Short read  from device, expected %d, got %d\n", length, count);
    //    close(fd);
    //    return(-1);
    //}
    //close(fd);

//    return -1;
//}

bool twi::TwiMgr::isIdle()
{
    while ((TWCR & (1 << TWINT)) == 0)
        //comms.putChar(1);
        ;
    return true;
}

void twi::TwiMgr::sendStart()
{
    TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
}

void twi::TwiMgr::sendStop() {
    TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
}

void twi::TwiMgr::sendSlaR(uint8_t addr)
{
    TWDR = (addr << 1) | 0x01;   
    TWCR = _BV(TWINT) | _BV(TWEN);
}

void twi::TwiMgr::sendSlaW(uint8_t addr)
{
    TWDR = addr << 1;
    TWCR = _BV(TWINT) | _BV(TWEN);
}

void twi::TwiMgr::test_read(uint8_t addr)
{
    sendStart();
    isIdle();

    uint8_t status = 0x00;

    while (status != 0x40) {
        status = TWI_STATUS;
        comms.putChar(status); 
        switch (TWSR)
        {
            case 0x08:
            case 0x10:
                sendSlaR(addr);
                comms.putChar(0xAA);
                break;
            case 0x40:
                comms.putChar(0x42);
                break;
            case 0x48:
                TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO);  // send a stop
                //sendStart();
                //repeatedStart();
                comms.putChar(0xBB);
                return;
                break;
            default:
                comms.putChar(0xEE);
                break;
        }
        isIdle();
    }
}

void twi::TwiMgr::request_read(uint8_t addr, uint8_t reg)
{
    // TWCR : 0x00
    // TWSR : 0xF8
    // TWDR : 0xFF
    // 0x2d
    print_status();

    sendStart();
    isIdle(); // 0x01

    // TWCR : 0xa4
    // TWSR : 0x08 -> start sent
    // TWDR : 0xFF
    // 0x2d
    print_status();

    // send SLA + R
    TWDR = (addr << 1) | 0x01; // SLA + R
    //TWDR = (addr << 1) | 0x00; // SLA + W
    //TWDR = 0xD3; // SLA + W
    TWCR |= (1 << TWINT);
    isIdle(); // 0x01

    // repeated start
    if (TWSR == 0x48) {
        TWCR |= (1 << TWINT) | (1 << TWSTA);
    }

    // TWCR : 0x84
    // TWSR : 0x20
    // TWDR : 0x69 or 0xd2
    // 0x2d
    print_status();

    //TWDR = 0x6B; // pwr register
    TWDR = 0x75; // who am i register
    TWCR = (1 << TWINT) | (1 << TWEN);
    isIdle(); // 0x01

    // TWCR : 0x84
    // TWSR : 0x30
    // TWDR : 0x75
    // 0x2d
    print_status();
}

void twi::TwiMgr::print_status()
{
    comms.putChar(TWCR);
    comms.putChar(TWSR & 0xF8);
    comms.putChar(TWDR);
    comms.putChar('-');
}

uint8_t twi::TwiMgr::i2c_start(uint8_t address)
{
	// reset TWI control register
	TWCR = 0;
	// transmit START condition
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	// wait for end of transmission
	while( !(TWCR & (1<<TWINT)) );

	// check if the start condition was successfully transmitted
	if((TWSR & 0xF8) != TW_START){ return 1; }

	// load slave address into data register
	TWDR = address;
	// start transmission of address
	TWCR = (1<<TWINT) | (1<<TWEN);
	// wait for end of transmission
	while( !(TWCR & (1<<TWINT)) );

	// check if the device has acknowledged the READ / WRITE mode
	uint8_t twst = TW_STATUS & 0xF8;
	if ( (twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) ) return 2;

	return 0;
}

#define I2C_TIMER_DELAY 10

void twi::TwiMgr::i2c_start_wait(unsigned char address)
{
	uint32_t  i2c_timer = 0;
	uint8_t   twst;
	uint8_t attempts = 0;

    while ( 1 )
    {
        if (attempts++ > 10) {
            comms.putChar(0x05);
            break;
        }
	    // send START condition
	    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

    	// wait until transmission completed 
	    i2c_timer = I2C_TIMER_DELAY;
    	while(!(TWCR & (1<<TWINT)) && i2c_timer--);

    	// check value of TWI Status Register. Mask prescaler bits.
    	twst = TW_STATUS & 0xF8;
    	if ( (twst != TW_START) && (twst != TW_REP_START)) continue;

    	// send device address
    	TWDR = address;
    	TWCR = (1<<TWINT) | (1<<TWEN);

    	// wail until transmission completed
    	i2c_timer = I2C_TIMER_DELAY;
    	while(!(TWCR & (1<<TWINT)) && i2c_timer--);

    	// check value of TWI Status Register. Mask prescaler bits.
    	twst = TW_STATUS & 0xF8;
    	comms.putChar(twst);
    	if ( (twst == TW_MT_SLA_NACK )||(twst ==TW_MR_DATA_NACK) )
    	{
    	    /* device busy, send stop condition to terminate write operation */
	        TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);

	        // wait until stop condition is executed and bus released
	        i2c_timer = I2C_TIMER_DELAY;
	        while((TWCR & (1<<TWSTO)) && i2c_timer--);
            comms.putChar(0x01);
    	    continue;
    	}
    	//if( twst != TW_MT_SLA_ACK) return 1;
    	comms.putChar(0x42);
    	break;
     }

}

void twi::TwiMgr::sendByte(uint8_t byte) {
    TWDR = byte;
    TWCR = _BV(TWINT);
}

/* i2c_start_wait */

// TODO finish implementing and test
bool twi::TwiMgr::writeByte(uint8_t devAddr,
                            uint8_t regAddr,
                            uint8_t data,
                            uint8_t timeout)
{
    sendStart();

    // Wait for a response
    while ( timeout-- > 0 && !isIdle() )
        ;

    // Send SLA+W & address
    sendSlaW(devAddr);

    // Wait for a response
    while ( timeout-- > 0 && !isIdle() )
        ;

    if (TWSR == TX_MODE_ADDR_NACK) {
        sendStart();

        // Wait for a response
        while ( timeout-- > 0 && !isIdle() )
            ;

        sendSlaW(devAddr);
    }

    if (TWSR == TX_MODE_ADDR_ACK) {
        sendByte(regAddr);

        // Wait for a response
        while ( timeout-- > 0 && !isIdle() )
            ;

        if (TWSR == TX_MODE_DATA_ACK)
        {
            // successful RA transmittion
        }

        sendByte(data);

        // Wait for a response
        while ( timeout-- > 0 && !isIdle() )
            ;

        if (TWSR == TX_MODE_DATA_ACK)
        {
            sendStop();
        }
    }
}
