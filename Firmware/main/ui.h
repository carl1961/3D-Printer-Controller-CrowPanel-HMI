/**
 * ui.h - Updated with Shutdown Button
 * LVGL 8.3.11 - CrowPanel 7" Marlin HMI
 */

#pragma once

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// ==================== SCREENS ====================
extern lv_obj_t *ui_ScreenMain;
extern lv_obj_t *ui_ScreenPrintStatus;
extern lv_obj_t *ui_ScreenJog;
extern lv_obj_t *ui_ScreenTMC;
extern lv_obj_t *ui_ScreenFilament;
extern lv_obj_t *ui_ScreenFiles;
extern lv_obj_t *ui_ScreenSettings;
extern lv_obj_t *ui_ScreenAbout;

// ==================== COMMON ====================
extern lv_obj_t *ui_LabelStatus;
extern lv_obj_t *ui_BtnBack;

// ==================== NEW: SHUTDOWN BUTTON ====================
extern lv_obj_t *ui_BtnShutDown;     // ← Added

// ==================== PRINT STATUS ====================
extern lv_obj_t *ui_ArcOverall;
extern lv_obj_t *ui_LabelBigPercent;
extern lv_obj_t *ui_LabelHotend;
extern lv_obj_t *ui_LabelBed;
extern lv_obj_t *ui_BarProgress;
extern lv_obj_t *ui_LabelLayer;
extern lv_obj_t *ui_LabelElapsed;
extern lv_obj_t *ui_LabelRemaining;
extern lv_obj_t *ui_BtnPauseResume;
extern lv_obj_t *ui_BtnStop;
extern lv_obj_t *ui_LabelFilamentStatus;
extern lv_obj_t *ui_PanelStopConfirm;
extern lv_obj_t *ui_SliderSpeed;

// ==================== JOG ====================
extern lv_obj_t *ui_BtnYPlus, *ui_BtnYMinus;
extern lv_obj_t *ui_BtnXPlus, *ui_BtnXMinus;
extern lv_obj_t *ui_BtnZPlus, *ui_BtnZMinus;
extern lv_obj_t *ui_BtnHomeAll;
extern lv_obj_t *ui_BtnAutoZAlign;
extern lv_obj_t *ui_BtnAutoBedLevel;
extern lv_obj_t *ui_SliderBabyZ;
extern lv_obj_t *ui_LabelPosX, *ui_LabelPosY, *ui_LabelPosZ;

// ==================== TMC ====================
extern lv_obj_t *ui_SliderXCurrent;
extern lv_obj_t *ui_LabelTMCStatus;

// ==================== FILAMENT ====================
extern lv_obj_t *ui_SwitchRunout;
extern lv_obj_t *ui_SwitchJam;

// ==================== FILES ====================
extern lv_obj_t *ui_ListFiles;
extern lv_obj_t *ui_LabelSelectedFile;
extern lv_obj_t *ui_BtnPrintSelected;

// ==================== SETTINGS ====================
extern lv_obj_t *ui_TxtXSteps, *ui_TxtYSteps, *ui_TxtZSteps, *ui_TxtESteps;
extern lv_obj_t *ui_TxtFilDia;
extern lv_obj_t *ui_SliderFlow;
extern lv_obj_t *ui_SliderBrightness;
extern lv_obj_t *ui_LabelPIDStatus;
extern lv_obj_t *ui_PanelNumPad;
extern lv_obj_t *ui_TxtNumPadInput;

// ==================== ABOUT ====================
extern lv_obj_t *ui_LabelFirmware;
extern lv_obj_t *ui_LabelVersion;

// ==================== INITIALIZATION ====================
void ui_init(void);

void ui_ScreenMain_screen_init(void);
void ui_ScreenPrintStatus_screen_init(void);
void ui_ScreenJog_screen_init(void);
void ui_ScreenTMC_screen_init(void);
void ui_ScreenFilament_screen_init(void);
void ui_ScreenFiles_screen_init(void);
void ui_ScreenSettings_screen_init(void);
void ui_ScreenAbout_screen_init(void);

#ifdef __cplusplus
} /* extern "C" */
#endif