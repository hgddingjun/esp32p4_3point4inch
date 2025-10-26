#ifndef _SPIFFS_H_

#define _SPIFFS_H_

#include "drivers.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_system.h"
#include "esp_spiffs.h"
#include "esp_log.h"
#include "esp_timer.h"

//#include "lcd_driver.h"

#define SPIFFS_BASE_PATH "/spiffs"

class Spiffs : public Drivers {
    public:
        void init() override;
        void deinit() override;
        void reset() override;
        void suspend() override;
        void resume() override;
        virtual ~Spiffs();

    private:
        static const char* TAG;
        bool checkFileExist(const char* path);
};



#endif /* _SPIFFS_H_ */