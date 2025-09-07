#ifndef _JD9365_H_
#define _JD9365_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_mipi_dsi.h"
#include "esp_ldo_regulator.h"
#include "esp_dma_utils.h"
#include "unity.h"
#include "unity_test_runner.h"
#include "unity_test_utils_memory.h"

#include "drivers.h"

#include <vector>
#include <memory>

class Jd9365 : public Drivers {
    public:
        std::unique_ptr<esp_ldo_channel_handle_t, void(*)(esp_ldo_channel_handle_t*)> m_MipiPhy;
        std::unique_ptr<esp_lcd_panel_handle_t, void(*)(esp_lcd_panel_handle_t*)> m_LcdPanel;
        std::unique_ptr<esp_lcd_dsi_bus_handle_t, void(*)(esp_lcd_dsi_bus_handle_t*)> m_DsiBus;
        std::unique_ptr<esp_lcd_panel_io_handle_t, void(*)(esp_lcd_panel_io_handle_t*)> m_LcdPanelIo;
        std::unique_ptr<SemaphoreHandle_t, void(*)(SemaphoreHandle_t*)> m_RefreshFinish;

    public:
        Jd9365(): m_MipiPhy(nullptr, deleteLdoChannel),
                  m_LcdPanel(nullptr, deleteLcdPanel),
                  m_DsiBus(nullptr, deleteDsiBus),
                  m_LcdPanelIo(nullptr, deleteLcdPanelIo),
                  m_RefreshFinish(nullptr, deleteSemaphore) {}

        void init() override;
        void deinit() override;
        void reset() override;
        void suspend() override;
        void resume() override;
        ~Jd9365() {}

        void drawColorBar(uint16_t h_res, uint16_t v_res);
        void drawPattern();
        void rotate();
        void run();
        void draw_color_bar(uint16_t h_res, uint16_t v_res);

        static IRAM_ATTR bool lcd_notify_refresh_ready(
                                            esp_lcd_panel_handle_t panel, 
                                            esp_lcd_dpi_panel_event_data_t* edata, 
                                            void* user_ctx
                                        )
        {
            auto refresh_finish = static_cast<SemaphoreHandle_t*>(user_ctx);
            BaseType_t need_yield = pdFALSE;
            
            if (refresh_finish && *refresh_finish) {
                xSemaphoreGiveFromISR(*refresh_finish, &need_yield);
            }

            return (need_yield == pdTRUE);
        }

    private:
        static constexpr const char* TAG =  "jd9365_driver";

        static void deleteLdoChannel(esp_ldo_channel_handle_t* handle) {
            if (handle && *handle) {
                esp_ldo_release_channel(*handle);
            }
        }

        static void deleteLcdPanel(esp_lcd_panel_handle_t* handle) {
            if (handle && *handle) {
                esp_lcd_panel_del(*handle);
            }
        }

        static void deleteDsiBus(esp_lcd_dsi_bus_handle_t* handle) {
            if (handle && *handle) {
                esp_lcd_del_dsi_bus(*handle);
            }
        }

        static void deleteLcdPanelIo(esp_lcd_panel_io_handle_t* handle) {
            if (handle && *handle) {
                esp_lcd_panel_io_del(*handle);
            }
        }

        static void deleteSemaphore(SemaphoreHandle_t* handle) {
            if (handle && *handle) {
                vSemaphoreDelete(*handle);
            }
        }
        
};
#endif