#ifndef __GUI__
#define __GUI__

#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "Adafruit_AHTX0.h"
#include "http_request.h"
#include "led_util.h"
#include "user_key.h"
#include "event_bus.h"
#include "lvgl/lvgl.h"
#include <TFT_eSPI.h>
#include "ui/ui.h"
#include <weather_util.h>

#define FPS_DELAY 5

void gui_thread(void *pvParameters);

void gui_logic();
#endif