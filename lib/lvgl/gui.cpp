/*
 * @Description: 
 * @Author: chenzedeng
 * @Date: 2023-07-11 10:23:36
 * @LastEditTime: 2023-07-11 15:16:29
 */
/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-10 20:12:00
 * @LastEditTime: 2023-07-11 15:05:07
 */
#include <gui.h>

static const uint16_t screenWidth = 240;
static const uint16_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * screenHeight / 10];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char* buf) {
    Serial.printf(buf);
    Serial.flush();
}
#endif

/* Display flushing */
void my_disp_flush(lv_disp_drv_t* disp,
                   const lv_area_t* area,
                   lv_color_t* color_p) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t*)&color_p->full, w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(disp);
}

void gui_setup() {
    lv_init();
#if LV_USE_LOG != 0
    lv_log_register_print_cb(
        my_print); /* register print function for debugging */
#endif

    tft.begin();        /* TFT init */
    tft.setRotation(3); /* Landscape orientation, flipped */

    lv_disp_draw_buf_init(&draw_buf, buf, NULL,
                          screenWidth * screenHeight / 10);

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    ui_init();

    Serial.println("Setup done");
}

void gui_thread(void* pvParameters) {
    gui_setup();
    while (1) {
        lv_timer_handler();
        gui_logic();
        V_DELAY_MS(FPS_DELAY);
    }
}