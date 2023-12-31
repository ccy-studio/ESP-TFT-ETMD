/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-10 10:46:32
 * @LastEditTime: 2023-07-10 11:20:58
 */
#ifndef __HTTP_REQUEST_
#define __HTTP_REQUEST_

#include <ArduinoJson.h>
#include "HTTPClient.h"
#include "util.h"

#define DEFAULT_JSON_SIZE 256

typedef struct {
    char key[20];
    char value[50];
} RequestMap;

class HttpRequest {
   public:
    String get(const char* url, RequestMap* params, u8 len);
    String postBody(const char* url, RequestMap* params, u8 len);
    String getRequestUrl(const char* url, RequestMap* params, u8 len);
};

extern HttpRequest httpRequest;

#endif