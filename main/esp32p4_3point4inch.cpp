
#include <cstdio>
#include "jd9365.h"
#include "sdmmc.h"
//#include "spiffs.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
//#include "nvs_flash.h"
//#include "nvs.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_check.h"
#include "esp_memory_utils.h"
#include "lvgl.h"
#include "bsp/esp-bsp.h"
#include "bsp/display.h"
#include "bsp_board_extra.h"
#include "lv_demos.h"

#include "dashboard_view.h"

#include "dashboard_bg.h"

LV_IMG_DECLARE(dashboard_bg);

//extern void sdmmc_run(void);

extern "C" void app_main(void)
{
    // 显示ESP32 Logo
    printf("   __    ___  ___ _____  __  ____\r\n");
    printf("   \\ \\  /   \\/ _ \\___ / / /_| ___|\r\n");
    printf("    \\ \\/ /\\ / (_) ||_ \\| '_ \\___ \\\r\n");
    printf("/\\_/ / /_// \\__, |__) | (_) |__) |\r\n");
    printf("\\___/___,'    /_/____/ \\___/____/\r\n");

    // 设置区域设置以支持中文(如果ESP-IDF支持)
    // setlocale(LC_ALL, "zh_CN.UTF-8");
    //ESP_LOGI("Main", "启动SPIFFS文件系统...");
    //Spiffs spiffs;
    //spiffs.init();

    ESP_LOGI("Main", "启动SD卡和显示系统...");
    Sdmmc sd;
    sd.init();
    sd.searchingFlash();

    // 运行测试
    Jd9365 jd9365_lcd;
    jd9365_lcd.init();

    ESP_LOGI("Main", "系统初始化完成，开始测试...");

    #if 1
    DashboardView dashboardView;

    jd9365_lcd.lockBspDisplay(0);
    // lv_demo_music();
    //lv_demo_benchmark();
    //lv_demo_widgets();
    //lv_demo_keypad_encoder();

    // 初始化LVGL后，获取屏幕并设置背景颜色
    lv_obj_t * scr = lv_screen_active();
    lv_obj_set_style_bg_color(scr, lv_color_black(), 0);

    // 然后创建图片并显示
    lv_obj_t * img = lv_img_create(scr);
    lv_img_set_src(img, &dashboard_bg);
    lv_obj_center(img);

    //dashboardView.initialize();
    jd9365_lcd.unlockBspDisplay();
    #endif

}

