// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.0
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_Main1_screen_init(void)
{
ui_Main1 = lv_obj_create(NULL);
lv_obj_clear_flag( ui_Main1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Main1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Main1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_tempInfo = lv_obj_create(ui_Main1);
lv_obj_set_width( ui_tempInfo, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_tempInfo, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_tempInfo, -55 );
lv_obj_set_y( ui_tempInfo, 88 );
lv_obj_set_align( ui_tempInfo, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_tempInfo,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_tempInfo, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_clear_flag( ui_tempInfo, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_tempInfo, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_tempInfo, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_tempInfo, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_tempInfo, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_tempLabP = lv_label_create(ui_tempInfo);
lv_obj_set_width( ui_tempLabP, LV_SIZE_CONTENT);  /// 50
lv_obj_set_height( ui_tempLabP, LV_SIZE_CONTENT);   /// 20
lv_obj_set_align( ui_tempLabP, LV_ALIGN_CENTER );
lv_label_set_text(ui_tempLabP,"温度:");
lv_label_set_recolor(ui_tempLabP,"true");
lv_obj_set_style_text_color(ui_tempLabP, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_tempLabP, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_letter_space(ui_tempLabP, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_line_space(ui_tempLabP, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_align(ui_tempLabP, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_tempLabP, &ui_font_HEITI21, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_tempVal = lv_label_create(ui_tempInfo);
lv_obj_set_width( ui_tempVal, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_tempVal, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_tempVal, -31 );
lv_obj_set_y( ui_tempVal, 94 );
lv_obj_set_align( ui_tempVal, LV_ALIGN_CENTER );
lv_label_set_text(ui_tempVal,"NA");
lv_obj_set_style_text_color(ui_tempVal, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_tempVal, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_tempVal, &lv_font_montserrat_20, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_humidityInfo = lv_obj_create(ui_Main1);
lv_obj_set_width( ui_humidityInfo, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_humidityInfo, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_humidityInfo, 57 );
lv_obj_set_y( ui_humidityInfo, 88 );
lv_obj_set_align( ui_humidityInfo, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_humidityInfo,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_humidityInfo, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_clear_flag( ui_humidityInfo, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_humidityInfo, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_humidityInfo, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_humidityInfo, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_humidityInfo, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_humidityP = lv_label_create(ui_humidityInfo);
lv_obj_set_width( ui_humidityP, LV_SIZE_CONTENT);  /// 50
lv_obj_set_height( ui_humidityP, LV_SIZE_CONTENT);   /// 20
lv_obj_set_align( ui_humidityP, LV_ALIGN_CENTER );
lv_label_set_text(ui_humidityP,"湿度:");
lv_label_set_recolor(ui_humidityP,"true");
lv_obj_set_style_text_color(ui_humidityP, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_humidityP, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_letter_space(ui_humidityP, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_line_space(ui_humidityP, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_align(ui_humidityP, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_humidityP, &ui_font_HEITI21, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_humidityVal = lv_label_create(ui_humidityInfo);
lv_obj_set_width( ui_humidityVal, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_humidityVal, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_humidityVal, -31 );
lv_obj_set_y( ui_humidityVal, 94 );
lv_obj_set_align( ui_humidityVal, LV_ALIGN_CENTER );
lv_label_set_text(ui_humidityVal,"NA");
lv_obj_set_style_text_color(ui_humidityVal, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_humidityVal, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_humidityVal, &lv_font_montserrat_20, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_homeTime = lv_obj_create(ui_Main1);
lv_obj_set_height( ui_homeTime, 60);
lv_obj_set_width( ui_homeTime, lv_pct(80));
lv_obj_set_align( ui_homeTime, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_homeTime,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_homeTime, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_clear_flag( ui_homeTime, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_homeTime, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_homeTime, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_homeTime, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_homeTime, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_hour = lv_label_create(ui_homeTime);
lv_obj_set_width( ui_hour, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_hour, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_hour, LV_ALIGN_CENTER );
lv_label_set_text(ui_hour,"NA");
lv_obj_set_style_text_color(ui_hour, lv_color_hex(0xF2BE45), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_hour, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_letter_space(ui_hour, 3, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_line_space(ui_hour, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_hour, &lv_font_montserrat_40, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_se1 = lv_label_create(ui_homeTime);
lv_obj_set_width( ui_se1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_se1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_se1, LV_ALIGN_CENTER );
lv_label_set_text(ui_se1,":");
lv_obj_set_style_text_color(ui_se1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_se1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_letter_space(ui_se1, 3, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_line_space(ui_se1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_se1, &lv_font_montserrat_30, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_min = lv_label_create(ui_homeTime);
lv_obj_set_width( ui_min, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_min, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_min, LV_ALIGN_CENTER );
lv_label_set_text(ui_min,"NA");
lv_obj_set_style_text_color(ui_min, lv_color_hex(0xFF4777), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_min, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_letter_space(ui_min, 3, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_line_space(ui_min, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_min, &lv_font_montserrat_40, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_se2 = lv_label_create(ui_homeTime);
lv_obj_set_width( ui_se2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_se2, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_se2, LV_ALIGN_CENTER );
lv_label_set_text(ui_se2,":");
lv_obj_set_style_text_color(ui_se2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_se2, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_letter_space(ui_se2, 3, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_line_space(ui_se2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_se2, &lv_font_montserrat_30, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_sec = lv_label_create(ui_homeTime);
lv_obj_set_width( ui_sec, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_sec, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_sec, LV_ALIGN_CENTER );
lv_label_set_text(ui_sec,"NA");
lv_obj_set_style_text_color(ui_sec, lv_color_hex(0xBDDD22), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_sec, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_letter_space(ui_sec, 3, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_line_space(ui_sec, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_sec, &lv_font_montserrat_40, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Image1 = lv_img_create(ui_Main1);
lv_img_set_src(ui_Image1, &ui_img_water_baoyu_png);
lv_obj_set_width( ui_Image1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Image1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Image1, -77 );
lv_obj_set_y( ui_Image1, -80 );
lv_obj_set_align( ui_Image1, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Image1, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_Image1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label1 = lv_label_create(ui_Main1);
lv_obj_set_width( ui_Label1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label1, -17 );
lv_obj_set_y( ui_Label1, -99 );
lv_obj_set_align( ui_Label1, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label1,"杨浦");
lv_obj_set_style_text_color(ui_Label1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Label1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Label1, &ui_font_HEITI21, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Label2 = lv_label_create(ui_Main1);
lv_obj_set_width( ui_Label2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label2, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label2, 31 );
lv_obj_set_y( ui_Label2, -99 );
lv_obj_set_align( ui_Label2, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label2,"小雨");
lv_obj_set_style_text_color(ui_Label2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Label2, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Label2, &ui_font_HEITI21, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Label3 = lv_label_create(ui_Main1);
lv_obj_set_width( ui_Label3, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label3, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label3, 7 );
lv_obj_set_y( ui_Label3, -71 );
lv_obj_set_align( ui_Label3, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label3,"当前温度24");
lv_obj_set_style_text_color(ui_Label3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Label3, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Label3, &ui_font_HEITI21, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Label5 = lv_label_create(ui_Main1);
lv_obj_set_width( ui_Label5, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label5, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label5, -3 );
lv_obj_set_y( ui_Label5, 39 );
lv_obj_set_align( ui_Label5, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label5,"CCY");
lv_obj_set_style_text_color(ui_Label5, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Label5, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Label5, &lv_font_montserrat_18, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_Main1, ui_event_Main1, LV_EVENT_ALL, NULL);

}
