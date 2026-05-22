/**
 * ui.c - Full Skeleton for CrowPanel 7" Marlin HMI
 * LVGL 8.3.11 - Ready for SquareLine export merge
 */

#include "ui.h"
#include "ui_helpers.h"

// ==================== SCREEN OBJECTS ====================
lv_obj_t *ui_ScreenMain;
lv_obj_t *ui_ScreenPrintStatus;
lv_obj_t *ui_ScreenJog;
lv_obj_t *ui_ScreenTMC;
lv_obj_t *ui_ScreenFilament;
lv_obj_t *ui_ScreenFiles;
lv_obj_t *ui_ScreenSettings;
lv_obj_t *ui_ScreenAbout;
lv_obj_t *ui_ScreenTemperature;   // Optional Temperature Dashboard

// ==================== COMMON OBJECTS ====================
lv_obj_t *ui_LabelStatus;
lv_obj_t *ui_BtnBack;
lv_obj_t *ui_PanelNumPad;
lv_obj_t *ui_TxtNumPadInput;

// ==================== UI INIT ====================
void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, 
                                               lv_palette_main(LV_PALETTE_BLUE), 
                                               lv_palette_main(LV_PALETTE_RED), 
                                               true, 
                                               LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);

    // Initialize all screens
    ui_ScreenMain_screen_init();
    ui_ScreenPrintStatus_screen_init();
    ui_ScreenJog_screen_init();
    ui_ScreenTMC_screen_init();
    ui_ScreenFilament_screen_init();
    ui_ScreenFiles_screen_init();
    ui_ScreenSettings_screen_init();
    ui_ScreenAbout_screen_init();
    ui_ScreenTemperature_screen_init();   // Optional

    lv_scr_load(ui_ScreenMain);   // Start on Main Menu
}

// ====================== MAIN MENU ======================
void ui_ScreenMain_screen_init(void)
{
    ui_ScreenMain = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenMain, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_ScreenMain, lv_color_hex(0x1E1E1E), LV_PART_MAIN | LV_STATE_DEFAULT);

    // TODO: Paste SquareLine generated code here for Main Menu
    // (Top bar, navigation buttons, etc.)
}

// ====================== PRINT STATUS ======================
void ui_ScreenPrintStatus_screen_init(void)
{
    ui_ScreenPrintStatus = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenPrintStatus, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_ScreenPrintStatus, lv_color_hex(0x1E1E1E), LV_PART_MAIN | LV_STATE_DEFAULT);

    // TODO: Paste SquareLine generated code here for Print Status
    // (Arc, labels, bars, bottom buttons, etc.)
}

// ====================== JOG SCREEN ======================
void ui_ScreenJog_screen_init(void)
{
    ui_ScreenJog = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenJog, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_ScreenJog, lv_color_hex(0x1E1E1E), LV_PART_MAIN | LV_STATE_DEFAULT);

    // TODO: Paste SquareLine generated code here for Jog Screen
    // (Directional buttons, step dropdown, baby Z slider, etc.)
}

// ====================== TMC SCREEN ======================
void ui_ScreenTMC_screen_init(void)
{
    ui_ScreenTMC = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenTMC, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_ScreenTMC, lv_color_hex(0x1E1E1E), LV_PART_MAIN | LV_STATE_DEFAULT);

    // TODO: Paste SquareLine generated code here for TMC Screen
    // (Tabs + sliders/dropdowns for each axis)
}

// ====================== FILAMENT SCREEN ======================
void ui_ScreenFilament_screen_init(void)
{
    ui_ScreenFilament = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenFilament, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_ScreenFilament, lv_color_hex(0x1E1E1E), LV_PART_MAIN | LV_STATE_DEFAULT);

    // TODO: Paste SquareLine generated code here for Filament Screen
}

// ====================== FILE BROWSER ======================
void ui_ScreenFiles_screen_init(void)
{
    ui_ScreenFiles = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenFiles, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_ScreenFiles, lv_color_hex(0x1E1E1E), LV_PART_MAIN | LV_STATE_DEFAULT);

    // TODO: Paste SquareLine generated code here for File Browser
}

// ====================== SETTINGS SCREEN ======================
void ui_ScreenSettings_screen_init(void)
{
    ui_ScreenSettings = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenSettings, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_ScreenSettings, lv_color_hex(0x1E1E1E), LV_PART_MAIN | LV_STATE_DEFAULT);

    // TODO: Paste SquareLine generated code here for Settings Screen
    // (Including ui_PanelNumPad)
}

// ====================== ABOUT SCREEN ======================
void ui_ScreenAbout_screen_init(void)
{
    ui_ScreenAbout = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenAbout, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_ScreenAbout, lv_color_hex(0x1E1E1E), LV_PART_MAIN | LV_STATE_DEFAULT);

    // TODO: Paste SquareLine generated code here for About Screen
}

// ====================== TEMPERATURE DASHBOARD (Optional) ======================
void ui_ScreenTemperature_screen_init(void)
{
    ui_ScreenTemperature = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenTemperature, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_ScreenTemperature, lv_color_hex(0x1E1E1E), LV_PART_MAIN | LV_STATE_DEFAULT);

    // TODO: Paste SquareLine generated code here for Temperature Screen
}

// ====================== PLACEHOLDER DESTROY FUNCTIONS ======================
void ui_ScreenMain_screen_destroy(void) {}
void ui_ScreenPrintStatus_screen_destroy(void) {}
void ui_ScreenJog_screen_destroy(void) {}
void ui_ScreenTMC_screen_destroy(void) {}
void ui_ScreenFilament_screen_destroy(void) {}
void ui_ScreenFiles_screen_destroy(void) {}
void ui_ScreenSettings_screen_destroy(void) {}
void ui_ScreenAbout_screen_destroy(void) {}
void ui_ScreenTemperature_screen_destroy(void) {}