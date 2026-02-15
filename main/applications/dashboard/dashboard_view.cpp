#include "dashboard_view.h"

#include "assets/dashboard_bg.c"  // 引入背景图片
// 声明外部图片
LV_IMG_DECLARE(dashboard_bg);

const char* DashboardView::TAG = "DashboardView";

// 不需要再定义静态成员变量了，因为已经改为普通成员变量

const struct NeedleData rpmNeedle[MAX_NEEDLE_NUM] = {
    {126-SPEED_AND_RPM_GAP, 47, 250, 278}, //rot_000.png
    {121-SPEED_AND_RPM_GAP, 40, 235, 276}, //rot_007.png
    {114-SPEED_AND_RPM_GAP, 30, 224, 278}, //rot_015.png
    {107-SPEED_AND_RPM_GAP, 16, 211, 283}, //rot_023.png
    {99-SPEED_AND_RPM_GAP, 0, 197, 284}, //rot_030.png
    {107-SPEED_AND_RPM_GAP, -17, 212, 283}, //rot_037.png
    {114-SPEED_AND_RPM_GAP, -30, 224, 277}, //rot_045.png
    {120-SPEED_AND_RPM_GAP, -39, 236, 276}, //rot_053.png
    {125-SPEED_AND_RPM_GAP, -46, 251, 277}, //rot_060.png
    {132-SPEED_AND_RPM_GAP, -54, 263, 274}, //rot_067.png
    {139-SPEED_AND_RPM_GAP, -59, 269, 268}, //rot_075.png
    {146-SPEED_AND_RPM_GAP, -66, 274, 262}, //rot_083.png
    {151-SPEED_AND_RPM_GAP, -72, 277, 251}, //rot_090.png
    {161-SPEED_AND_RPM_GAP, -78, 276, 236}, //rot_097.png
    {170-SPEED_AND_RPM_GAP, -84, 278, 224}, //rot_105.png
    {182-SPEED_AND_RPM_GAP, -91, 283, 210}, //rot_113.png
    {198-SPEED_AND_RPM_GAP, -99, 284, 197}, //rot_120.png
    {215-SPEED_AND_RPM_GAP, -90, 283, 212}, //rot_127.png
    {228-SPEED_AND_RPM_GAP, -84, 278, 224}, //rot_135.png
    {238-SPEED_AND_RPM_GAP, -78, 276, 236}, //rot_143.png
    {245-SPEED_AND_RPM_GAP, -72, 277, 250}, //rot_150.png
    {253-SPEED_AND_RPM_GAP, -66, 274, 263}, //rot_157.png
    {258-SPEED_AND_RPM_GAP, -59, 268, 269}, //rot_165.png
    {264-SPEED_AND_RPM_GAP, -54, 262, 274}, //rot_173.png
    {270-SPEED_AND_RPM_GAP, -47, 250, 277}, //rot_180.png
    {276-SPEED_AND_RPM_GAP, -39, 236, 276}, //rot_187.png
    {283-SPEED_AND_RPM_GAP, -29, 224, 278}, //rot_195.png
    {289-SPEED_AND_RPM_GAP, -17, 213, 282}, //rot_203.png
    {297-SPEED_AND_RPM_GAP, 0, 197, 284}, //rot_210.png
    {290-SPEED_AND_RPM_GAP, 16, 212, 284}, //rot_217.png
    {283-SPEED_AND_RPM_GAP, 29, 224, 278}, //rot_225.png
    {276-SPEED_AND_RPM_GAP, 39, 234, 276}, //rot_233.png
    {271-SPEED_AND_RPM_GAP, 46, 251, 277}, //rot_240.png
};

const struct NeedleData speedNeedle[MAX_NEEDLE_NUM] = {
    {126, 47, 250, 278}, //rot_000.png
    {121, 40, 235, 276}, //rot_007.png
    {114, 30, 224, 278}, //rot_015.png
    {107, 16, 211, 283}, //rot_023.png
    {99, 0, 197, 284}, //rot_030.png
    {107, -17, 212, 283}, //rot_037.png
    {114, -30, 224, 277}, //rot_045.png
    {120, -39, 236, 276}, //rot_053.png
    {125, -46, 251, 277}, //rot_060.png
    {132, -54, 263, 274}, //rot_067.png
    {139, -59, 269, 268}, //rot_075.png
    {146, -66, 274, 262}, //rot_083.png
    {151, -72, 277, 251}, //rot_090.png
    {161, -78, 276, 236}, //rot_097.png
    {170, -84, 278, 224}, //rot_105.png
    {182, -91, 283, 210}, //rot_113.png
    {198, -99, 284, 197}, //rot_120.png
    {215, -90, 283, 212}, //rot_127.png
    {228, -84, 278, 224}, //rot_135.png
    {238, -78, 276, 236}, //rot_143.png
    {245, -72, 277, 250}, //rot_150.png
    {253, -66, 274, 263}, //rot_157.png
    {258, -59, 268, 269}, //rot_165.png
    {264, -54, 262, 274}, //rot_173.png
    {270, -47, 250, 277}, //rot_180.png
    {276, -39, 236, 276}, //rot_187.png
    {283, -29, 224, 278}, //rot_195.png
    {289, -17, 213, 282}, //rot_203.png
    {297, 0, 197, 284}, //rot_210.png
    {290, 16, 212, 284}, //rot_217.png
    {283, 29, 224, 278}, //rot_225.png
    {276, 39, 234, 276}, //rot_233.png
    {271, 46, 251, 277}, //rot_240.png
};

DashboardView::DashboardView()
    : screen_(nullptr)
    , disp_size_(DISP_SMALL)  // 初始化普通成员变量
    , tv_(nullptr)
    , font_large_(nullptr)
    , font_normal_(nullptr)
{
    // 初始化样式
    lv_style_init(&style_text_muted_);
    lv_style_init(&style_title_);
    lv_style_init(&style_icon_);
    lv_style_init(&style_bullet_);
}

DashboardView::~DashboardView()
{
    if (screen_) {
        //lv_obj_del(screen_);
        screen_ = nullptr;
    }
    
    // 重置样式
    lv_style_reset(&style_text_muted_);
    lv_style_reset(&style_title_);
    lv_style_reset(&style_icon_);
    lv_style_reset(&style_bullet_);
}

void DashboardView::createBackground() {
    ESP_LOGI(TAG, "创建背景");

    lv_obj_set_style_bg_color(screen_, lv_color_black(), 0);
    
    // 创建背景图片对象
    lv_obj_t* bg_img = lv_image_create(screen_);
    if (bg_img == nullptr) {
        ESP_LOGE(TAG, "创建背景图片对象失败");
        return;
    }

    // 使用LV_IMG_DECLARE声明的图片数据
    lv_image_set_src(bg_img, &dashboard_bg);
    
    // 设置图片位置（居中对齐）
    lv_obj_align(bg_img, LV_ALIGN_CENTER, 0, 0);
    
    // 确保背景在最底层
    lv_obj_move_background(bg_img);

    ESP_LOGI(TAG, "背景PNG图片加载完成");
}


bool DashboardView::initialize()
{
    screen_ = lv_screen_active(); //lv_obj_create(nullptr);
    if (!screen_) {
        ESP_LOGE(TAG, "创建屏幕失败!");
        return false;
    }

    createBackground();

    return true;
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