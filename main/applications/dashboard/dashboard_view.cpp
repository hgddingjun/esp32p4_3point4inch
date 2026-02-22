#include "dashboard_view.h"

#include "assets/ui_font_speedFont.c"
LV_FONT_DECLARE(ui_font_speedFont);   // 声明外部字体

#include "assets/dashboard_bg.c"  // 引入背景图片
// 声明外部图片
LV_IMG_DECLARE(dashboard_bg);

#include "assets/rot_000.c"
LV_IMG_DECLARE(rot_000);
#include "assets/rot_007.c"
LV_IMG_DECLARE(rot_007);
#include "assets/rot_015.c"
LV_IMG_DECLARE(rot_015);
#include "assets/rot_023.c"
LV_IMG_DECLARE(rot_023);

#if 1
#include "assets/rot_030.c"
LV_IMG_DECLARE(rot_030);
#include "assets/rot_037.c"
LV_IMG_DECLARE(rot_037);
#include "assets/rot_045.c"
LV_IMG_DECLARE(rot_045);
#include "assets/rot_053.c"
LV_IMG_DECLARE(rot_053);
#include "assets/rot_060.c"
LV_IMG_DECLARE(rot_060);
#include "assets/rot_067.c"
LV_IMG_DECLARE(rot_067);
#include "assets/rot_075.c"
LV_IMG_DECLARE(rot_075);
#include "assets/rot_083.c"
LV_IMG_DECLARE(rot_083);
#include "assets/rot_090.c"
LV_IMG_DECLARE(rot_090);
#include "assets/rot_097.c"
LV_IMG_DECLARE(rot_097);
#include "assets/rot_105.c"
LV_IMG_DECLARE(rot_105);
#include "assets/rot_113.c"
LV_IMG_DECLARE(rot_113);
#include "assets/rot_120.c"
LV_IMG_DECLARE(rot_120);
#include "assets/rot_127.c"
LV_IMG_DECLARE(rot_127);
#include "assets/rot_135.c"
LV_IMG_DECLARE(rot_135);
#include "assets/rot_143.c"
LV_IMG_DECLARE(rot_143);
#include "assets/rot_150.c"
LV_IMG_DECLARE(rot_150);
#include "assets/rot_157.c"
LV_IMG_DECLARE(rot_157);
#include "assets/rot_165.c"
LV_IMG_DECLARE(rot_165);
#include "assets/rot_173.c"
LV_IMG_DECLARE(rot_173);
#include "assets/rot_180.c"
LV_IMG_DECLARE(rot_180);
#include "assets/rot_187.c"
LV_IMG_DECLARE(rot_187);
#include "assets/rot_195.c"
LV_IMG_DECLARE(rot_195);
#include "assets/rot_203.c"
LV_IMG_DECLARE(rot_203);
#include "assets/rot_210.c"
LV_IMG_DECLARE(rot_210);
#include "assets/rot_217.c"
LV_IMG_DECLARE(rot_217);
#include "assets/rot_225.c"
LV_IMG_DECLARE(rot_225);
#include "assets/rot_233.c"
LV_IMG_DECLARE(rot_233);
#include "assets/rot_240.c"
LV_IMG_DECLARE(rot_240);
#endif

const char* DashboardView::TAG = "DashboardView";

const int rpm[MAX_NEEDLE_NUM] = {
    0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8
};

