#include "sdmmc.h"

#define MOUNT_POINT "/sdcard"

#define PATH_MAX_CHAR_SIZE    256

const char* Sdmmc::TAG = "SDMMC_TF_CARD";

#ifdef CONFIG_EXAMPLE_DEBUG_PIN_CONNECTIONS
const char* names[] = {"CLK", "CMD", "D0", "D1", "D2", "D3"};
const int pins[] = {CONFIG_EXAMPLE_PIN_CLK,
                    CONFIG_EXAMPLE_PIN_CMD,
                    CONFIG_EXAMPLE_PIN_D0
                    #ifdef CONFIG_EXAMPLE_SDMMC_BUS_WIDTH_4
                    ,CONFIG_EXAMPLE_PIN_D1,
                    CONFIG_EXAMPLE_PIN_D2,
                    CONFIG_EXAMPLE_PIN_D3
                    #endif
                    };

const int pin_count = sizeof(pins)/sizeof(pins[0]);

#if CONFIG_EXAMPLE_ENABLE_ADC_FEATURE
const int adc_channels[] = {CONFIG_EXAMPLE_ADC_PIN_CLK,
                            CONFIG_EXAMPLE_ADC_PIN_CMD,
                            CONFIG_EXAMPLE_ADC_PIN_D0
                            #ifdef CONFIG_EXAMPLE_SDMMC_BUS_WIDTH_4
                            ,CONFIG_EXAMPLE_ADC_PIN_D1,
                            CONFIG_EXAMPLE_ADC_PIN_D2,
                            CONFIG_EXAMPLE_ADC_PIN_D3
                            #endif
                            };
#endif //CONFIG_EXAMPLE_ENABLE_ADC_FEATURE

pin_configuration_t config = {
    .names = names,
    .pins = pins,
#if CONFIG_EXAMPLE_ENABLE_ADC_FEATURE
    .adc_channels = adc_channels,
#endif
};
#endif //CONFIG_EXAMPLE_DEBUG_PIN_CONNECTIONS

// 检查是否为MP3文件（不区分大小写）
bool Sdmmc::isMp3File(const char* filename) {
    if(!filename) return false;
    const char* ext = strrchr(filename, '.');
    if(NULL != ext) {
        if(strcasecmp(ext, ".mp3") == 0) {
            return true;
        }
    }
    return false;
}


// 打印文件信息（支持中文）
void Sdmmc::printFileInfo(const char* filename, long size, const char* fullpath) {
    static int file_count = 0;
    file_count++;

    char size_str[32] = {0};
    if(size > 1024 * 1024) {
        snprintf(size_str, sizeof(size_str), "%.2f MB", size / (1024.0 * 1024.0));
    } else if(size > 1024) {
        snprintf(size_str, sizeof(size_str), "%.2f KB", size / 1024.0);
    } else {
        snprintf(size_str, sizeof(size_str), "%ld B", size);
    }

    ESP_LOGI(TAG, "MP3文件 [%d]: %s", file_count, filename);
    ESP_LOGI(TAG, "  路径: %s", fullpath);
    ESP_LOGI(TAG, "  大小: %s", size_str);
}

