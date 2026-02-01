#include "dashboard_view.h"

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
        lv_obj_del(screen_);
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
    
    // 方法1: 直接设置纯色背景（确保能工作）
    lv_obj_set_style_bg_color(screen_, lv_color_make(30, 30, 60), 0);  // 深蓝色背景
    lv_obj_set_style_bg_opa(screen_, LV_OPA_COVER, 0);
    
    // 方法2: 创建一个背景对象
    lv_obj_t* bg_obj = lv_obj_create(screen_);
    lv_obj_remove_style_all(bg_obj);  // 移除默认样式
    lv_obj_set_style_bg_color(bg_obj, lv_color_make(20, 20, 40), 0);
    lv_obj_set_style_bg_opa(bg_obj, LV_OPA_COVER, 0);
    lv_obj_set_size(bg_obj, LV_HOR_RES, LV_VER_RES);
    lv_obj_align(bg_obj, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_move_background(bg_obj);  // 移到最底层
    
    // 暂时不使用图片，先确保其他UI元素能正常显示
    // 图片加载问题可以在其他UI正常工作后再调试
    
    ESP_LOGI(TAG, "背景创建完成(使用纯色)");
    setRedBackground();
}

void DashboardView::setRedBackground() {
    // 方法1：设置屏幕背景色为红色
    lv_obj_set_style_bg_color(screen_, lv_color_make(255, 0, 0), 0);
    lv_obj_set_style_bg_opa(screen_, LV_OPA_COVER, 0);
    
    // 或者创建一个全屏的红色矩形
    lv_obj_t* red_bg = lv_obj_create(screen_);
    lv_obj_set_size(red_bg, LV_HOR_RES, LV_VER_RES);
    lv_obj_set_style_bg_color(red_bg, lv_color_make(255, 0, 0), 0);
    lv_obj_set_style_bg_opa(red_bg, LV_OPA_COVER, 0);
    lv_obj_align(red_bg, LV_ALIGN_CENTER, 0, 0);
    
    // 确保红色背景在最底层
    lv_obj_move_background(red_bg);
    
    ESP_LOGI(TAG, "已设置纯红色背景");
}

bool DashboardView::initialize()
{
    screen_ = lv_obj_create(nullptr);
    if (!screen_) {
        ESP_LOGE(TAG, "创建屏幕失败!");
        return false;
    }

    //createBackground();
    lvglDemoWidgets();

    return true;
}