const struct NeedleData rpmNeedle[MAX_NEEDLE_NUM] = {
    {126-SPEED_AND_RPM_GAP, 47, 250, 278, &rot_000}, //rot_000.png
    {121-SPEED_AND_RPM_GAP, 40, 235, 276, &rot_007}, //rot_007.png
    {114-SPEED_AND_RPM_GAP, 30, 224, 278, &rot_015}, //rot_015.png
    {107-SPEED_AND_RPM_GAP, 16, 211, 283, &rot_023}, //rot_023.png
    {99-SPEED_AND_RPM_GAP, 0, 197, 284, &rot_030}, //rot_030.png
    {107-SPEED_AND_RPM_GAP, -17, 212, 283, &rot_037}, //rot_037.png
    {114-SPEED_AND_RPM_GAP, -30, 224, 277, &rot_045}, //rot_045.png
    {120-SPEED_AND_RPM_GAP, -39, 236, 276, &rot_053}, //rot_053.png
    {125-SPEED_AND_RPM_GAP, -46, 251, 277, &rot_060}, //rot_060.png
    {132-SPEED_AND_RPM_GAP, -54, 263, 274, &rot_067}, //rot_067.png
    {139-SPEED_AND_RPM_GAP, -59, 269, 268, &rot_075}, //rot_075.png
    {146-SPEED_AND_RPM_GAP, -66, 274, 262, &rot_083}, //rot_083.png
    {151-SPEED_AND_RPM_GAP, -72, 277, 251, &rot_090}, //rot_090.png
    {161-SPEED_AND_RPM_GAP, -78, 276, 236, &rot_097}, //rot_097.png
    {170-SPEED_AND_RPM_GAP, -84, 278, 224, &rot_105}, //rot_105.png
    {182-SPEED_AND_RPM_GAP, -91, 283, 210, &rot_113}, //rot_113.png
    {198-SPEED_AND_RPM_GAP, -99, 284, 197, &rot_120}, //rot_120.png
    {215-SPEED_AND_RPM_GAP, -90, 283, 212, &rot_127}, //rot_127.png
    {228-SPEED_AND_RPM_GAP, -84, 278, 224, &rot_135}, //rot_135.png
    {238-SPEED_AND_RPM_GAP, -78, 276, 236, &rot_143}, //rot_143.png
    {245-SPEED_AND_RPM_GAP, -72, 277, 250, &rot_150}, //rot_150.png
    {253-SPEED_AND_RPM_GAP, -66, 274, 263, &rot_157}, //rot_157.png
    {258-SPEED_AND_RPM_GAP, -59, 268, 269, &rot_165}, //rot_165.png
    {264-SPEED_AND_RPM_GAP, -54, 262, 274, &rot_173}, //rot_173.png
    {270-SPEED_AND_RPM_GAP, -47, 250, 277, &rot_180}, //rot_180.png
    {276-SPEED_AND_RPM_GAP, -39, 236, 276, &rot_187}, //rot_187.png
    {283-SPEED_AND_RPM_GAP, -29, 224, 278, &rot_195}, //rot_195.png
    {289-SPEED_AND_RPM_GAP, -17, 213, 282, &rot_203}, //rot_203.png
    {297-SPEED_AND_RPM_GAP, 0, 197, 284, &rot_210}, //rot_210.png
    {290-SPEED_AND_RPM_GAP, 16, 212, 284, &rot_217}, //rot_217.png
    {283-SPEED_AND_RPM_GAP, 29, 224, 278, &rot_225}, //rot_225.png
    {276-SPEED_AND_RPM_GAP, 39, 234, 276, &rot_233}, //rot_233.png
    {271-SPEED_AND_RPM_GAP, 46, 251, 277, &rot_240}, //rot_240.png
};

const int speed[MAX_NEEDLE_NUM] = {
    0, 7, 15, 23, 30, 37, 45, 53, 60, 67, 75, 83, 90, 
    97, 105, 113, 120, 127, 135, 143, 150, 157, 165, 
    173, 180, 187, 195, 203, 210, 217, 225, 233, 240
};

const struct NeedleData speedNeedle[MAX_NEEDLE_NUM] = {
    {126, 47, 250, 278, &rot_000}, //rot_000.png
    {121, 40, 235, 276, &rot_007}, //rot_007.png
    {114, 30, 224, 278, &rot_015}, //rot_015.png
    {107, 16, 211, 283, &rot_023}, //rot_023.png
    {99, 0, 197, 284, &rot_030}, //rot_030.png
    {107, -17, 212, 283, &rot_037}, //rot_037.png
    {114, -30, 224, 277, &rot_045}, //rot_045.png
    {120, -39, 236, 276, &rot_053}, //rot_053.png
    {125, -46, 251, 277, &rot_060}, //rot_060.png
    {132, -54, 263, 274, &rot_067}, //rot_067.png
    {139, -59, 269, 268, &rot_075}, //rot_075.png
    {146, -66, 274, 262, &rot_083}, //rot_083.png
    {151, -72, 277, 251, &rot_090}, //rot_090.png
    {161, -78, 276, 236, &rot_097}, //rot_097.png
    {170, -84, 278, 224, &rot_105}, //rot_105.png
    {182, -91, 283, 210, &rot_113}, //rot_113.png
    {198, -99, 284, 197, &rot_120}, //rot_120.png
    {215, -90, 283, 212, &rot_127}, //rot_127.png
    {228, -84, 278, 224, &rot_135}, //rot_135.png
    {238, -78, 276, 236, &rot_143}, //rot_143.png
    {245, -72, 277, 250, &rot_150}, //rot_150.png
    {253, -66, 274, 263, &rot_157}, //rot_157.png
    {258, -59, 268, 269, &rot_165}, //rot_165.png
    {264, -54, 262, 274, &rot_173}, //rot_173.png
    {270, -47, 250, 277, &rot_180}, //rot_180.png
    {276, -39, 236, 276, &rot_187}, //rot_187.png
    {283, -29, 224, 278, &rot_195}, //rot_195.png
    {289, -17, 213, 282, &rot_203}, //rot_203.png
    {297, 0, 197, 284, &rot_210}, //rot_210.png
    {290, 16, 212, 284, &rot_217}, //rot_217.png
    {283, 29, 224, 278, &rot_225}, //rot_225.png
    {276, 39, 234, 276, &rot_233}, //rot_233.png
    {271, 46, 251, 277, &rot_240}, //rot_240.png
};

