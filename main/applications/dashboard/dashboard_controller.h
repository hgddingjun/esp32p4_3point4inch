#ifndef _DASHBOARD_CONTROLLER_H_
#define _DASHBOARD_CONTROLLER_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "dashboard_model.h"
#include "dashboard_view.h"

/**
 * @brief 仪表盘控制器
 * 
 * MVC中的Controller角色。负责协调Model和View：
 * - 创建并持有Model和View
 * - 通过FreeRTOS任务周期性地从Model读取数据并更新View
 * - 处理LVGL显示锁以保证线程安全
 */
class DashboardController {
public:
    DashboardController();
    ~DashboardController();

    /** 初始化View界面（需在LVGL显示锁内调用） */
    bool initialize();

    /** 启动Model模拟和View更新任务 */
    void start();

    /** 停止所有任务 */
    void stop();

    DashboardView& getView() { return view_; }

private:
    static void updateTask(void* param);

    DashboardModel model_;
    DashboardView view_;
    bool running_;
    TaskHandle_t task_handle_;

    static const char* TAG;
};

#endif // _DASHBOARD_CONTROLLER_H_
