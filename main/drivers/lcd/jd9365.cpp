#include "jd9365.h"
#include "esp_lcd_jd9365.h"


constexpr uint16_t LCD_H_RES = 800;
constexpr uint16_t LCD_V_RES = 800;
constexpr uint8_t LCD_BIT_PER_PIXEL = 24;
constexpr int PIN_NUM_LCD_RST = 27;
constexpr int PIN_NUM_BK_LIGHT = 26; // set to -1 if not used
constexpr bool LCD_BK_LIGHT_ON_LEVEL = 0; // 0 or 1
constexpr bool LCD_BK_LIGHT_OFF_LEVEL = !LCD_BK_LIGHT_ON_LEVEL;
constexpr uint8_t MIPI_DSI_LANE_NUM = 2;

// 像素格式选择
// #if (LCD_BIT_PER_PIXEL == 24)
// #define MIPI_DPI_PX_FORMAT     (LCD_COLOR_PIXEL_FORMAT_RGB888)
// #elif (LCD_BIT_PER_PIXEL == 18)
// #define MIPI_DPI_PX_FORMAT     (LCD_COLOR_PIXEL_FORMAT_RGB666)
// #elif (LCD_BIT_PER_PIXEL == 16)
// #define MIPI_DPI_PX_FORMAT     (LCD_COLOR_PIXEL_FORMAT_RGB565)
// #endif

constexpr uint32_t DELAY_TIME_MS = 3000;
constexpr uint32_t MIPI_DSI_PHY_PWR_LDO_CHAN = 3;
constexpr uint32_t MIPI_DSI_PHY_PWR_LDO_VOLTAGE_MV = 2500;

struct Jd9365LcdInitCmd {
    uint8_t cmd;
    std::vector<uint8_t> data;
    uint8_t data_bytes; // Number of data bytes; bit 7 = delay after set; 0xFF = end of cmds.
    uint8_t delay_ms;
};