DashboardView::DashboardView()
    : screen_(nullptr)
    , disp_size_(DISP_SMALL)
    , tv_(nullptr)
    , font_large_(nullptr)
    , font_normal_(nullptr)
    , anim_running_(false)
    , valid_(true)          // 新增
    , current_speed_index_(0)
    , current_rpm_index_(0)
    , smooth_speed_f_(0.0f)
    , smooth_rpm_f_(0.0f)
    , label_rpm_(nullptr)
    , label_speed_(nullptr)
{
    // 将指针数组全部初始化为 nullptr
    for (int i = 0; i < MAX_NEEDLE_NUM; i++) {
        rpm_needle_[i] = nullptr;
        speed_needle_[i] = nullptr;
    }
    // 初始化样式
    lv_style_init(&style_text_muted_);
    lv_style_init(&style_title_);
    lv_style_init(&style_icon_);
    lv_style_init(&style_bullet_);
}

DashboardView::~DashboardView()
{
    // 先停止动画，确保回调不会再被调用
    lv_anim_del(this, (lv_anim_exec_xcb_t)animationCallBack);
    anim_running_ = false;
    valid_ = false;  // 之后再标记无效

    // 重置样式
    lv_style_reset(&style_text_muted_);
    lv_style_reset(&style_title_);
    lv_style_reset(&style_icon_);
    lv_style_reset(&style_bullet_);

    if (screen_) {
        //lv_obj_del(screen_);
        screen_ = nullptr;
    }
}

void DashboardView::createBackground() {
    int i=0;
    ESP_LOGI(TAG, "创建背景");

    lv_obj_set_style_bg_color(screen_, lv_color_black(), 0);
    
    // 创建背景图片对象
    image_bg_ = lv_image_create(screen_);
    if (image_bg_ == nullptr) {
        ESP_LOGE(TAG, "创建背景图片对象失败");
        return;
    }

    // 使用LV_IMG_DECLARE声明的图片数据
    lv_image_set_src(image_bg_, &dashboard_bg);
    
    // 设置图片位置（居中对齐）
    lv_obj_align(image_bg_, LV_ALIGN_CENTER, 0, 0);
    
    // 确保背景在最底层
    lv_obj_move_background(image_bg_);

    for(i=0; i<MAX_NEEDLE_NUM; i++) {
        rpm_needle_[i] = lv_image_create(screen_);
        if (rpm_needle_[i] == nullptr) {
            ESP_LOGE(TAG, "创建转速指针[%d]失败", i);
        } else {
            lv_image_set_src(rpm_needle_[i], rpmNeedle[i].image);
            lv_obj_align(rpm_needle_[i], LV_ALIGN_CENTER, rpmNeedle[i].x, rpmNeedle[i].y);
            if(i>0) lv_obj_add_flag(rpm_needle_[i], LV_OBJ_FLAG_HIDDEN);
        }

        speed_needle_[i] = lv_image_create(screen_);
        if (speed_needle_[i] == nullptr) {
            ESP_LOGE(TAG, "创建速度指针[%d]失败", i);
        } else {
            lv_image_set_src(speed_needle_[i], speedNeedle[i].image);
            lv_obj_align(speed_needle_[i], LV_ALIGN_CENTER, speedNeedle[i].x, speedNeedle[i].y);
            if(i>0) lv_obj_add_flag(speed_needle_[i], LV_OBJ_FLAG_HIDDEN);
        }
    }

    ESP_LOGI(TAG, "背景PNG图片加载完成");

    // 创建左侧数字标签
    label_rpm_ = lv_label_create(screen_);
    if (label_rpm_ == nullptr) {
        ESP_LOGE(TAG, "创建左侧标签失败");
    } else {
        lv_obj_set_style_text_font(label_rpm_, &ui_font_speedFont, 0);
        lv_label_set_text(label_rpm_, "5");                // 初始显示 "0"
        lv_obj_set_style_text_color(label_rpm_, lv_color_white(), 0);
        lv_obj_align(label_rpm_, LV_ALIGN_CENTER, -200, 0); // 偏移 (-200, 0)
    }

    // 创建右侧数字标签
    label_speed_ = lv_label_create(screen_);
    if (label_speed_ == nullptr) {
        ESP_LOGE(TAG, "创建右侧标签失败");
    } else {
        lv_obj_set_style_text_font(label_speed_, &ui_font_speedFont, 0);
        lv_label_set_text(label_speed_, "210");
        lv_obj_set_style_text_color(label_speed_, lv_color_white(), 0);
        lv_obj_align(label_speed_, LV_ALIGN_CENTER, 200, 0);  // 偏移 (200, 0)
    }

    ESP_LOGI(TAG, "数字标签创建完成");
}

