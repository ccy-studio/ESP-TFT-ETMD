/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-07 15:07:02
 * @LastEditTime: 2023-07-09 09:47:00
 */
#ifndef __AT24CX_
#define __AT24CX_
#include <Adafruit_I2CDevice.h>

/**
 * 根据页码算地址，有一个简单的公式，就是页地址 = (页码 - 1) *
8。例如，第5页的地址是 (5 - 1) * 8 = 0x20。
 * 第1页：0x00
第2页：0x08
第3页：0x10
第4页：0x18
第5页：0x20
第6页：0x28
第7页：0x30
第8页：0x38
第9页：0x40
第10页：0x48
第11页：0x50
第12页：0x58
第13页：0x60
第14页：0x68
第15页：0x70
第16页：0x78
第17页：0x80
第18页：0x88
第19页：0x90
第20页：0x98
第21页：0xA0
第22页：0xA8
第23页：0xB0
第24页：0xB8
第25页：0xC0
第26页：0xC8
第27页：0xD0
第28页：0xD8
第29页：0xE0
第30页：0xE8
第31页：0xF0
第32页：0xF8
*/
class EEPROMAddressEnum {
   public:
    // WIFI配置信息 账号和密码分别占用24个字节（三页）
    const static uint8_t WIFI_CONF_SSID = 0x00;
    const static uint8_t WIFI_CONF_SSID_LEN = 24;

    const static uint8_t WIFI_CONF_PASSWORD = 0x18;
    const static uint8_t WIFI_CONF_PASSWORD_LEN = 24;

    const static uint8_t MY_NAME = 0x30;  // 我的昵称
    const static uint8_t MY_NAME_LEN = 16;

    const static uint8_t MY_DESC = 0x40;  // 我的个人描述
    const static uint8_t MY_DESC_LEN = 16;

    const static uint8_t CITY_CODE = 0x50;  // 城市编码
    const static uint8_t CITY_CODE_LEN = 8;
};

// I2C地址
#define AT24CX_ADDRESS 0x50

class I2CMemory {
   public:
    I2CMemory(uint8_t address);
    bool init();
    bool write_byte(uint8_t addr, uint8_t* data, uint8_t len);
    bool read_byte(uint8_t addr,
                   uint8_t* buf,
                   uint8_t len,
                   bool isCheck = true);
    bool write_page(uint8_t addr, const uint8_t* data, size_t len);
    bool read_page(uint8_t addr, uint8_t* data, size_t len);
    bool clear(uint8_t addr, uint8_t len);

   private:
    Adafruit_I2CDevice i2c_dev;
};

#endif