const std::vector<Jd9365LcdInitCmd> lcd_init_cmds = {
    // Example initialization commands for JD9365
    {0xE0, {0x00}, 1, 0},

    {0xE1, {0x93}, 1, 0},
    {0xE2, {0x65}, 1, 0},
    {0xE3, {0xF8}, 1, 0},
    {0x80, {0x01}, 1, 0},

    {0xE0, {0x01}, 1, 0},

    {0x00, {0x00}, 1, 0},
    {0x01, {0x41}, 1, 0},
    {0x03, {0x10}, 1, 0},
    {0x04, {0x44}, 1, 0},

    {0x17, {0x00}, 1, 0},
    {0x18, {0xD0}, 1, 0},
    {0x19, {0x00}, 1, 0},
    {0x1A, {0x00}, 1, 0},
    {0x1B, {0xD0}, 1, 0},
    {0x1C, {0x00}, 1, 0},

    {0x24, {0xFE}, 1, 0},
    {0x35, {0x26}, 1, 0},

    {0x37, {0x09}, 1, 0},

    {0x38, {0x04}, 1, 0},
    {0x39, {0x08}, 1, 0},
    {0x3A, {0x0A}, 1, 0},
    {0x3C, {0x78}, 1, 0},
    {0x3D, {0xFF}, 1, 0},
    {0x3E, {0xFF}, 1, 0},
    {0x3F, {0xFF}, 1, 0},

    {0x40, {0x00}, 1, 0},
    {0x41, {0x64}, 1, 0},
    {0x42, {0xC7}, 1, 0},
    {0x43, {0x18}, 1, 0},
    {0x44, {0x0B}, 1, 0},
    {0x45, {0x14}, 1, 0},

    {0x55, {0x02}, 1, 0},
    {0x57, {0x49}, 1, 0},
    {0x59, {0x0A}, 1, 0},
    {0x5A, {0x1B}, 1, 0},
    {0x5B, {0x19}, 1, 0},

    {0x5D, {0x7F}, 1, 0},
    {0x5E, {0x56}, 1, 0},
    {0x5F, {0x43}, 1, 0},
    {0x60, {0x37}, 1, 0},
    {0x61, {0x33}, 1, 0},
    {0x62, {0x25}, 1, 0},
    {0x63, {0x2A}, 1, 0},
    {0x64, {0x16}, 1, 0},
    {0x65, {0x30}, 1, 0},
    {0x66, {0x2F}, 1, 0},
    {0x67, {0x32}, 1, 0},
    {0x68, {0x53}, 1, 0},
    {0x69, {0x43}, 1, 0},
    {0x6A, {0x4C}, 1, 0},
    {0x6B, {0x40}, 1, 0},
    {0x6C, {0x3D}, 1, 0},
    {0x6D, {0x31}, 1, 0},
    {0x6E, {0x20}, 1, 0},
    {0x6F, {0x0F}, 1, 0},

    {0x70, {0x7F}, 1, 0},
    {0x71, {0x56}, 1, 0},
    {0x72, {0x43}, 1, 0},
    {0x73, {0x37}, 1, 0},
    {0x74, {0x33}, 1, 0},
    {0x75, {0x25}, 1, 0},
    {0x76, {0x2A}, 1, 0},
    {0x77, {0x16}, 1, 0},
    {0x78, {0x30}, 1, 0},
    {0x79, {0x2F}, 1, 0},
    {0x7A, {0x32}, 1, 0},
    {0x7B, {0x53}, 1, 0},
    {0x7C, {0x43}, 1, 0},
    {0x7D, {0x4C}, 1, 0},
    {0x7E, {0x40}, 1, 0},
    {0x7F, {0x3D}, 1, 0},
    {0x80, {0x31}, 1, 0},
    {0x81, {0x20}, 1, 0},
    {0x82, {0x0F}, 1, 0},

    {0xE0, {0x02}, 1, 0},
    {0x00, {0x5F}, 1, 0},
    {0x01, {0x5F}, 1, 0},
    {0x02, {0x5E}, 1, 0},
    {0x03, {0x5E}, 1, 0},
    {0x04, {0x50}, 1, 0},
    {0x05, {0x48}, 1, 0},
    {0x06, {0x48}, 1, 0},
    {0x07, {0x4A}, 1, 0},
    {0x08, {0x4A}, 1, 0},
    {0x09, {0x44}, 1, 0},
    {0x0A, {0x44}, 1, 0},
    {0x0B, {0x46}, 1, 0},
    {0x0C, {0x46}, 1, 0},
    {0x0D, {0x5F}, 1, 0},
    {0x0E, {0x5F}, 1, 0},
    {0x0F, {0x57}, 1, 0},
    {0x10, {0x57}, 1, 0},
    {0x11, {0x77}, 1, 0},
    {0x12, {0x77}, 1, 0},
    {0x13, {0x40}, 1, 0},
    {0x14, {0x42}, 1, 0},
    {0x15, {0x5F}, 1, 0},

    {0x16, {0x5F}, 1, 0},
    {0x17, {0x5F}, 1, 0},
    {0x18, {0x5E}, 1, 0},
    {0x19, {0x5E}, 1, 0},
    {0x1A, {0x50}, 1, 0},
    {0x1B, {0x49}, 1, 0},
    {0x1C, {0x49}, 1, 0},
    {0x1D, {0x4B}, 1, 0},
    {0x1E, {0x4B}, 1, 0},
    {0x1F, {0x45}, 1, 0},
    {0x20, {0x45}, 1, 0},
    {0x21, {0x47}, 1, 0},
    {0x22, {0x47}, 1, 0},
    {0x23, {0x5F}, 1, 0},
    {0x24, {0x5F}, 1, 0},
    {0x25, {0x57}, 1, 0},
    {0x26, {0x57}, 1, 0},
    {0x27, {0x77}, 1, 0},
    {0x28, {0x77}, 1, 0},
    {0x29, {0x41}, 1, 0},
    {0x2A, {0x43}, 1, 0},
    {0x2B, {0x5F}, 1, 0},

    {0x2C, {0x1E}, 1, 0},
    {0x2D, {0x1E}, 1, 0},
    {0x2E, {0x1F}, 1, 0},
    {0x2F, {0x1F}, 1, 0},
    {0x30, {0x10}, 1, 0},
    {0x31, {0x07}, 1, 0},
    {0x32, {0x07}, 1, 0},
    {0x33, {0x05}, 1, 0},
    {0x34, {0x05}, 1, 0},
    {0x35, {0x0B}, 1, 0},
    {0x36, {0x0B}, 1, 0},
    {0x37, {0x09}, 1, 0},
    {0x38, {0x09}, 1, 0},
    {0x39, {0x1F}, 1, 0},
    {0x3A, {0x1F}, 1, 0},
    {0x3B, {0x17}, 1, 0},
    {0x3C, {0x17}, 1, 0},
    {0x3D, {0x17}, 1, 0},
    {0x3E, {0x17}, 1, 0},
    {0x3F, {0x03}, 1, 0},
    {0x40, {0x01}, 1, 0},
    {0x41, {0x1F}, 1, 0},

    {0x42, {0x1E}, 1, 0},
    {0x43, {0x1E}, 1, 0},
    {0x44, {0x1F}, 1, 0},
    {0x45, {0x1F}, 1, 0},
    {0x46, {0x10}, 1, 0},
    {0x47, {0x06}, 1, 0},
    {0x48, {0x06}, 1, 0},
    {0x49, {0x04}, 1, 0},
    {0x4A, {0x04}, 1, 0},
    {0x4B, {0x0A}, 1, 0},
    {0x4C, {0x0A}, 1, 0},
    {0x4D, {0x08}, 1, 0},
    {0x4E, {0x08}, 1, 0},
    {0x4F, {0x1F}, 1, 0},
    {0x50, {0x1F}, 1, 0},
    {0x51, {0x17}, 1, 0},
    {0x52, {0x17}, 1, 0},
    {0x53, {0x17}, 1, 0},
    {0x54, {0x17}, 1, 0},
    {0x55, {0x02}, 1, 0},
    {0x56, {0x00}, 1, 0},
    {0x57, {0x1F}, 1, 0},

    {0xE0, {0x02}, 1, 0},
    {0x58, {0x40}, 1, 0},
    {0x59, {0x00}, 1, 0},
    {0x5A, {0x00}, 1, 0},
    {0x5B, {0x30}, 1, 0},
    {0x5C, {0x01}, 1, 0},
    {0x5D, {0x30}, 1, 0},
    {0x5E, {0x01}, 1, 0},
    {0x5F, {0x02}, 1, 0},
    {0x60, {0x30}, 1, 0},
    {0x61, {0x03}, 1, 0},
    {0x62, {0x04}, 1, 0},
    {0x63, {0x04}, 1, 0},
    {0x64, {0xA6}, 1, 0},
    {0x65, {0x43}, 1, 0},
    {0x66, {0x30}, 1, 0},
    {0x67, {0x73}, 1, 0},
    {0x68, {0x05}, 1, 0},
    {0x69, {0x04}, 1, 0},
    {0x6A, {0x7F}, 1, 0},
    {0x6B, {0x08}, 1, 0},
    {0x6C, {0x00}, 1, 0},
    {0x6D, {0x04}, 1, 0},
    {0x6E, {0x04}, 1, 0},
    {0x6F, {0x88}, 1, 0},

    {0x75, {0xD9}, 1, 0},
    {0x76, {0x00}, 1, 0},
    {0x77, {0x33}, 1, 0},
    {0x78, {0x43}, 1, 0},

    {0xE0, {0x00}, 1, 0},

    {0x11, {0x00}, 1, 120},

    {0x29, {0x00}, 1, 20},
    {0x35, {0x00}, 1, 0},
};