bool DashboardView::initialize()
{
    screen_ = lv_screen_active(); //lv_obj_create(nullptr);
    if (!screen_) {
        ESP_LOGE(TAG, "创建屏幕失败!");
        return false;
    }

    createBackground();
    startRotationAnimation();
    return true;
}

void DashboardView::animationCallBack(void* var, int32_t v)
{
    DashboardView* view = (DashboardView*)var;
    if (!view || !view->valid_) return;   // 检查对象有效性

    //ESP_LOGI(view->TAG, "Animation callback, var=0x%08p, value=%d", var, v);

    // 检查索引范围
    if (v < 0 || v >= MAX_NEEDLE_NUM) return;
    uint8_t index = (uint8_t)v;

    // 隐藏旧的指针（需要检查指针非空）
    if (view->current_speed_index_ >= 0 && view->current_speed_index_ < MAX_NEEDLE_NUM) {
        lv_obj_t* old_speed_needle = view->speed_needle_[view->current_speed_index_];
        if (old_speed_needle != nullptr) {
            lv_obj_add_flag(old_speed_needle, LV_OBJ_FLAG_HIDDEN);
        } else {
            ESP_LOGE(view->TAG, "speed_needle_[%d] is null, animation skipped", view->current_speed_index_);
        }
    }

    if (view->current_rpm_index_ >= 0 && view->current_rpm_index_ < MAX_NEEDLE_NUM) {
        lv_obj_t* old_rpm_needle = view->rpm_needle_[view->current_rpm_index_];
        if (old_rpm_needle != nullptr) {
            lv_obj_add_flag(old_rpm_needle, LV_OBJ_FLAG_HIDDEN);
        } else {
            ESP_LOGE(view->TAG, "rpm_needle_[%d] is null, animation skipped", view->current_rpm_index_);
        }
    }

    // 显示新的指针
    lv_obj_t* new_speed_needle = view->speed_needle_[index];
    if (new_speed_needle != nullptr) {
        lv_obj_clear_flag(new_speed_needle, LV_OBJ_FLAG_HIDDEN);
    } else {
        ESP_LOGE(view->TAG, "speed_needle_[%d] is null, animation skipped", index);
    }

    lv_obj_t* new_rpm_needle = view->rpm_needle_[index];
    if (new_rpm_needle != nullptr) {
        lv_obj_clear_flag(new_rpm_needle, LV_OBJ_FLAG_HIDDEN);
    } else {
        ESP_LOGE(view->TAG, "rpm_needle_[%d] is null, animation skipped", index);
    }

    view->current_rpm_index_ = index;
    //ESP_LOGI(view->TAG, "Current rpm index set to %d", view->current_rpm_index_);
    view->current_speed_index_ = index;
    //ESP_LOGI(view->TAG, "Current speed index set to %d", view->current_speed_index_);


    if(view->label_speed_) {
        lv_label_set_text_fmt(view->label_speed_, "%d", speed[view->current_speed_index_]); // 更新速度标签
    } else {
        ESP_LOGE(view->TAG, "label_speed_ is null, cannot update speed value");
    }

    if(view->label_rpm_) {
        lv_label_set_text_fmt(view->label_rpm_, "%d", rpm[view->current_rpm_index_]);     // 更新转速标签
    } else {
        ESP_LOGE(view->TAG, "label_rpm_ is null, cannot update rpm value");
    }

}

