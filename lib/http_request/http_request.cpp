/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-10 10:46:38
 * @LastEditTime: 2023-07-11 23:07:33
 */
#include <http_request.h>
// #include <UrlEncode.h>

HTTPClient requestClient;
HttpRequest httpRequest;

String HttpRequest::getRequestUrl(const char* url, RequestMap* params, u8 len) {
    String requestUrl = url;
    if (len > 0) {
        requestUrl += "?";
        for (uint8_t i = 0; i < len; i++) {
            requestUrl += params[i].key;
            requestUrl += "=";
            requestUrl += params[i].value;
            if (i < len - 1) {
                requestUrl += "&";
            }
        }
    }
    printf("Return UrlParams: %s\n", requestUrl.c_str());
    return requestUrl;
}

String HttpRequest::get(const char* url, RequestMap* params, u8 len) {
    String response;
    if (WiFi.status() == WL_CONNECTED) {
        requestClient.begin(getRequestUrl(url, params, len));
        requestClient.addHeader("Content-Type",
                                "application/x-www-form-urlencoded");
        int httpResponseCode = requestClient.GET();
        if (httpResponseCode == HTTP_CODE_OK) {
            response = requestClient.getString();
        }
        requestClient.end();
    } else {
        printf("WIFI UnConnect! \n");
    }
    printf("Send Get ResponseStr:%s\n", response.c_str());
    return response;
}

String HttpRequest::postBody(const char* url, RequestMap* params, u8 len) {
    StaticJsonDocument<DEFAULT_JSON_SIZE> jsonDoc;
    for (uint8_t i = 0; i < len; i++) {
        jsonDoc[params[i].key] = params[i].value;
    }
    String requestBody;
    serializeJson(jsonDoc, requestBody);
    String response;
    if (WiFi.status() == WL_CONNECTED) {
        requestClient.addHeader("Content-Type", "application/json");
        int httpResponseCode = requestClient.POST(requestBody);
        if (httpResponseCode == HTTP_CODE_OK) {
            response = requestClient.getString();
        }
    }
    return response;
}