void Jd9365::init() {
#if TEST_PIN_NUM_BK_LIGHT >= 0
        ESP_LOGI(TAG, "Turn on LCD backlight");

        gpio_config_t bk_gpio_config = {
            .pin_bit_mask = (1ULL << PIN_NUM_BK_LIGHT),
            .mode = GPIO_MODE_OUTPUT,
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .intr_type = GPIO_INTR_DISABLE,
            .hys_ctrl_mode = GPIO_HYS_SOFT_DISABLE  // 根据实际情况选择禁用或使能
        };

        TEST_ESP_OK(gpio_config(&bk_gpio_config));
        TEST_ESP_OK(gpio_set_level(static_cast<gpio_num_t>(PIN_NUM_BK_LIGHT), 
                                  LCD_BK_LIGHT_ON_LEVEL));
#endif

        // 为MIPI DSI PHY上电
#ifdef TEST_MIPI_DSI_PHY_PWR_LDO_CHAN
        ESP_LOGI(TAG, "MIPI DSI PHY Powered on");
        esp_ldo_channel_config_t ldo_mipi_phy_config = {
            .chan_id = TEST_MIPI_DSI_PHY_PWR_LDO_CHAN,
            .voltage_mv = TEST_MIPI_DSI_PHY_PWR_LDO_VOLTAGE_MV,
            .flags = {}
        };
        
        esp_ldo_channel_handle_t ldo_handle;
        TEST_ESP_OK(esp_ldo_acquire_channel(&ldo_mipi_phy_config, &ldo_handle));
        m_MipiPhy.reset(new esp_ldo_channel_handle_t(ldo_handle));
#endif

        ESP_LOGI(TAG, "Initialize MIPI DSI bus");
        esp_lcd_dsi_bus_config_t bus_config = JD9365_PANEL_BUS_DSI_2CH_CONFIG();
        
        esp_lcd_dsi_bus_handle_t dsi_bus_handle;
        TEST_ESP_OK(esp_lcd_new_dsi_bus(&bus_config, &dsi_bus_handle));
        m_DsiBus.reset(new esp_lcd_dsi_bus_handle_t(dsi_bus_handle));

        ESP_LOGI(TAG, "Install panel IO");
        esp_lcd_dbi_io_config_t dbi_config = JD9365_PANEL_IO_DBI_CONFIG();
        
        esp_lcd_panel_io_handle_t dbi_io_handle;
        TEST_ESP_OK(esp_lcd_new_panel_io_dbi(*m_DsiBus, &dbi_config, &dbi_io_handle));
        m_LcdPanelIo.reset(new esp_lcd_panel_io_handle_t(dbi_io_handle));

        ESP_LOGI(TAG, "Install LCD driver of jd9365");


#if 0
        esp_lcd_dpi_panel_config_t dpi_config = {
            .dpi_clk_src = MIPI_DSI_DPI_CLK_SRC_DEFAULT,
            .dpi_clock_freq_mhz = 80,

//#if (LCD_BIT_PER_PIXEL == 24)
            .pixel_format = LCD_COLOR_PIXEL_FORMAT_RGB888,
// #elif (LCD_BIT_PER_PIXEL == 18)
//             .pixel_format = LCD_COLOR_PIXEL_FORMAT_RGB666,
// #elif (LCD_BIT_PER_PIXEL == 16)
//             .pixel_format = LCD_COLOR_PIXEL_FORMAT_RGB565,
// #endif

            //.in_color_format = 0, // 根据实际设置，如果没有可用0或默认值
            //.out_color_format = 0, // 根据实际设置
            .num_fbs = 1,
            .video_timing = {
                .h_size = 800,
                .v_size = 800,
                .hsync_back_porch = 20,
                .hsync_pulse_width = 20,
                .hsync_front_porch = 40,
                .vsync_back_porch = 12,
                .vsync_pulse_width = 4,
                .vsync_front_porch = 24,
            },
            .flags = {
                .use_dma2d = true,
            }
        };
#endif



        esp_lcd_dpi_panel_config_t dpi_config = {
            .dpi_clk_src = MIPI_DSI_DPI_CLK_SRC_DEFAULT,
            .dpi_clock_freq_mhz = 80,
            //.virtual_channel = 0,
//#if (LCD_BIT_PER_PIXEL == 24)
            .pixel_format = LCD_COLOR_PIXEL_FORMAT_RGB888,
// #elif (LCD_BIT_PER_PIXEL == 18)
//             .pixel_format = LCD_COLOR_PIXEL_FORMAT_RGB666,
// #elif (LCD_BIT_PER_PIXEL == 16)
//             .pixel_format = LCD_COLOR_PIXEL_FORMAT_RGB565,
// #endif
            .num_fbs = 1,
            .video_timing = {
                .h_size = 800,
                .v_size = 800,
                .hsync_pulse_width=20,
                .hsync_back_porch=20,
                .hsync_front_porch=40,
                .vsync_pulse_width=4,
                .vsync_back_porch=12,
                .vsync_front_porch=24,
            },
            .flags = {
                .use_dma2d = true
            }
        };



        // 转换初始化命令格式
        std::vector<jd9365_lcd_init_cmd_t> init_cmds;
        for (const auto& cmd : lcd_init_cmds) {
            jd9365_lcd_init_cmd_t converted_cmd = {
                .cmd = cmd.cmd,
                .data = const_cast<uint8_t*>(cmd.data.data()), // 注意：这里需要const_cast
                .data_bytes = cmd.data_bytes,
                .delay_ms = cmd.delay_ms
            };
            init_cmds.push_back(converted_cmd);
        }
        
        jd9365_vendor_config_t vendor_config = {
            .init_cmds = init_cmds.data(),
            .init_cmds_size = static_cast<uint16_t>(init_cmds.size()),
            .mipi_config = {
                .dsi_bus = *m_DsiBus,
                .dpi_config = &dpi_config,
                .lane_num = MIPI_DSI_LANE_NUM,
            },
        };

        const esp_lcd_panel_dev_config_t panel_config = {
            .reset_gpio_num = PIN_NUM_LCD_RST,
            .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
            .bits_per_pixel = LCD_BIT_PER_PIXEL,
            //.data_endian = LCD_RGB_DATA_ENDIAN_BIG, // 或者根据实际设置
            .vendor_config = &vendor_config,
            //.flags = {
            //    .reset_active_high = 0, // 根据实际设置
            //}
        };

        esp_lcd_panel_handle_t panel_handle_ptr;
        TEST_ESP_OK(esp_lcd_new_panel_jd9365(*m_LcdPanelIo, &panel_config, &panel_handle_ptr));
        m_LcdPanel.reset(new esp_lcd_panel_handle_t(panel_handle_ptr));
        
        TEST_ESP_OK(esp_lcd_panel_reset(*m_LcdPanel));
        TEST_ESP_OK(esp_lcd_panel_init(*m_LcdPanel));
        TEST_ESP_OK(esp_lcd_panel_disp_on_off(*m_LcdPanel, true));

        SemaphoreHandle_t semaphore = xSemaphoreCreateBinary();
        TEST_ASSERT_NOT_NULL(semaphore);
        m_RefreshFinish.reset(new SemaphoreHandle_t(semaphore));
        
        esp_lcd_dpi_panel_event_callbacks_t cbs = {
            .on_color_trans_done = lcd_notify_refresh_ready,
        };
        TEST_ESP_OK(esp_lcd_dpi_panel_register_event_callbacks(*m_LcdPanel, &cbs, m_RefreshFinish.get()));
}