void DashboardView::startRotationAnimation() {
    if (anim_running_ || !valid_) return;  // 防止重复启动或对象无效时启动

    ESP_LOGI(TAG, "Starting rotation animation");
    ESP_LOGI(TAG, "animationCallBack=0x%08p", (lv_anim_exec_xcb_t)animationCallBack);

    lv_anim_init(&anim_);
    lv_anim_set_var(&anim_, this);
    lv_anim_set_exec_cb(&anim_, (lv_anim_exec_xcb_t)animationCallBack);
    lv_anim_set_values(&anim_, 0, MAX_NEEDLE_NUM - 1);
    lv_anim_set_time(&anim_, 1000);
    lv_anim_set_playback_time(&anim_, 1000);
    lv_anim_set_repeat_count(&anim_, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_path_cb(&anim_, lv_anim_path_linear);

    lv_anim_start(&anim_);
    anim_running_ = true;
}

void DashboardView::stopRotationAnimation() {
    if (!anim_running_ /*|| !valid_*/) return;
    lv_anim_del(this, (lv_anim_exec_xcb_t)animationCallBack);
    anim_running_ = false;
}


void DashboardView::updateSpeed(int speed_value)
{
    // 将速度值(0-240)映射到指针索引(0-32)
    if (speed_value < 0) speed_value = 0;
    if (speed_value > 240) speed_value = 240;

    // 指数平滑滤波，消除离散跳变引起的卡顿
    smooth_speed_f_ += SMOOTH_FACTOR * ((float)speed_value - smooth_speed_f_);

    int new_index = (int)(smooth_speed_f_ * (MAX_NEEDLE_NUM - 1) / 240.0f + 0.5f);
    if (new_index >= MAX_NEEDLE_NUM) new_index = MAX_NEEDLE_NUM - 1;
    if (new_index < 0) new_index = 0;

    // 索引未变化时跳过更新，减少无效刷新
    if (new_index == current_speed_index_) return;

    // 先显示新指针再隐藏旧指针，避免闪烁
    if (speed_needle_[new_index]) {
        lv_obj_clear_flag(speed_needle_[new_index], LV_OBJ_FLAG_HIDDEN);
    }
    if (current_speed_index_ >= 0 && current_speed_index_ < MAX_NEEDLE_NUM) {
        if (speed_needle_[current_speed_index_]) {
            lv_obj_add_flag(speed_needle_[current_speed_index_], LV_OBJ_FLAG_HIDDEN);
        }
    }
    current_speed_index_ = new_index;

    // 更新速度数字标签
    if (label_speed_) {
        lv_label_set_text_fmt(label_speed_, "%d", speed_value);
    }
}

void DashboardView::updateRpm(int rpm_value)
{
    // rpm_value 现为高精度值 0-8000（即RPM*1000）
    if (rpm_value < 0) rpm_value = 0;
    if (rpm_value > 8000) rpm_value = 8000;

    // 指数平滑滤波，消除离散跳变引起的卡顿
    smooth_rpm_f_ += SMOOTH_FACTOR * ((float)rpm_value - smooth_rpm_f_);

    int new_index = (int)(smooth_rpm_f_ * (MAX_NEEDLE_NUM - 1) / 8000.0f + 0.5f);
    if (new_index >= MAX_NEEDLE_NUM) new_index = MAX_NEEDLE_NUM - 1;
    if (new_index < 0) new_index = 0;

    // 索引未变化时跳过更新，减少无效刷新
    if (new_index == current_rpm_index_) return;

    // 先显示新指针再隐藏旧指针，避免闪烁
    if (rpm_needle_[new_index]) {
        lv_obj_clear_flag(rpm_needle_[new_index], LV_OBJ_FLAG_HIDDEN);
    }
    if (current_rpm_index_ >= 0 && current_rpm_index_ < MAX_NEEDLE_NUM) {
        if (rpm_needle_[current_rpm_index_]) {
            lv_obj_add_flag(rpm_needle_[current_rpm_index_], LV_OBJ_FLAG_HIDDEN);
        }
    }
    current_rpm_index_ = new_index;

    // 更新转速数字标签（显示实际RPM 0-8）
    if (label_rpm_) {
        lv_label_set_text_fmt(label_rpm_, "%d", rpm_value / 1000);
    }
}

void DashboardView::tabview_delete_event_cb(lv_event_t* e)
{
    // 注意：这是一个静态函数，不能访问非静态成员
    // 如果需要重置样式，需要确保样式对象是静态的
    // 或者通过其他方式处理
    
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_DELETE) {
        // 由于样式现在是成员变量，不能在这里重置
        // 重置操作应该在析构函数中进行
        // lv_style_reset(&style_text_muted);
        // lv_style_reset(&style_title);
        // lv_style_reset(&style_icon);
        // lv_style_reset(&style_bullet);
    }
}