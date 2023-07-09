/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-09 13:01:43
 * @LastEditTime: 2023-07-09 22:44:54
 */
#include <led_util.h>
#include "user_key.h"

volatile static bool openState = false;

volatile static unsigned int mode = LED_MODE_AUTO_1;

static u16 delayMs = 500;

static void led_keyEvent(UserKey key) {
    if (key.isPress == 1) {
        if (key.keyId == ADC_KEY_ACTION_H) {
            delayMs = 500;
        } else if (key.keyId == ADC_KEY_ACTION_L) {
            delayMs = 100;
        }
    }
}

void led_thread(void* pvParameters) {
    pinMode(LED_PIN, OUTPUT);
    registerListener(led_keyEvent);
    while (1) {
        // Serial.print("Task stack high water mark: ");
        // Serial.println(uxTaskGetStackHighWaterMark(NULL));
        if (mode == LED_MODE_MANUAL) {
            digitalWrite(LED_PIN, openState ? LOW : HIGH);
        } else if (mode == LED_MODE_AUTO_1) {
            digitalWrite(LED_PIN, !digitalRead(LED_PIN));
            V_DELAY_MS(delayMs);
        }
    }
}

void led_open() {
    openState = true;
}

void led_close() {
    openState = false;
}

void led_delay_ms(u16 ms) {
    delayMs = ms;
}

void led_mode(unsigned int setMode) {
    mode = setMode;
}