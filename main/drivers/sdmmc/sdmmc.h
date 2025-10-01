#ifndef _SDMMC_H_
#define _SDMMC_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/sdmmc_host.h"
#include "driver/sdmmc_defs.h"
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "sd_pwr_ctrl.h"
#include "sd_pwr_ctrl_by_on_chip_ldo.h"
#include "sdmmc_cmd.h"
#include "esp_flash.h"

#include <sys/stat.h>

#include "drivers.h"

class Sdmmc : public Drivers {
    public:
        void init() override;
        void deinit() override;
        void reset() override;
        void suspend() override;
        void resume() override;
        virtual ~Sdmmc();

    public:
        uint32_t getSDCardSize() { return m_SDCardSize; }
        uint32_t getFlashSize() { return m_FlashSize; }
        void searchingFlash();

    private:
        static const char* TAG;
        uint32_t m_SDCardSize = 0;
        uint32_t m_FlashSize = 0;
};

#endif /* _SDMMC_H_ */