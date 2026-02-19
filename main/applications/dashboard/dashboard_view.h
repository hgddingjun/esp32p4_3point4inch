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
    const void * image; // 指向指针图片的指针
};

class DashboardView {
public:
    DashboardView();
    ~DashboardView();

    bool initialize();

    void updateView(uint32_t speed);
    void startRotationAnimation();
    void stopRotationAnimation();
    static void animationCallBack(void* var, int32_t v);

    lv_obj_t* getScreen() const {
        return screen_;
    }

private:
    void createBackground();

private:
    static void tabview_delete_event_cb(lv_event_t* e);

private:
    lv_obj_t* screen_;
    lv_obj_t* image_bg_;
    lv_obj_t* rpm_needle_[MAX_NEEDLE_NUM];
    lv_obj_t* speed_needle_[MAX_NEEDLE_NUM];

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

    lv_anim_t anim_;
    bool anim_running_;
    bool valid_;          // 新增，标记对象有效
    int current_speed_index_;
    int current_rpm_index_;

    lv_obj_t* label_rpm_;      //位置 (-200, 0)
    lv_obj_t* label_speed_;    //位置 ( 200, 0)

};

#endif // _DASHBOARD_VIEW_H_