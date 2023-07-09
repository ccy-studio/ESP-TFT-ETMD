#ifndef __LED_UTIL_
#define __LED_UTIL_

#include "util.h"


#define LED_PIN GPIO_NUM_2

#define LED_MODE_MANUAL 0  // 手动模式
#define LED_MODE_AUTO_1 1  // 自动模式一

void led_thread(void *pvParameters);

void led_open();

void led_close();

void led_mode(unsigned int setMode);

void led_delay_ms(u16 ms);

#endif