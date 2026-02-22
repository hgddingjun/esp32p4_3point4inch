#include "dashboard_model.h"

const char* DashboardModel::TAG = "DashboardModel";

DashboardModel::DashboardModel()
    : speed_(0)
    , rpm_(0)
    , direction_(1)
    , running_(false)
    , task_handle_(nullptr)
    , mutex_(nullptr)
{
    mutex_ = xSemaphoreCreateMutex();
}

DashboardModel::~DashboardModel()
{
    stop();
    if (mutex_) {
        vSemaphoreDelete(mutex_);
        mutex_ = nullptr;
    }
}

void DashboardModel::start()
{
    if (running_) return;
    running_ = true;
    xTaskCreate(simulatorTask, "sim_task", 4096, this, 5, &task_handle_);
    ESP_LOGI(TAG, "模拟数据生成任务已启动");
}

void DashboardModel::stop()
{
    running_ = false;
    if (task_handle_) {
        vTaskDelay(pdMS_TO_TICKS(200));
        task_handle_ = nullptr;
    }
    ESP_LOGI(TAG, "模拟数据生成任务已停止");
}

int DashboardModel::getSpeed() const
{
    int val = 0;
    if (xSemaphoreTake(mutex_, pdMS_TO_TICKS(10)) == pdTRUE) {
        val = speed_;
        xSemaphoreGive(mutex_);
    }
    return val;
}

int DashboardModel::getRpm() const
{
    int val = 0;
    if (xSemaphoreTake(mutex_, pdMS_TO_TICKS(10)) == pdTRUE) {
        val = rpm_;
        xSemaphoreGive(mutex_);
    }
    return val;
}

/**
 * @brief 模拟器任务 - 生成三角波形的速度和转速数据
 * 
 * 速度从0线性增加到240，再线性减少到0，循环往复。
 * 转速与速度成正比: rpm = speed * 8 / 240
 */
void DashboardModel::simulatorTask(void* param)
{
    DashboardModel* model = static_cast<DashboardModel*>(param);
    const int speed_step = 2;  // 每次更新速度变化量（减小步长，更平滑）

    while (model->running_) {
        if (xSemaphoreTake(model->mutex_, pdMS_TO_TICKS(10)) == pdTRUE) {
            // 更新速度（三角波）
            model->speed_ += model->direction_ * speed_step;

            // 边界检测并反向
            if (model->speed_ >= MAX_SPEED) {
                model->speed_ = MAX_SPEED;
                model->direction_ = -1;
            } else if (model->speed_ <= 0) {
                model->speed_ = 0;
                model->direction_ = 1;
            }

            // 转速与速度成正比（高精度，0-8000）
            model->rpm_ = (model->speed_ * MAX_RPM_SCALED) / MAX_SPEED;

            xSemaphoreGive(model->mutex_);
        }

        vTaskDelay(pdMS_TO_TICKS(33));  // 每33ms更新一次（约30fps）
    }

    ESP_LOGI(model->TAG, "模拟器任务退出");
    vTaskDelete(NULL);
}
