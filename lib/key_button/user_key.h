/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-09 13:28:37
 * @LastEditTime: 2023-07-10 21:03:46
 */
#ifndef __USER_KEY__
#define __USER_KEY__

#include "util.h"

//如果你想打印Log日志请去掉注释
#define DEBUG_USER_KEY

#define ADC_KEY_PIN GPIO_NUM_0

#define ADC_KEY_ACTION_H 1  // 按键1  580~650
#define ADC_KEY_ACTION_L 2  // 按键2 1470~1490
#define ADC_KEY_ACTION_R 3  // 按键3 2200~2400

#define ADC_KEY_GROUP_HL 12  // 组合按键 1和2同时按下460~480

typedef struct {
    u8 keyId;        // 按键ID
    u8 isPress;      // 是否按下
    u8 isPressLong;  // 是否长按
    u32 tickCount;
    u16 adcVal;
} UserKey;

typedef void (*UserKeyFun_t)(UserKey key);

void user_key_thread(void* pvParameters);

int registerListener(UserKeyFun_t listener);

#endif