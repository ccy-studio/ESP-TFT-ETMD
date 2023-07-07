/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-07 15:07:08
 * @LastEditTime: 2023-07-07 16:34:41
 */
#include "at24cx.h"

I2CMemory::I2CMemory(uint8_t address) : i2cDevice(address) {}

bool I2CMemory::save(uint8_t pageAddress, const uint8_t* data) {
    // 创建一个数据缓冲区，用于包含页地址和数据
    uint8_t buffer[9];
    buffer[0] = pageAddress;
    memcpy(&buffer[1], data, 8);  // 复制数据到缓冲区

    // 执行页写操作
    return i2cDevice.write(buffer, 9);
}

bool I2CMemory::read(uint8_t pageAddress, uint8_t* buffer) {
    // 创建一个地址缓冲区，用于指定要读取的页地址
    uint8_t addressBuffer[1];
    addressBuffer[0] = pageAddress;

    // 设置读取操作的目标地址
    if (!i2cDevice.write_then_read(addressBuffer, 1, buffer, 8)) {
        return false;  // 设置目标地址失败
    }

    // 检查读取到的数据是否为0xFF，如果是，则停止读取
    for (int i = 0; i < 8; i++) {
        if (buffer[i] == 0xFF) {
            break;
        }
    }

    return true;
}

bool I2CMemory::clear(uint8_t pageAddress) {
    uint8_t buffer[9];
    buffer[0] = pageAddress;
    memset(&buffer[1], 0xFF, 8);
    return i2cDevice.write(buffer, 9);
}