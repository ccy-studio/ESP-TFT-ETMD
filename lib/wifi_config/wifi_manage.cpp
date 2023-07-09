#include "wifi_manage.h"
#include "at24cx.h"

DNSServer dnsServer;
AsyncWebServer server(80);
I2CMemory eeprom(AT24CX_ADDRESS);

WIFIConfig gloabWifiConfig;

volatile static RunState currentRunState;

void handleRequest(AsyncWebServerRequest* request) {
    request->redirect("http://192.168.1.1/");
}

void initWifiManage() {
    uint8_t* ssid = (uint8_t*)calloc(EEPROMAddressEnum::WIFI_CONF_SSID_LEN,
                                     sizeof(uint8_t));
    uint8_t* password = (uint8_t*)calloc(
        EEPROMAddressEnum::WIFI_CONF_PASSWORD_LEN, sizeof(uint8_t));

    if (ssid == NULL || password == NULL) {
        printf("ERROR: getWifiAPConfig内存分配失败");
        return;
    }
    gloabWifiConfig.password = password;
    gloabWifiConfig.ssidName = ssid;
}

void freeWifiManage() {
    if (gloabWifiConfig.password != NULL) {
        free(gloabWifiConfig.password);
    }
    if (gloabWifiConfig.ssidName != NULL) {
        free(gloabWifiConfig.ssidName);
    }
}

RunState getAPState(void) {
    return currentRunState;
}

void resetWifiConcig(void) {
    eeprom.clear(EEPROMAddressEnum::WIFI_CONF_SSID,
                 EEPROMAddressEnum::WIFI_CONF_SSID_LEN);
    eeprom.clear(EEPROMAddressEnum::WIFI_CONF_PASSWORD,
                 EEPROMAddressEnum::WIFI_CONF_PASSWORD_LEN);

    memset(gloabWifiConfig.password, 0x00,
           EEPROMAddressEnum::WIFI_CONF_PASSWORD_LEN);
    memset(gloabWifiConfig.ssidName, 0x00,
           EEPROMAddressEnum::WIFI_CONF_SSID_LEN);
}

