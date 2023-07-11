/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-11 10:24:44
 * @LastEditTime: 2023-07-11 23:17:16
 */
#ifndef __WEATHER__
#define __WEATHER__

#include "http_request.h"

// 天气接口API Key
#define API_KEY "S9YSc3OVs47tFJRth"

// 当前位置
extern char weahterLocation[50];

typedef struct {
    char text[10];
    u8 code;
    char temperature[5];
} WeatherResponse;

WeatherResponse getWeatherNowInfo();

#endif