// 递归遍历目录查找MP3文件
void Sdmmc::listMp3FilesRecursive(const char *basePath) {
    struct dirent* entry;
    char path[PATH_MAX_CHAR_SIZE];
    struct stat statbuf;
    DIR* dir;

    //打开目录
    if(NULL == (dir = opendir(basePath))) {
        ESP_LOGE(TAG, "无法打开目录: %s", basePath);
        return;
    }

    //遍历目录项
    while( NULL != (entry = readdir(dir)) ) {
        //跳过"."和".."目录
        if( strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 ) {
            continue;
        }

        //构建完整路径
        //snprintf(path, sizeof(path), "%s/%s", basePath, entry->d_name);

        /* -------------------------------------------------------------------------- */
        // 安全地构建路径
        int base_len = strlcpy(path, basePath, sizeof(path));
        if (base_len >= sizeof(path) - 2) { // 预留空间给 '/' 和文件名
            ESP_LOGW(TAG, "基础路径过长: %s", basePath);
            continue;
        }

        // 添加路径分隔符
        if (path[base_len - 1] != '/') {
            if (strlcat(path, "/", sizeof(path)) >= sizeof(path)) {
                continue;
            }
        }

        // 添加文件名
        if (strlcat(path, entry->d_name, sizeof(path)) >= sizeof(path)) {
            ESP_LOGW(TAG, "完整路径过长: %s/%s", basePath, entry->d_name);
            continue;
        }
        /* -------------------------------------------------------------------------- */

        //获取文件状态
        if( stat(path, &statbuf) == -1 ) {
            ESP_LOGW(TAG, "无法获取文件状态: %s", path);
            continue;
        }

        if( S_ISDIR(statbuf.st_mode) ) {
            // 如果是目录，递归遍历
            ESP_LOGI(TAG, "进入目录: %s", path);
            listMp3FilesRecursive(path);
        } else if( S_ISREG(statbuf.st_mode) ) {
            //如果是文件，检查是否为MP3文件
            if( isMp3File(entry->d_name) ) {
                printFileInfo(entry->d_name, statbuf.st_size, path);
            }
        }
    }
    closedir(dir);
}


void Sdmmc::listMp3Files() {
    ESP_LOGI(TAG, "开始在SD卡中搜索MP3文件...");

    // 从挂载点开始递归搜索
    listMp3FilesRecursive(MOUNT_POINT);

    ESP_LOGI(TAG, "MP3文件搜索完成");
}

void Sdmmc::searchingFlash(void) {
    // 搜索SD卡中的MP3文件
    if(esp_flash_get_physical_size(NULL, &m_FlashSize) == ESP_OK) {
        m_FlashSize = m_FlashSize / (uint32_t)(1024 * 1024);
        printf("Flash size: %ld MB\n", m_FlashSize);
    } else {
        ESP_LOGI(TAG, "Get flash size failed.");
    }
}

void Sdmmc::init() {

    esp_err_t ret;

    ESP_LOGI(TAG, "SDMMC init");

    // Options for mounting the filesystem.
    // If format_if_mount_failed is set to true, SD card will be partitioned and
    // formatted in case when mounting fails.
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
#ifdef CONFIG_EXAMPLE_FORMAT_IF_MOUNT_FAILED
        .format_if_mount_failed = true,
#else
        .format_if_mount_failed = false,
#endif // EXAMPLE_FORMAT_IF_MOUNT_FAILED
        .max_files = 5,
        .allocation_unit_size = 16 * 1024,
        .disk_status_check_enable = false,
        .use_one_fat = false
    };
    sdmmc_card_t *card;
    const char* mount_point = MOUNT_POINT;
    ESP_LOGI(TAG, "Initializing SD card");

    // Use settings defined above to initialize SD card and mount FAT filesystem.
    // Note: esp_vfs_fat_sdmmc/sdspi_mount is all-in-one convenience functions.
    // Please check its source code and implement error recovery when developing
    // production applications.

    ESP_LOGI(TAG, "Using SDMMC peripheral");

    // By default, SD card frequency is initialized to SDMMC_FREQ_DEFAULT (20MHz)
    // For setting a specific frequency, use host.max_freq_khz (range 400kHz - 40MHz for SDMMC)
    // Example: for fixed frequency of 10MHz, use host.max_freq_khz = 10000;
    sdmmc_host_t host = SDMMC_HOST_DEFAULT();

    // For SoCs where the SD power can be supplied both via an internal or external (e.g. on-board LDO) power supply.
    // When using specific IO pins (which can be used for ultra high-speed SDMMC) to connect to the SD card
    // and the internal LDO power supply, we need to initialize the power supply first.
