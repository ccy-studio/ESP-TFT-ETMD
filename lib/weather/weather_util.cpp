/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-11 22:17:16
 * @LastEditTime: 2023-07-11 23:39:03
 */
#include <weather_util.h>

const char api_url[] = "https://api.seniverse.com/v3/weather/now.json";

char weahterLocation[50];

WeatherResponse getWeatherNowInfo() {
    WeatherResponse weatherResponse;
    RequestMap requestParams[4] = {{"key", API_KEY},
                                   {"location", ""},
                                   {"language", "zh-Hans"},
                                   {"unit", "c"}};
    strcpy(requestParams[1].value, weahterLocation);
    String responseStr = httpRequest.get(api_url, requestParams, 4);
    if (responseStr != NULL && !responseStr.isEmpty()) {
        StaticJsonDocument<512> jsonDoc;
        DeserializationError error = deserializeJson(jsonDoc, responseStr);
        if (error) {
            Serial.print("Deserialization error: ");
            Serial.println(error.c_str());
        } else {
            JsonObject results_0 = jsonDoc["results"][0];
            strcpy(weatherResponse.text, results_0["now"]["text"]);
            weatherResponse.code = results_0["now"]["code"];
            strcpy(weatherResponse.temperature,
                   results_0["now"]["temperature"]);
        }
    }
    return weatherResponse;
}
