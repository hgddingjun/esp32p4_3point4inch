#ifndef _DASHBOARD_VIEW_H_
#define _DASHBOARD_VIEW_H_

#include <cstdint>
#include <string>
#include "esp_log.h"
#include "lvgl.h"

/**********************
 *      TYPEDEFS
 **********************/
typedef enum {
    DISP_SMALL,
    DISP_MEDIUM,
    DISP_LARGE,
} disp_size_t;

const int16_t MAX_NEEDLE_NUM = 33;
const int16_t SPEED_AND_RPM_GAP = 396;

struct NeedleData {
    int16_t x;          // 指针在屏幕中的x坐标, 以图片的中心点为基准
    int16_t y;          // 指针在屏幕中的y坐标, 以图片的中心点为基准
    int16_t width;      // 指针宽度
    int16_t height;     // 指针高度
};

class DashboardView {
public:
    DashboardView();
    ~DashboardView();

    bool initialize();

    void updateView(uint32_t speed);

    lv_obj_t* getScreen() const {
        return screen_;
    }

private:
    void createBackground();

private:
    static void tabview_delete_event_cb(lv_event_t* e);

private:
    lv_obj_t* screen_;
    static const char* TAG;

    // 将静态成员变量改为普通成员变量，或者保留静态但正确定义
    disp_size_t disp_size_;  // 去掉static，改为普通成员变量
    lv_obj_t* tv_;
    const lv_font_t* font_large_;
    const lv_font_t* font_normal_;
    lv_style_t style_text_muted_;
    lv_style_t style_title_;
    lv_style_t style_icon_;
    lv_style_t style_bullet_;

};

#endif // _DASHBOARD_VIEW_H_