#if CONFIG_EXAMPLE_SD_PWR_CTRL_LDO_INTERNAL_IO
    sd_pwr_ctrl_ldo_config_t ldo_config = {
        .ldo_chan_id = CONFIG_EXAMPLE_SD_PWR_CTRL_LDO_IO_ID,
    };
    sd_pwr_ctrl_handle_t pwr_ctrl_handle = NULL;

    ret = sd_pwr_ctrl_new_on_chip_ldo(&ldo_config, &pwr_ctrl_handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to create a new on-chip LDO power control driver");
        return;
    }
    host.pwr_ctrl_handle = pwr_ctrl_handle;
#endif

    // This initializes the slot without card detect (CD) and write protect (WP) signals.
    // Modify slot_config.gpio_cd and slot_config.gpio_wp if your board has these signals.
    sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();

    // Set bus width to use:
#ifdef CONFIG_EXAMPLE_SDMMC_BUS_WIDTH_4
    slot_config.width = 4;
#else
    slot_config.width = 1;
#endif

    // On chips where the GPIOs used for SD card can be configured, set them in
    // the slot_config structure:
#ifdef CONFIG_SOC_SDMMC_USE_GPIO_MATRIX
    slot_config.clk = static_cast<gpio_num_t>(CONFIG_EXAMPLE_PIN_CLK);
    slot_config.cmd = static_cast<gpio_num_t>(CONFIG_EXAMPLE_PIN_CMD);
    slot_config.d0 = static_cast<gpio_num_t>(CONFIG_EXAMPLE_PIN_D0);
#ifdef CONFIG_EXAMPLE_SDMMC_BUS_WIDTH_4
    slot_config.d1 = static_cast<gpio_num_t>(CONFIG_EXAMPLE_PIN_D1);
    slot_config.d2 = static_cast<gpio_num_t>(CONFIG_EXAMPLE_PIN_D2);
    slot_config.d3 = static_cast<gpio_num_t>(CONFIG_EXAMPLE_PIN_D3);
#endif  // CONFIG_EXAMPLE_SDMMC_BUS_WIDTH_4
#endif  // CONFIG_SOC_SDMMC_USE_GPIO_MATRIX

    // Enable internal pullups on enabled pins. The internal pullups
    // are insufficient however, please make sure 10k external pullups are
    // connected on the bus. This is for debug / example purpose only.
    slot_config.flags |= SDMMC_SLOT_FLAG_INTERNAL_PULLUP;

    ESP_LOGI(TAG, "Mounting filesystem");
    ret = esp_vfs_fat_sdmmc_mount(mount_point, &host, &slot_config, &mount_config, &card);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount filesystem. "
                     "If you want the card to be formatted, set the EXAMPLE_FORMAT_IF_MOUNT_FAILED menuconfig option.");
        } else {
            ESP_LOGE(TAG, "Failed to initialize the card (%s). "
                     "Make sure SD card lines have pull-up resistors in place.", esp_err_to_name(ret));
#ifdef CONFIG_EXAMPLE_DEBUG_PIN_CONNECTIONS
            check_sd_card_pins(&config, pin_count);
#endif
        }
        return;
    }
    ESP_LOGI(TAG, "Filesystem mounted");

    // Card has been initialized, print its properties
    sdmmc_card_print_info(stdout, card);
    m_SDCardSize = ((uint64_t) card->csd.capacity) * card->csd.sector_size / (1024 * 1024);
    ESP_LOGI(TAG, "SD Card Size: %uMB", m_SDCardSize);

    listMp3Files();
}

void Sdmmc::deinit() {
    ESP_LOGI(TAG, "SDMMC deinit");
}

void Sdmmc::reset() {
    ESP_LOGI(TAG, "SDMMC reset");
}

void Sdmmc::suspend() {
    ESP_LOGI(TAG, "SDMMC suspend");
}

void Sdmmc::resume() {
    ESP_LOGI(TAG, "SDMMC resume");
}

Sdmmc::~Sdmmc() {
    ESP_LOGI(TAG, "SDMMC destructor");
}