void startRunWifiAPConfig(void) {
    IPAddress localIP(192, 168, 1, 1);   // 热点IP地址
    IPAddress gateway(192, 168, 1, 1);   // 路由主地址
    IPAddress subnet(255, 255, 255, 0);  // 子网掩码
                                         // 获取设备编码
    uint64_t macAddress = ESP.getEfuseMac();
    char macString[13];
    snprintf(macString, sizeof(macString), "%02X%02X%02X%02X%02X%02X",
             (uint8_t)(macAddress >> 40), (uint8_t)(macAddress >> 32),
             (uint8_t)(macAddress >> 24), (uint8_t)(macAddress >> 16),
             (uint8_t)(macAddress >> 8), (uint8_t)macAddress);
    char ssid[32];
    snprintf(ssid, sizeof(ssid), "ETMD-%s", macString);
    WiFi.softAP(ssid);
    WiFi.softAPConfig(localIP, gateway, subnet);
    dnsServer.start(53, "*", WiFi.softAPIP());

    // 设置请求处理程序
    server.onNotFound(handleRequest);

    // server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);
    server.on("/", [](AsyncWebServerRequest* request) {
        AsyncResponseStream* response =
            request->beginResponseStream("text/html");
        response->print(
            "<html>\n"
            "<head>\n"
            "  <meta charset=\"UTF-8\">\n"
            "  <title>设置WiFi</title>\n"
            "  <style>\n"
            "    body {\n"
            "      font-family: Arial, sans-serif;\n"
            "      text-align: center;\n"
            "    }\n"
            "\n"
            "    h1 {\n"
            "      margin-top: 30px;\n"
            "    }\n"
            "\n"
            "    form {\n"
            "      display: inline-block;\n"
            "      text-align: left;\n"
            "      margin-top: 30px;\n"
            "    }\n"
            "\n"
            "    label {\n"
            "      display: block;\n"
            "      margin-bottom: 10px;\n"
            "    }\n"
            "\n"
            "    input[type=\"text\"],\n"
            "    input[type=\"password\"] {\n"
            "      width: 200px;\n"
            "      padding: 5px;\n"
            "      border: 1px solid #ccc;\n"
            "      border-radius: 4px;\n"
            "    }\n"
            "\n"
            "    input[type=\"submit\"] {\n"
            "      margin-top: 10px;\n"
            "      padding: 8px 15px;\n"
            "      background-color: #4CAF50;\n"
            "      color: white;\n"
            "      border: none;\n"
            "      border-radius: 4px;\n"
            "      cursor: pointer;\n"
            "    }\n"
            "  </style>\n"
            "</head>\n"
            "<body>\n"
            "  <h1>设置WiFi</h1>\n"
            "\n");

        if (request->hasParam("error")) {
            AsyncWebParameter* p = request->getParam("error");
            const char* errorStr = p->value().c_str();
            response->printf("<h2 style=\"color\":red;>%s</h2>", errorStr);
        }

        response->print(
            "  <form method=\"post\" action=\"/save\">\n"
            "    <label for=\"ssid\">WiFi名称:</label>\n"
            "    <input type=\"text\" id=\"ssid\" name=\"ssid\" required>\n"
            "\n"
            "    <label for=\"password\">WiFi密码:</label>\n"
            "    <input type=\"password\" id=\"password\" name=\"password\" "
            "required>\n"
            "\n"
            "    <input type=\"submit\" value=\"保存\">\n"
            "  </form>\n"
            "</body>\n"
            "</html>");
        request->send(response);
    });

    // 处理保存配置的请求
    server.on("/save", HTTP_POST, [](AsyncWebServerRequest* request) {
        // 读取表单数据
        String ssid = request->arg("ssid");
        String password = request->arg("password");

        if (ssid.length() > EEPROMAddressEnum::WIFI_CONF_SSID_LEN) {
            request->redirect("/?error=SSID不可超过24字符长度");
            return;
        }

        if (password.length() > EEPROMAddressEnum::WIFI_CONF_PASSWORD_LEN) {
            request->redirect("/?error=密码不可超过24字符长度");
            return;
        }
        password.trim();
        ssid.trim();

        printf("打印获取保存的数据:SSID:%s, PWD:%s\n", ssid, password);
        // 保存WiFi配置
        resetWifiConcig();
        WIFIConfig config;
        config.ssidName = (uint8_t*)ssid.c_str();
        config.password = (uint8_t*)password.c_str();
        setWifiConfig(config);

        printf("保存WIFI成功\n");

        WIFIConfig wifiConfig = getWifiAPConfig();
        printf("获取保存的WIFIConfig-> SSID:%s PWD:%s \n", wifiConfig.ssidName,
               wifiConfig.password);

        AsyncResponseStream* response =
            request->beginResponseStream("text/html");
        response->print("<h1>保存成功正在连接....<h1>");
        request->send(response);
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

void setWifiConfig(WIFIConfig config) {
    eeprom.write_page(EEPROMAddressEnum::WIFI_CONF_PASSWORD, config.password,
                      EEPROMAddressEnum::WIFI_CONF_PASSWORD_LEN);
    eeprom.write_page(EEPROMAddressEnum::WIFI_CONF_SSID, config.ssidName,
                      EEPROMAddressEnum::WIFI_CONF_SSID_LEN);

    memcpy(gloabWifiConfig.password, config.password,
           EEPROMAddressEnum::WIFI_CONF_PASSWORD_LEN);
    memcpy(gloabWifiConfig.ssidName, config.ssidName,
           EEPROMAddressEnum::WIFI_CONF_SSID_LEN);
}

WIFIConfig getWifiAPConfig(void) {
    eeprom.read_page(EEPROMAddressEnum::WIFI_CONF_PASSWORD,
                     gloabWifiConfig.password,
                     EEPROMAddressEnum::WIFI_CONF_PASSWORD_LEN);
    eeprom.read_page(EEPROMAddressEnum::WIFI_CONF_SSID,
                     gloabWifiConfig.ssidName,
                     EEPROMAddressEnum::WIFI_CONF_SSID_LEN);
    return gloabWifiConfig;
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