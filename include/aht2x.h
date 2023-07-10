/*
 * @Description: 
 * @Author: chenzedeng
 * @Date: 2023-07-10 11:24:04
 * @LastEditTime: 2023-07-10 11:27:43
 */
#ifndef __AHT2X__
#define __AHT2X__

#include <Adafruit_AHTX0.h>

Adafruit_AHTX0 aht;

void gather(float* temp, float* humidity) {
    sensors_event_t humidity_s, temp_s;
    aht.getEvent(&humidity_s, &temp_s);
    *temp = temp_s.temperature;
    *humidity = humidity_s.relative_humidity;
}

#endif