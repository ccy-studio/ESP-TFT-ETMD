/*
 * @Description: 
 * @Author: chenzedeng
 * @Date: 2023-07-11 10:24:44
 * @LastEditTime: 2023-07-11 17:18:32
 */
#ifndef __WEATHER__
#define __WEATHER__

#include "http_request.h"

// 天气接口API Key
#define API_KEY "S9YSc3OVs47tFJRth"

typedef struct {
    char text[10];
    u8 code;
    char temperature[5];
} WeatherResponse;

WeatherResponse getWeatherNowInfo();

#endif