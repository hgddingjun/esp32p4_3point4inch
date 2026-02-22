#ifndef _DASHBOARD_MODEL_H_
#define _DASHBOARD_MODEL_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

/**
 * @brief 仪表盘数据模型
 * 
 * 使用FreeRTOS任务模拟速度和转速数据的生成。
 * 速度范围: 0-240, 转速范围: 0-8
 */
class DashboardModel {
public:
    static constexpr int MAX_SPEED = 240;
    static constexpr int MAX_RPM   = 8;
    static constexpr int RPM_SCALE = 1000;                    // RPM精度放大因子
    static constexpr int MAX_RPM_SCALED = MAX_RPM * RPM_SCALE; // 8000

    DashboardModel();
    ~DashboardModel();

    /** 启动模拟数据生成任务 */
    void start();
    /** 停止模拟数据生成任务 */
    void stop();

    /** 获取当前速度 (0-240) */
    int getSpeed() const;
    /** 获取当前转速 (0-8000, 即RPM*1000, 高精度) */
    int getRpm() const;

private:
    static void simulatorTask(void* param);

    int speed_;           // 当前速度 0-240
    int rpm_;             // 当前转速 0-8
    int direction_;       // 1=加速, -1=减速
    bool running_;
    TaskHandle_t task_handle_;
    mutable SemaphoreHandle_t mutex_;

    static const char* TAG;
};

#endif // _DASHBOARD_MODEL_H_
