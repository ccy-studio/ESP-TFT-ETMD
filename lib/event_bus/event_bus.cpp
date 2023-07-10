/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-10 10:18:35
 * @LastEditTime: 2023-07-10 20:34:17
 */
#include <event_bus.h>

typedef struct {
    EventBusFun_t funt;
    u8 sourceId;
} Bus;
// Bus订阅者容器
static Bus busArr[BUS_COUNT];
static int busArrIndex = -1;

void freeEvent(Event event) {
    if (event.data != NULL) {
        free(event.data);
    }
}

u8 registerListener(EventBusFun_t funt, u8 soruceId) {
    busArrIndex++;
    busArr[busArrIndex] = Bus{funt, soruceId};
    return busArrIndex;
}

void sendEvent(Event event) {
    for (int i = 0; i < BUS_COUNT; i++) {
        Bus b = busArr[i];
        if (event.targetId) {
            if (event.targetId == b.sourceId) {
                b.funt(event);
#ifdef BUS_AUTO_RELEASE
                freeEvent(event);
#endif
                break;
            }
        } else {
            b.funt(event);
#ifdef BUS_AUTO_RELEASE
            freeEvent(event);
#endif
        }
    }
}

u8* createMemory(u8 len) {
    if (!len) {
        return NULL;
    }
    u8* buf = (u8*)calloc(len, sizeof(u8));
    return buf;
}