void Jd9365::deinit() {
    // 智能指针会自动释放资源
        m_LcdPanel.reset();
        m_LcdPanelIo.reset();
        m_DsiBus.reset();
        m_MipiPhy.reset();
        m_RefreshFinish.reset();

#if TEST_PIN_NUM_BK_LIGHT >= 0
        TEST_ESP_OK(gpio_reset_pin(static_cast<gpio_num_t>(PIN_NUM_BK_LIGHT)));
#endif

}

void Jd9365::reset() {

}
void Jd9365::suspend() {

}
void Jd9365::resume() {

}

// 绘制彩色条
void Jd9365::draw_color_bar(uint16_t h_res, uint16_t v_res) {
    uint8_t byte_per_pixel = (LCD_BIT_PER_PIXEL + 7) / 8;
    uint16_t row_line = v_res / byte_per_pixel / 8;
    
    // 使用vector管理内存
    std::vector<uint8_t> color(row_line * h_res * byte_per_pixel, 0);

    for (int j = 0; j < byte_per_pixel * 8; j++) {
        for (int i = 0; i < row_line * h_res; i++) {
            for (int k = 0; k < byte_per_pixel; k++) {
                color[i * byte_per_pixel + k] = (BIT(j) >> (k * 8)) & 0xff;
            }
        }
        
        TEST_ESP_OK(esp_lcd_panel_draw_bitmap(*m_LcdPanel, 0, j * row_line, 
                                                h_res, (j + 1) * row_line, color.data()));
        xSemaphoreTake(*m_RefreshFinish, portMAX_DELAY);
    }

    uint16_t color_line = row_line * byte_per_pixel * 8;
    uint16_t res_line = v_res - color_line;
    
    if (res_line) {
        for (int i = 0; i < res_line * h_res; i++) {
            for (int k = 0; k < byte_per_pixel; k++) {
                color[i * byte_per_pixel + k] = 0xff;
            }
        }
        
        TEST_ESP_OK(esp_lcd_panel_draw_bitmap(*m_LcdPanel, 0, color_line, 
                                                h_res, v_res, color.data()));
        xSemaphoreTake(*m_RefreshFinish, portMAX_DELAY);
    }
}