void DashboardView::lvglDemoWidgets()
{
    if(LV_HOR_RES <= 320) disp_size_ = DISP_SMALL;
    else if(LV_HOR_RES < 720) disp_size_ = DISP_MEDIUM;
    else disp_size_ = DISP_LARGE;

    font_large_ = LV_FONT_DEFAULT;
    font_normal_ = LV_FONT_DEFAULT;

    int32_t tab_h;
    if(disp_size_ == DISP_LARGE) {
        tab_h = 70;
#if LV_DEMO_BENCHMARK_ALIGNED_FONTS
        font_large_     = &lv_font_benchmark_montserrat_24_aligned;
#elif LV_FONT_MONTSERRAT_24
        font_large_     = &lv_font_montserrat_24;
#else
        LV_LOG_WARN("LV_FONT_MONTSERRAT_24 or LV_DEMO_BENCHMARK_ALIGNED_FONTS is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
#if LV_DEMO_BENCHMARK_ALIGNED_FONTS
        font_normal_    = &lv_font_benchmark_montserrat_16_aligned;
#elif LV_FONT_MONTSERRAT_16
        font_normal_    = &lv_font_montserrat_16;
#else
        LV_LOG_WARN("LV_FONT_MONTSERRAT_16 or LV_DEMO_BENCHMARK_ALIGNED_FONTS is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
    }
    else if(disp_size_ == DISP_MEDIUM) {
        tab_h = 45;
#if LV_DEMO_BENCHMARK_ALIGNED_FONTS
        font_large_     = &lv_font_benchmark_montserrat_20_aligned;
#elif LV_FONT_MONTSERRAT_20
        font_large_     = &lv_font_montserrat_20;
#else
        LV_LOG_WARN("LV_FONT_MONTSERRAT_20 or LV_DEMO_BENCHMARK_ALIGNED_FONTS is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
#if LV_DEMO_BENCHMARK_ALIGNED_FONTS
        font_normal_    = &lv_font_benchmark_montserrat_14_aligned;
#elif LV_FONT_MONTSERRAT_14
        font_normal_    = &lv_font_montserrat_14;
#else
        LV_LOG_WARN("LV_FONT_MONTSERRAT_14 or LV_DEMO_BENCHMARK_ALIGNED_FONTS is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
    }
    else {   /* disp_size == DISP_SMALL */
        tab_h = 45;
#if LV_DEMO_BENCHMARK_ALIGNED_FONTS
        font_large_     = &lv_font_benchmark_montserrat_18_aligned;
#elif LV_FONT_MONTSERRAT_18
        font_large_     = &lv_font_montserrat_18;
#else
        LV_LOG_WARN("LV_FONT_MONTSERRAT_18 or LV_DEMO_BENCHMARK_ALIGNED_FONTS is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
#if LV_DEMO_BENCHMARK_ALIGNED_FONTS
        font_normal_    = &lv_font_benchmark_montserrat_12_aligned;
#elif LV_FONT_MONTSERRAT_12
        font_normal_    = &lv_font_montserrat_12;
#else
        LV_LOG_WARN("LV_FONT_MONTSERRAT_12 or LV_DEMO_BENCHMARK_ALIGNED_FONTS is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
    }

#if LV_USE_THEME_DEFAULT
    lv_theme_default_init(NULL, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), LV_THEME_DEFAULT_DARK,
                          font_normal_);
#endif

    lv_style_init(&style_text_muted_);
    lv_style_set_text_opa(&style_text_muted_, LV_OPA_50);

    lv_style_init(&style_title_);
    lv_style_set_text_font(&style_title_, font_large_);

    lv_style_init(&style_icon_);
    lv_style_set_text_color(&style_icon_, lv_theme_get_color_primary(NULL));
    lv_style_set_text_font(&style_icon_, font_large_);

    lv_style_init(&style_bullet_);
    lv_style_set_border_width(&style_bullet_, 0);
    lv_style_set_radius(&style_bullet_, LV_RADIUS_CIRCLE);

    tv_ = lv_tabview_create(lv_screen_active());
    lv_tabview_set_tab_bar_size(tv_, tab_h);
    lv_obj_add_event_cb(tv_, tabview_delete_event_cb, LV_EVENT_DELETE, NULL);

    lv_obj_set_style_text_font(lv_screen_active(), font_normal_, 0);

    lv_obj_t* t1 = lv_tabview_add_tab(tv_, "Profile");
    lv_obj_t* t2 = lv_tabview_add_tab(tv_, "Analytics");
    lv_obj_t* t3 = lv_tabview_add_tab(tv_, "Shop");

    if(disp_size_ == DISP_LARGE) {
        lv_obj_t* tab_bar = lv_tabview_get_tab_bar(tv_);
        lv_obj_set_style_pad_left(tab_bar, LV_HOR_RES / 2, 0);
        lv_obj_t* logo = lv_image_create(tab_bar);
        lv_obj_add_flag(logo, LV_OBJ_FLAG_IGNORE_LAYOUT);
        LV_IMAGE_DECLARE(img_lvgl_logo);
        lv_image_set_src(logo, &img_lvgl_logo);
        lv_obj_align(logo, LV_ALIGN_LEFT_MID, -LV_HOR_RES / 2 + 25, 0);

        lv_obj_t* label = lv_label_create(tab_bar);
        lv_obj_add_style(label, &style_title_, 0);
        lv_obj_add_flag(label, LV_OBJ_FLAG_IGNORE_LAYOUT);
        lv_label_set_text_fmt(label, "LVGL v%d.%d.%d", lv_version_major(), lv_version_minor(), lv_version_patch());
        lv_obj_align_to(label, logo, LV_ALIGN_OUT_RIGHT_TOP, 10, 0);

        label = lv_label_create(tab_bar);
        lv_label_set_text_static(label, "Widgets demo");
        lv_obj_add_flag(label, LV_OBJ_FLAG_IGNORE_LAYOUT);
        lv_obj_add_style(label, &style_text_muted_, 0);
        lv_obj_align_to(label, logo, LV_ALIGN_OUT_RIGHT_BOTTOM, 10, 0);
    }

    //profile_create(t1);
    //analytics_create(t2);
    //shop_create(t3);

    //color_changer_create(tv_);
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