/*
 * @Description: 
 * @Author: chenzedeng
 * @Date: 2023-07-10 19:51:52
 * @LastEditTime: 2023-07-10 20:31:36
 */
#ifndef __EVENT_BUS__
#define __EVENT_BUS__

#include <util.h>

#define BUS_COUNT 3
//是否自动释放
#define BUS_AUTO_RELEASE

typedef struct {
    u8 eventId;
    u8 targetId;
    u8 sourceId;
    u8* data;
    size_t dataLen;
} Event;

typedef void (*EventBusFun_t)(Event event);

void freeEvent(Event event);

u8 registerListener(EventBusFun_t funt, u8 soruceId);

void sendEvent(Event event);

/**
 * 分配内存
 */
u8* createMemory(u8 len);

#endif