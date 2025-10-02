#include <cstdio>
#include "jd9365.h"
#include "sdmmc.h"

extern void sdmmc_run(void);

extern "C" void app_main(void)
{
    // 显示ESP32 Logo
    printf("   __    ___  ___ _____  __  ____\r\n");
    printf("   \\ \\  /   \\/ _ \\___ / / /_| ___|\r\n");
    printf("    \\ \\/ /\\ / (_) ||_ \\| '_ \\___ \\\r\n");
    printf("/\\_/ / /_// \\__, |__) | (_) |__) |\r\n");
    printf("\\___/___,'    /_/____/ \\___/____/\r\n");


    // 设置区域设置以支持中文（如果ESP-IDF支持）
    // setlocale(LC_ALL, "zh_CN.UTF-8");

    ESP_LOGI("Main", "启动SD卡和显示系统...");
    Sdmmc sd;
    sd.init();
    sd.searchingFlash();

    // 运行测试
    Jd9365 jd9365_lcd;
    jd9365_lcd.init();

    ESP_LOGI("Main", "系统初始化完成，开始显示测试...");

    // 保持运行
    while (true) {
        #if 1
        TEST_ESP_OK(esp_lcd_dpi_panel_set_pattern(*(jd9365_lcd.m_LcdPanel), MIPI_DSI_PATTERN_BAR_VERTICAL));
        vTaskDelay(pdMS_TO_TICKS(3000));
        TEST_ESP_OK(esp_lcd_dpi_panel_set_pattern(*(jd9365_lcd.m_LcdPanel), MIPI_DSI_PATTERN_BAR_HORIZONTAL));
        vTaskDelay(pdMS_TO_TICKS(3000));
        #else
        vTaskDelay(pdMS_TO_TICKS(1000));
        #endif
    }
}
