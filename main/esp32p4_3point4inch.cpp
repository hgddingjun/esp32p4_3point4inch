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

    jd9365_lcd.lockBspDisplay(0);
    // lv_demo_music();
    // lv_demo_benchmark();
    lv_demo_widgets();
    jd9365_lcd.unlockBspDisplay();


/****************************************************** unused ****************************************************** */
//#if 0
    // bsp_display_cfg_t cfg = {
    //     .lvgl_port_cfg = ESP_LVGL_PORT_INIT_CONFIG(),
    //     .buffer_size = BSP_LCD_DRAW_BUFF_SIZE,
    //     .double_buffer = BSP_LCD_DRAW_BUFF_DOUBLE,
    //     .flags = {
    //         .buff_dma = true,
    //         .buff_spiram = false,
    //         .sw_rotate = false,
    //     }
    // };

    // bsp_display_start_with_config(&cfg);
    // bsp_display_backlight_on();
    // bsp_display_brightness_set(50);

    // bsp_display_lock(0);

    // lv_demo_music();
    // lv_demo_benchmark();
    // lv_demo_widgets();

    // bsp_display_unlock();
//#else //////////////////////////////////////////////////////////////////////////////////////////

    // 运行测试
    // Jd9365 jd9365_lcd;
    // jd9365_lcd.initColorBar();

    // while (true) {
    //     #if 1
    //     TEST_ESP_OK(esp_lcd_dpi_panel_set_pattern(*(jd9365_lcd.m_LcdPanel), MIPI_DSI_PATTERN_BAR_VERTICAL));
    //     vTaskDelay(pdMS_TO_TICKS(3000));
    //     TEST_ESP_OK(esp_lcd_dpi_panel_set_pattern(*(jd9365_lcd.m_LcdPanel), MIPI_DSI_PATTERN_BAR_HORIZONTAL));
    //     vTaskDelay(pdMS_TO_TICKS(3000));
    //     #else
    //     vTaskDelay(pdMS_TO_TICKS(1000));
    //     #endif
    // }
//#endif
/****************************************************** unused ****************************************************** */
}
