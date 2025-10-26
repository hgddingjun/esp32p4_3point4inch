#include "spiffs.h"

const char* Spiffs::TAG = "SPIFFS_STORGE";

void Spiffs::init() {
    
    esp_err_t ret;

    ESP_LOGI(TAG, "SPIFFS init");

    esp_vfs_spiffs_conf_t conf = {
        .base_path = SPIFFS_BASE_PATH,
        .partition_label = "spiffs",
        .max_files = 5,
        .format_if_mount_failed = true
    };

    // Use settings defined above to initialize and mount SPIFFS filesystem.
    // Note: esp_vfs_spiffs_register is an all-in-one convenience function.
    // Please check its source code and implement error recovery when developing
    // production applications.

    ret = esp_vfs_spiffs_register(&conf);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount or format SPIFFS filesystem");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            ESP_LOGE(TAG, "Failed to find SPIFFS partition");
        } else {
            ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
        return;
    }

    size_t total = 0, used = 0;
    ret = esp_spiffs_info(NULL, &total, &used);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
    } else {
        ESP_LOGI(TAG, "SPIFFS Partition size: total: %d, used: %d", total, used);
    }
}

void Spiffs::deinit() {
    ESP_LOGI(TAG, "SPIFFS deinit");
}

void Spiffs::reset() {
    ESP_LOGI(TAG, "SPIFFS reset");
}

void Spiffs::suspend() {
    ESP_LOGI(TAG, "SPIFFS suspend");
}

void Spiffs::resume() {
    ESP_LOGI(TAG, "SPIFFS resume");
}

Spiffs::~Spiffs() {
    ESP_LOGI(TAG, "SPIFFS destructor");
}

bool Spiffs::checkFileExist(const char* path) {
    FILE* f = fopen(path, "r");
    if (f == NULL) {
        return false;
    } else {
        fclose(f);
        return true;
    }
}
