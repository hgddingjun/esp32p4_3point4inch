#include <cstdio>
#include "jd9365.h"

extern "C" void app_main(void)
{
    // 显示ESP32 Logo
    printf("   __    ___  ___ _____  __  ____\r\n");
    printf("   \\ \\  /   \\/ _ \\___ / / /_| ___|\r\n");
    printf("    \\ \\/ /\\ / (_) ||_ \\| '_ \\___ \\\r\n");
    printf("/\\_/ / /_// \\__, |__) | (_) |__) |\r\n");
    printf("\\___/___,'    /_/____/ \\___/____/\r\n");
    
    // 运行测试
    Jd9365 test;
    test.init();
    
    ESP_LOGI("jd9365 testing", "Show color bar pattern drawn by hardware");
    TEST_ESP_OK(esp_lcd_dpi_panel_set_pattern(*(test.m_LcdPanel), MIPI_DSI_PATTERN_BAR_VERTICAL));
    
    // 保持运行
    while (true) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
