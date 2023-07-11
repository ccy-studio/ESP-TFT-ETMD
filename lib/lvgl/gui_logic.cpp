/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-11 15:15:44
 * @LastEditTime: 2023-07-11 23:52:34
 */
// #include "aht2x.h"
#include <gui.h>

#define NTP1 "ntp1.aliyun.com"
#define NTP2 "ntp2.aliyun.com"
#define NTP3 "ntp3.aliyun.com"

#define ASYNC_DELAY 1000  // 异步任务执行频率单位毫秒

#define TIME_UPDATE_DELAY 500
#define AHT21_UPDATE_DELAY 5000

static u8 _gui_time_falg = 0;
static u16 _gui_aht21_falg = 0;
struct tm timeinfo;

static int lastHour = -1;
static char timeStr[3];   // 时间字符串缓冲区
static char aht21Str[5];  // AHT21字符串缓冲区
static char weather_temperature_buf[20];

Adafruit_AHTX0 aht;

extern const lv_img_dsc_t ui_img_4;
extern const lv_img_dsc_t ui_img_99;

void aht21Gather(float* temp, float* humidity) {
    sensors_event_t humidity_s, temp_s;
    aht.getEvent(&humidity_s, &temp_s);
    *temp = temp_s.temperature;
    *humidity = humidity_s.relative_humidity;
}

void getTimeInfo() {
    if (!getLocalTime(&timeinfo)) {
        if (WiFi.isConnected()) {
            configTime(8 * 3600, 0, NTP1, NTP2, NTP3);
        }
    }
}

void updateWeather() {
    printf("开始请求获取天气信息\n");
    WeatherResponse response = getWeatherNowInfo();
    if (response.code) {
        printf("天气获取成功==>code:%d text:%s,temp:%s\n", response.code,
               response.text, response.temperature);

        sniprintf(weather_temperature_buf, sizeof(weather_temperature_buf),
                  "当前温度 %s", response.temperature);
        lv_label_set_text(ui_Label3, weather_temperature_buf);
        memset(weather_temperature_buf, 0, sizeof(weather_temperature_buf));

        switch (response.code) {
            case 4:
                lv_img_set_src(ui_Image1, &ui_img_4);
                break;
            default:
                lv_img_set_src(ui_Image1, &ui_img_99);
                break;
        }
    } else {
        printf("获取天气信息失败\n");
    }
    Serial.print("updateWeather==> Task stack high water mark: ");
    Serial.println(uxTaskGetStackHighWaterMark(NULL));
}

void updateTime() {
    getTimeInfo();
    // 更新时的文本值
    snprintf(timeStr, sizeof(timeStr), "%02d", timeinfo.tm_hour);
    lv_label_set_text(ui_hour, timeStr);
    memset(timeStr, 0, sizeof(timeStr));  // 清空缓冲区

    // 更新分的文本值
    snprintf(timeStr, sizeof(timeStr), "%02d", timeinfo.tm_min);
    lv_label_set_text(ui_min, timeStr);
    memset(timeStr, 0, sizeof(timeStr));  // 清空缓冲区

    // 更新秒的文本值
    snprintf(timeStr, sizeof(timeStr), "%02d", timeinfo.tm_sec);
    lv_label_set_text(ui_sec, timeStr);
    memset(timeStr, 0, sizeof(timeStr));  // 清空缓冲区
}

void updateAht21() {
    float temp, humidity;
    aht21Gather(&temp, &humidity);
    // 文本缓冲区
    snprintf(aht21Str, sizeof(aht21Str), "%.1f°", temp);
    lv_label_set_text(ui_tempVal, aht21Str);
    memset(aht21Str, 0x00, sizeof(aht21Str));
    snprintf(aht21Str, sizeof(aht21Str), "%.1f°", humidity);
    lv_label_set_text(ui_humidityVal, aht21Str);
    memset(aht21Str, 0x00, sizeof(aht21Str));
}

void gui_async_time(void* pvParameters) {
    while (1) {
        updateTime();
        lastHour = timeinfo.tm_hour;
        V_DELAY_MS(500);
    }
}

void gui_async_task(void* pvParameters) {
    V_DELAY_MS(500);
    while (1) {
        if (_gui_aht21_falg == 0) {
            updateAht21();
        }
        _gui_aht21_falg++;

        if ((_gui_aht21_falg * ASYNC_DELAY) >= AHT21_UPDATE_DELAY) {
            _gui_aht21_falg = 0;
        }

        if (lastHour != timeinfo.tm_hour) {
            // 过了一小时，更新天气信息
            updateWeather();
            _gui_aht21_falg = 0;
        }
        V_DELAY_MS(ASYNC_DELAY);
    }
}