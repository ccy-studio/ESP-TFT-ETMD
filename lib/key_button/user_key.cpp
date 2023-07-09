/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-09 13:28:43
 * @LastEditTime: 2023-07-09 22:27:38
 */
#include <user_key.h>

#define MAX_LEN 3
#define FREQUENCY 100
#define LONG_PRESS 20

static UserKeyFun_t subscriber[MAX_LEN];
static int _index = -0;

u32 lastTime;
u8 lastKey;
int delayCount;

void sendEvent(UserKey key) {
#ifdef DEBUG_USER_KEY
    printf("SendEvent===>> Id:%d, isPress:%d, isPressLong:%d, tickCount:%ld\n",
           key.keyId, key.isPress, key.isPressLong, key.tickCount);
#endif
    for (int i = 0; i < MAX_LEN; i++) {
        UserKeyFun_t item = subscriber[i];
        if (item && item != NULL) {
            item(key);
        }
    }
}

void checkBtn(int key) {
    if (lastKey != key) {
        lastKey = key;
        delayCount = 0;
        lastTime = micros();
        // 发送首次按下事件
        UserKey uk;
        uk.isPress = 1;
        uk.tickCount = micros();
        uk.keyId = key;
        sendEvent(uk);
    } else {
        if (delayCount == LONG_PRESS) {
            // 发送长按的事件
            UserKey uk;
            uk.isPressLong = 1;
            uk.tickCount = micros();
            uk.keyId = key;
            sendEvent(uk);
        }
    }
}

void user_key_thread(void* pvParameters) {
    pinMode(ADC_KEY_PIN, INPUT);

    while (1) {
        // Serial.print("Task stack high water mark: ");
        // Serial.println(uxTaskGetStackHighWaterMark(NULL));
        V_DELAY_MS(FREQUENCY);
        u16 adcVal = analogRead(ADC_KEY_PIN);
        // printf("ADC Val==>> %ld\n", adcVal);
        delayCount++;
        if (adcVal >= 580 && adcVal <= 650) {
            // 按键1按下了
            checkBtn(ADC_KEY_ACTION_H);
        } else if (adcVal >= 1470 && adcVal <= 1490) {
            // 按键2按下了
            checkBtn(ADC_KEY_ACTION_L);
        } else if (adcVal >= 2200 && adcVal <= 2400) {
            // 按键3按下了
            checkBtn(ADC_KEY_ACTION_R);
        } else if (adcVal >= 460 && adcVal <= 480) {
            // 组合按键-1和2同时按下
            checkBtn(ADC_KEY_GROUP_HL);
        } else if (adcVal > 4000) {
            // 全部释放
            if (lastKey) {
                UserKey uk;
                uk.tickCount = micros();
                uk.keyId = lastKey;
                sendEvent(uk);
                lastKey = 0;
            }
        }
    }
}

int registerListener(UserKeyFun_t listener) {
    _index++;
    subscriber[_index] = listener;
    return _index;
}
