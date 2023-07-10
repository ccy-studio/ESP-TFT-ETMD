/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-07 10:23:33
 * @LastEditTime: 2023-07-10 13:38:14
 */

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "at24cx.h"
#include "led_util.h"
#include "user_key.h"
#include "wifi_manage.h"
#include "aht2x.h"

void keyEvent(UserKey key) {
    printf("SendEvent===>> Id:%d, isPress:%d, isPressLong:%d, tickCount:%ld\n",
           key.keyId, key.isPress, key.isPressLong, key.tickCount);
    if (key.keyId == ADC_KEY_GROUP_HL && key.isPress == 1) {
        resetWifiConcig();
        printf("重置WIFI成功");
    }
}

void setup() {
    Serial.begin(115200);
    // Init I2C
    Wire.setPins(GPIO_NUM_18, GPIO_NUM_19);

    if (!aht.begin(&Wire, 0L, 0x38)) {
        Serial.println("Could not find AHT? Check wiring");
        while (1)
            delay(10);
    }

    initWifiManage();
    delay(500);

    // if (!eeprom.init()) {
    //     Serial.println("Could not find AT24C? Check wiring");
    //     while (1)
    //         delay(10);
    // }

    WIFIConfig config = getWifiAPConfig();
    printf("WIFIConfig-> SSID:%s PWD:%s \n", config.ssidName, config.password);
    if (!(*config.ssidName)) {
        printf("WIFI未配置,开启AP配置WIFI\n");
        startRunWifiAPConfig();
    } else {
        // connectWifiSTA();
    }

    xTaskCreate(led_thread, "LED Task", 800, NULL, 1, NULL);
    xTaskCreate(user_key_thread, "UserKey Task", 2000, NULL, 1, NULL);
    registerListener(keyEvent);
}

void loop() {
    mainLoop();
}
