#include "dashboard_controller.h"
#include "bsp/display.h"
#include "esp_lvgl_port.h"

const char* DashboardController::TAG = "DashboardController";

DashboardController::DashboardController()
    : running_(false)
    , task_handle_(nullptr)
{
}

DashboardController::~DashboardController()
{
    stop();
}

bool DashboardController::initialize()
{
    // 持有LVGL显示锁，保护View初始化中的所有LVGL操作
    if (!lvgl_port_lock(0)) {
        ESP_LOGE(TAG, "获取LVGL显示锁失败");
        return false;
    }

    // 初始化View（创建UI元素）
    if (!view_.initialize()) {
        ESP_LOGE(TAG, "View初始化失败");
        lvgl_port_unlock();
        return false;
    }

    // 停止View自带的演示动画，由Controller驱动更新
    view_.stopRotationAnimation();

    lvgl_port_unlock();

    ESP_LOGI(TAG, "控制器初始化完成");
    return true;
}

void DashboardController::start()
{
    if (running_) return;
    running_ = true;

    // 启动Model模拟数据生成
    model_.start();

    // 启动Controller更新任务，周期性读取Model数据并刷新View
    xTaskCreate(updateTask, "ctrl_task", 4096, this, 5, &task_handle_);

    ESP_LOGI(TAG, "控制器已启动");
}

void DashboardController::stop()
{
    running_ = false;
    model_.stop();
    if (task_handle_) {
        vTaskDelay(pdMS_TO_TICKS(200));
        task_handle_ = nullptr;
    }
    ESP_LOGI(TAG, "控制器已停止");
}

/**
 * @brief 控制器更新任务
 * 
 * 周期性从Model获取最新速度和转速数据，
 * 通过LVGL显示锁保证线程安全地更新View。
 */
void DashboardController::updateTask(void* param)
{
    DashboardController* ctrl = static_cast<DashboardController*>(param);

    while (ctrl->running_) {
        // 从Model获取最新数据
        int speed = ctrl->model_.getSpeed();
        int rpm   = ctrl->model_.getRpm();

        // 获取LVGL显示锁后更新View
        if (lvgl_port_lock(100)) {
            ctrl->view_.updateSpeed(speed);
            ctrl->view_.updateRpm(rpm);
            lvgl_port_unlock();
        }

        vTaskDelay(pdMS_TO_TICKS(33));  // 每33ms刷新一次显示（约30fps）
    }

    ESP_LOGI(ctrl->TAG, "控制器更新任务退出");
    vTaskDelete(NULL);
}
