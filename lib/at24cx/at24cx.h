/*
 * @Description: 
 * @Author: chenzedeng
 * @Date: 2023-07-07 15:07:02
 * @LastEditTime: 2023-07-07 16:19:10
 */
#ifndef __AT24CX_
#define __AT24CX_
#include <Adafruit_I2CDevice.h>
#include <eeporm_address.h>

//I2C地址
#define AT24CX_ADDRESS 0xA0


class I2CMemory {
public:
  I2CMemory(uint8_t address);
  bool save(uint8_t pageAddress, const uint8_t* data);
  bool read(uint8_t pageAddress, uint8_t* buffer);
  bool clear(uint8_t pageAddress);
private:
  Adafruit_I2CDevice i2cDevice;
};

#endif