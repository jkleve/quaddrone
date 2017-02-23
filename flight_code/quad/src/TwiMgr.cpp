//
// Created by jesse on 2/22/17.
//

extern "C" {
#include <avr/io.h>
}

#include "TwiMgr.h"

Twi::TwiMgr::TwiMgr()
{
    // TWI Bit Rate Register
    TWBR = ((F_CPU / I2C_BAUD) - 16)/2;

    // Set prescalar to 1
    TWSR |= (0 << TWPS1) | (0 << TWPS0);
}

Twi::TwiMgr &Twi::TwiMgr::reference( void )
{
    static Twi::TwiMgr ref;
    return ref;
}

/** write a single bit in an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to write to
 * @param bitNum Bit position to write (0-7)
 * @param value New bit value to write
 * @return Status of operation (true = success)
 */
bool Twi::TwiMgr::writeBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data)
{
    uint8_t b;
    readByte(devAddr, regAddr, &b);
    b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
    return writeByte(devAddr, regAddr, b);
}

/** Write multiple bits in an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to write to
 * @param bitStart First bit position to write (0-7)
 * @param length Number of bits to write (not more than 8)
 * @param data Right-aligned value to write
 * @return Status of operation (true = success)
 */
bool Twi::TwiMgr::writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data)
{
    //      010 value to write
    // 76543210 bit numbers
    //    xxx   args: bitStart=4, length=3
    // 00011100 mask byte
    // 10101111 original value (sample)
    // 10100011 original & ~mask
    // 10101011 masked | value
    uint8_t b;
    if (readByte(devAddr, regAddr, &b) != 0) {
        uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        data <<= (bitStart - length + 1); // shift data into correct position
        data &= mask; // zero all non-important bits in data
        b &= ~(mask); // zero all important bits in existing byte
        b |= data; // combine data with existing byte
        return writeByte(devAddr, regAddr, b);
    } else {
        return false;
    }
}

/** Write single byte to an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register address to write to
 * @param data New byte value to write
 * @return Status of operation (true = success)
 */
bool Twi::TwiMgr::writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data)
{
    return writeBytes(devAddr, regAddr, 1, &data);
}

/** Write multiple bytes to an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr First register address to write to
 * @param length Number of bytes to write
 * @param data Buffer to copy new data from
 * @return Status of operation (true = success)
 */
bool Twi::TwiMgr::writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t* data)
{
    int8_t count = 0;
    uint8_t buf[128];
    //int fd;

    //if (length > 127) {
    //    fprintf(stderr, "Byte write count (%d) > 127\n", length);
    //    return(FALSE);
    //}

    //fd = open("/dev/i2c-1", O_RDWR);
    //if (fd < 0) {
    //    fprintf(stderr, "Failed to open device: %s\n", strerror(errno));
    //    return(FALSE);
    //}
    //if (ioctl(fd, I2C_SLAVE, devAddr) < 0) {
    //    fprintf(stderr, "Failed to select device: %s\n", strerror(errno));
    //    close(fd);
    //    return(FALSE);
    //}
    //buf[0] = regAddr;
    //memcpy(buf+1,data,length);
    //count = write(fd, buf, length+1);
    //if (count < 0) {
    //    fprintf(stderr, "Failed to write device(%d): %s\n", count, ::strerror(errno));
    //    close(fd);
    //    return(FALSE);
    //} else if (count != length+1) {
    //    fprintf(stderr, "Short write to device, expected %d, got %d\n", length+1, count);
    //    close(fd);
    //    return(FALSE);
    //}
    //close(fd);

    return false;
}

/** Read single byte from an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to read from
 * @param data Container for byte value read from device
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
 * @return Status of read operation (true = success)
 */
int8_t Twi::TwiMgr::readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint16_t timeout)
{
    return readBytes(devAddr, regAddr, 1, data, timeout);
}

/** Read multiple bytes from an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr First register regAddr to read from
 * @param length Number of bytes to read
 * @param data Buffer to store read data in
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
 * @return Number of bytes read (-1 indicates failure)
 */
int8_t Twi::TwiMgr::readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data, uint16_t timeout)
{
    int8_t count = 0;
    //int fd = open("/dev/i2c-1", O_RDWR);

    //if (fd < 0) {
    //    fprintf(stderr, "Failed to open device: %s\n", strerror(errno));
    //    return(-1);
    //}
    //if (ioctl(fd, I2C_SLAVE, devAddr) < 0) {
    //    fprintf(stderr, "Failed to select device: %s\n", strerror(errno));
    //    close(fd);
    //    return(-1);
    //}
    //if (write(fd, &regAddr, 1) != 1) {
    //    fprintf(stderr, "Failed to write reg: %s\n", strerror(errno));
    //    close(fd);
    //    return(-1);
    //}
    //count = read(fd, data, length);
    //if (count < 0) {
    //    fprintf(stderr, "Failed to read device(%d): %s\n", count, ::strerror(errno));
    //    close(fd);
    //    return(-1);
    //} else if (count != length) {
    //    fprintf(stderr, "Short read  from device, expected %d, got %d\n", length, count);
    //    close(fd);
    //    return(-1);
    //}
    //close(fd);

    return -1;
}