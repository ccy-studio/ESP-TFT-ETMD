/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-07 15:07:08
 * @LastEditTime: 2023-07-09 10:00:35
 */
#include "at24cx.h"

#define MAX_LENGTH 8

I2CMemory::I2CMemory(uint8_t address) : i2c_dev(address, &Wire) {}

bool I2CMemory::init() {
    if (!i2c_dev.begin()) {
        return false;
    }
    return true;
}

bool I2CMemory::write_byte(uint8_t addr, uint8_t* data, uint8_t len) {
    i2c_dev.write(data, len, true, &addr, 1);
    delay(10);
    return true;
}

bool I2CMemory::read_byte(uint8_t addr,
                          uint8_t* dataBuf,
                          uint8_t len,
                          bool isCheck) {
    i2c_dev.write_then_read(&addr, 1, dataBuf, len);
    if (isCheck) {
        for (int i = 0; i < len; i++) {
            if (dataBuf[i] == 0xFF) {
                dataBuf[i] = 0x00;
            }
        }
    }
    delay(10);
    return true;
}

bool I2CMemory::write_page(uint8_t addr, const uint8_t* data, size_t len) {
    uint8_t spliteCount = (len > MAX_LENGTH)
                              ? ((len % MAX_LENGTH == 0) ? len / MAX_LENGTH
                                                         : len / MAX_LENGTH + 1)
                              : 1;
    uint8_t bufs[spliteCount][MAX_LENGTH];

    for (int i = 0; i < spliteCount; i++) {
        size_t index = i * MAX_LENGTH;
        for (int j = 0; j < MAX_LENGTH; j++) {
            if (*data) {
                bufs[i][j] = *data;
                data++;
            } else {
                bufs[i][j] = 0xFF;
            }
        }
    }
    uint8_t startAddress = addr;
    for (int i = 0; i < spliteCount; i++) {
        write_byte(startAddress, bufs[i], MAX_LENGTH);
        startAddress += 8;
    }
    return true;
}

bool I2CMemory::read_page(uint8_t addr, uint8_t* data, size_t len) {
    uint8_t spliteCount = (len > MAX_LENGTH)
                              ? ((len % MAX_LENGTH == 0) ? len / MAX_LENGTH
                                                         : len / MAX_LENGTH + 1)
                              : 1;
    uint8_t startAddress = addr;
    uint8_t isDone = false;
    uint8_t buf[MAX_LENGTH];
    for (int i = 0; i < spliteCount; i++) {
        if (isDone) {
            break;
        }
        read_byte(startAddress, buf, MAX_LENGTH, false);
        if (buf[MAX_LENGTH - 1] == 0xFF) {
            isDone = true;
            for (int j = 0; j < MAX_LENGTH; j++) {
                if (buf[j] == 0xFF) {
                    buf[j] = 0x00;
                }
            }
        }
        memcpy(data + (i * MAX_LENGTH), buf, MAX_LENGTH);
        startAddress += 8;
    }
    return true;
}

bool I2CMemory::clear(uint8_t addr, uint8_t len) {
    uint8_t buf[len];
    memset(buf, 0xFF, sizeof(buf));
    return write_page(addr, buf, len);
}