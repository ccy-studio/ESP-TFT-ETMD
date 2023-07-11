#include <weather_util.h>


const char api_url[] = "https://api.seniverse.com/v3/weather/now.json";

// 当前位置
char weahterLocation[20];

WeatherResponse getWeatherNowInfo() {
     WeatherResponse weatherResponse;
    RequestMap requestParams[] = {{"key", API_KEY},
                                  {"location", *weahterLocation},
                                  {"language", "zh-Hans"},
                                  {"unit", "c"}};
    String responseStr = httpRequest.get(api_url, requestParams, 4);
    if (responseStr != NULL && !responseStr.isEmpty()) {
        StaticJsonDocument<DEFAULT_JSON_SIZE> jsonDoc;
        DeserializationError error = deserializeJson(jsonDoc, responseStr);
        if (error) {
            Serial.print("Deserialization error: ");
            Serial.println(error.c_str());
        } else {
            JsonArray results = jsonDoc["results"];
            JsonObject weatherData = results[0]["now"];

            strncpy(weatherResponse.text, weatherData["text"].as<const char*>(),
                    sizeof(weatherResponse.text));
            weatherResponse.code = weatherData["code"].as<uint8_t>();
            strncpy(weatherResponse.temperature,
                    weatherData["temperature"].as<const char*>(),
                    sizeof(weatherResponse.temperature));
        }
    }
    return weatherResponse;
}