void Jd9365::rotate() {
    ESP_LOGI(TAG, "Initialize LCD device");
    init();

    ESP_LOGI(TAG, "Mirror the screen");
    for (size_t i = 0; i < 4; i++) {
        TEST_ASSERT_NOT_EQUAL(esp_lcd_panel_mirror(*m_LcdPanel, i & 2, i & 1), ESP_FAIL);

        ESP_LOGI(TAG, "Mirror: %d", i);
        draw_color_bar(LCD_H_RES, LCD_V_RES);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    ESP_LOGI(TAG, "Deinitialize LCD device");
    deinit();
}

void Jd9365::drawPattern() {
    ESP_LOGI(TAG, "Initialize LCD device");
    init();

    ESP_LOGI(TAG, "Show color bar pattern drawn by hardware");
    TEST_ESP_OK(esp_lcd_dpi_panel_set_pattern(*m_LcdPanel, MIPI_DSI_PATTERN_BAR_VERTICAL));
    vTaskDelay(pdMS_TO_TICKS(DELAY_TIME_MS));
    TEST_ESP_OK(esp_lcd_dpi_panel_set_pattern(*m_LcdPanel, MIPI_DSI_PATTERN_BAR_HORIZONTAL));
    vTaskDelay(pdMS_TO_TICKS(DELAY_TIME_MS));
    TEST_ESP_OK(esp_lcd_dpi_panel_set_pattern(*m_LcdPanel, MIPI_DSI_PATTERN_NONE));

    ESP_LOGI(TAG, "Deinitialize LCD device");
    deinit();
}

void Jd9365::drawColorBar(uint16_t h_res, uint16_t v_res) {
    ESP_LOGI(TAG, "Initialize LCD device");
    init();

    ESP_LOGI(TAG, "Show color bar drawn by software");
    draw_color_bar(LCD_H_RES, LCD_V_RES);
    vTaskDelay(pdMS_TO_TICKS(DELAY_TIME_MS));

    ESP_LOGI(TAG, "Deinitialize LCD device");
    deinit();
}


void Jd9365::run() {
    drawPattern();
    drawColorBar(LCD_H_RES, LCD_V_RES);
    rotate();
}

// 内存泄漏检测
constexpr size_t MEMORY_LEAK_THRESHOLD = 300;
static size_t before_free_8bit;
static size_t before_free_32bit;

void setUp(void) {
    before_free_8bit = heap_caps_get_free_size(MALLOC_CAP_8BIT);
    before_free_32bit = heap_caps_get_free_size(MALLOC_CAP_32BIT);
}

void tearDown(void) {
    size_t after_free_8bit = heap_caps_get_free_size(MALLOC_CAP_8BIT);
    size_t after_free_32bit = heap_caps_get_free_size(MALLOC_CAP_32BIT);
    unity_utils_check_leak(before_free_8bit, after_free_8bit, "8BIT", MEMORY_LEAK_THRESHOLD);
    unity_utils_check_leak(before_free_32bit, after_free_32bit, "32BIT", MEMORY_LEAK_THRESHOLD);
}

// 测试用例
extern "C" void test_jd9365_draw_pattern(void) {
    Jd9365 test;
    test.drawPattern();
}

extern "C" void test_jd9365_draw_color_bar(void) {
    Jd9365 test;
    test.drawColorBar(LCD_H_RES, LCD_V_RES);
}

extern "C" void test_jd9365_rotate(void) {
    Jd9365 test;
    test.rotate();
}



