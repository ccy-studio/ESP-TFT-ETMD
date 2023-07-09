#ifndef __UTIL__
#define __UTIL__

#include <Arduino.h>

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

#define V_DELAY_MS(ms) vTaskDelay(pdMS_TO_TICKS(ms))

#endif