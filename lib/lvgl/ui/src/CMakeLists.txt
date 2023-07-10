SET(SOURCES screens/ui_Main1.c
    ui.c
    ui_helpers.c
    images/ui_img_water_baoyu_png.c
    fonts/ui_font_HEITI21.c)

add_library(ui ${SOURCES})
