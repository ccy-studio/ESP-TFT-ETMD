#ifndef __GUI__
#define __GUI__

#include "event_bus.h"
#include "lvgl/lvgl.h"
#include <TFT_eSPI.h>
#include "ui/ui.h"

void gui_thread(void *pvParameters);

#endif