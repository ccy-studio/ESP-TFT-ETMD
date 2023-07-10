#ifndef __EVENT_BUS__
#define __EVENT_BUS__

#include <util.h>
#include "event_constant.h"

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