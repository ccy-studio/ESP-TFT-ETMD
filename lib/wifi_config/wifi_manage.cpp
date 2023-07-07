#include "wifi_manage.h"
#include "at24cx.h"

DNSServer dnsServer;
AsyncWebServer server(80);
I2CMemory eeprom(AT24CX_ADDRESS);

static RunState currentRunState;

// class CaptiveRequestHandler : public AsyncWebHandler {
//    public:
//     CaptiveRequestHandler() {}
//     virtual ~CaptiveRequestHandler() {}

//     bool canHandle(AsyncWebServerRequest* request) {
//         // request->addInterestingHeader("ANY");
//         return true;
//     }

//     void handleRequest(AsyncWebServerRequest* request) {}
// };

RunState getAPState(void) {
    return currentRunState;
}

void resetWifiConcig(void) {
    eeprom.clear(EEPROMAddressEnum::WIFI_CONF_P1);
    eeprom.clear(EEPROMAddressEnum::WIFI_CONF_P2);
    eeprom.clear(EEPROMAddressEnum::WIFI_CONF_P3);
    eeprom.clear(EEPROMAddressEnum::WIFI_CONF_S1);
    eeprom.clear(EEPROMAddressEnum::WIFI_CONF_S2);
    eeprom.clear(EEPROMAddressEnum::WIFI_CONF_S3);
}

void startRunWifiAPConfig(void) {
    WiFi.softAP("ESP32-ETMD");
    dnsServer.start(53, "*", WiFi.softAPIP());

    // server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);
    server.on("/", [](AsyncWebServerRequest* request) {
        AsyncResponseStream* response =
            request->beginResponseStream("text/html");
        response->print(
            "<!DOCTYPE html><html><head><title>Captive "
            "Portal</title></head><body>");

        if (request->hasParam("error")) {
            AsyncWebParameter* p = request->getParam("error");
            const char* errorStr = p->value().c_str();
            response->printf("<h2 style='color:read'>%s</h2>", errorStr);
        }

        response->print(
            "<h1>WiFi AP配网</h1><form method='POST' action='/save'><label "
            "for='ssid'>WiFi名称:</label><br><input type='text' id='ssid' "
            "name='ssid'><br><label for='password'>WiFi密码:</label><br><input "
            "type='password' id='password' name='password'><br><br><input "
            "type='submit' value='保存'></form>");

        response->print("</body></html>");
        request->send(response);
    });

    // 处理保存配置的请求
    server.on("/save", HTTP_POST, [](AsyncWebServerRequest* request) {
        // 读取表单数据
        String ssid = request->arg("ssid");
        String password = request->arg("password");

        if (ssid.length() < 24) {
            request->redirect("/?error=SSID不可超过24字符长度");
            return;
        }

        if (password.length() < 24) {
            request->redirect("/?error=密码不可超过24字符长度");
            return;
        }

        // 保存WiFi配置
        WIFIConfig config;
        config.password = (uint8_t*)password.c_str();
        config.password = (uint8_t*)password.c_str();
        setWifiConfig(config);

        // 重启服务
        ESP.restart();
    });

    server.begin();
    delay(100);
    currentRunState = RunState::AP;
}

void stopWifiAp(void) {
    server.reset();
    server.end();
    dnsServer.stop();
    WiFi.disconnect();
    currentRunState = RunState::NO_CONNECT;
}

void splitArray(const uint8_t* source,
                uint8_t* dest1,
                uint8_t* dest2,
                uint8_t* dest3) {
    int i;
    // 拆分数组并将元素复制到目标数组
    for (i = 0; i < 8; i++) {
        dest1[i] = source[i];
        dest2[i] = source[i + 8];
        dest3[i] = source[i + 16];
    }
}

void put24(uint8_t address, uint8_t data[24]) {
    uint8_t index = address;
    uint8_t part1[8];
    uint8_t part2[8];
    uint8_t part3[8];
    splitArray(data, part1, part2, part3);
    eeprom.save(index, part1);
    index += 8;
    eeprom.save(index, part2);
    index += 8;
    eeprom.save(index, part3);
}

void setWifiConfig(WIFIConfig config) {
    put24(EEPROMAddressEnum::WIFI_CONF_S1, config.ssidName);
    put24(EEPROMAddressEnum::WIFI_CONF_P1, config.password);
}

void read24(uint8_t address, uint8_t* data) {
    uint8_t index = address;
    uint8_t part1[8];
    uint8_t part2[8];
    uint8_t part3[8];
    eeprom.read(index, part1);
    index += 8;
    eeprom.read(index, part2);
    index += 8;
    eeprom.read(index, part3);
    memcpy(data, part1, 8);
    memcpy(data + 8, part2, 8);
    memcpy(data + 16, part3, 8);
}

WIFIConfig getWifiAPConfig(void) {
    uint8_t ssid[24];
    uint8_t password[24];
    read24(EEPROMAddressEnum::WIFI_CONF_S1, ssid);
    read24(EEPROMAddressEnum::WIFI_CONF_P1, password);
    WIFIConfig wifi;
    wifi.password = password;
    wifi.ssidName = ssid;
    return wifi;
}

void unconnectWifiSTA() {
    WiFi.disconnect();
    currentRunState = RunState::NO_CONNECT;
}

void connectWifiSTA() {
    stopWifiAp();
    unconnectWifiSTA();
    WIFIConfig config = getWifiAPConfig();
    WiFi.mode(WIFI_MODE_STA);
    currentRunState = RunState::CONNECTING;
    WiFi.begin((char*)config.ssidName, (char*)config.password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi Connect STA Failed!\n");
        currentRunState = RunState::FAIL;
        return;
    }

    Serial.print("Wifi Connected IP Address: ");
    Serial.println(WiFi.localIP());
    currentRunState = RunState::CONNECTED;
}

void mainLoop(void) {
    if (currentRunState == RunState::AP) {
        dnsServer.processNextRequest();
    }
}
