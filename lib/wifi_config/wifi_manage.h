/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-07 20:01:44
 * @LastEditTime: 2023-07-11 17:22:00
 */
#ifndef __WIFI_CONFIG_
#define __WIFI_CONFIG_

#include <Arduino.h>
#include <AsyncTCP.h>
#include <DNSServer.h>
#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include "at24cx.h"
#include "event_bus.h"

enum class RunState {
    CONNECTED = 0,
    AP = 1,
    STA = 2,
    NO_CONNECT = 3,
    CONNECTING = 4,
    FAIL = -1,
};

struct WIFIConfig {
    uint8_t* ssidName;
    uint8_t* password;
};

void initWifiManage();

void freeWifiManage();

/**
 * 获取当前WIFI的模式与状态
 */
RunState getAPState(void);

/**
 * 重置WIFI配置
 */
void resetWifiConcig(void);

/**
 * 开启WIFI配网
 */
void startRunWifiAPConfig(void);

void stopWifiAp(void);

/**
 * 获取当前WIFI配置信息
 */
WIFIConfig getWifiAPConfig(void);

/**
 * 设置WIFI配置信息
 */
void setWifiConfig(WIFIConfig config);

void unconnectWifiSTA();

void connectWifiSTA();

void mainLoop(void);

void testEEPROM();

#endif