/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-07 10:23:33
 * @LastEditTime: 2023-07-09 22:22:36
 */
#include <Adafruit_AHTX0.h>
#include <Arduino.h>
#include <HTTPClient.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "at24cx.h"
#include "led_util.h"
#include "user_key.h"
#include "wifi_manage.h"

Adafruit_AHTX0 aht;

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
    // resetWifiConcig();
    // WIFIConfig setWifi;
    // setWifi.password = (uint8_t*)"13083278337";
    // setWifi.ssidName = (uint8_t*)"Connect-YC";
    // setWifiConfig(setWifi);

    // printf("1 WIFIConfig-> SSID:%s PWD:%s \n", setWifi.ssidName,
    // setWifi.password);

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

    // delay(500);
    // digitalWrite(LED, LOW);
    // delay(500);
    // digitalWrite(LED, HIGH);

    // sensors_event_t humidity, temp;
    // aht.getEvent(&humidity, &temp);
    // printf("温度：%f -- 湿度: %f\n", temp.temperature,
    //        humidity.relative_humidity);

    // size_t len = 50;
    // uint8_t* buf = (uint8_t*)calloc(len, sizeof(uint8_t));
    // eeprom.read_page(0x00, buf, len);
    // printf("最终输出的文字: %s\n", buf);
    // free(buf);
    // buf = NULL;
}
