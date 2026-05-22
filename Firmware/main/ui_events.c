// =====================================================
// ui_events.c - COMPLETE VERSION WITH PID TUNING
// SquareLine 1.60 + LVGL 8.3.11 - CrowPanel 7" Marlin HMI
// Includes improved PID tuning feedback with Kp/Ki/Kd values
// =====================================================

#include "ui.h"
#include <HardwareSerial.h>
#include <lvgl.h>
#include <stdarg.h>

extern HardwareSerial MarlinSerial;
extern LGFX lcd;

String selected_file = "";
String numpad_buffer = "";

// ====================== HELPERS ======================
void send_gcode(const char* cmd) {
    MarlinSerial.println(cmd);
}

void send_gcode_fmt(const char* format, ...) {
    char buf[128];
    va_list args;
    va_start(args, format);
    vsnprintf(buf, sizeof(buf), format, args);
    va_end(args);
    MarlinSerial.println(buf);
}

// ====================== NAVIGATION ======================
void ui_eventBtnBack(lv_event_t * e) {
    lv_scr_load(ui_ScreenMain);
}

// ====================== SHUTDOWN ======================
void ui_eventBtnShutDown(lv_event_t * e) {
    send_gcode("M81");
}

// ====================== PRINT STATUS ======================
void ui_eventBtnPauseResume(lv_event_t * e) {
    static bool paused = false;
    if (!paused) {
        send_gcode("M25");
        lv_label_set_text(ui_BtnPauseResume, "RESUME");
    } else {
        send_gcode("M24");
        lv_label_set_text(ui_BtnPauseResume, "PAUSE");
    }
    paused = !paused;
}

void ui_eventBtnStop(lv_event_t * e) {
    lv_obj_clear_flag(ui_PanelStopConfirm, LV_OBJ_FLAG_HIDDEN);
}

void ui_eventBtnStopConfirmYes(lv_event_t * e) {
    send_gcode("M0");
    lv_obj_add_flag(ui_PanelStopConfirm, LV_OBJ_FLAG_HIDDEN);
    lv_scr_load(ui_ScreenMain);
}

void ui_eventBtnStopConfirmNo(lv_event_t * e) {
    lv_obj_add_flag(ui_PanelStopConfirm, LV_OBJ_FLAG_HIDDEN);
}

void ui_eventSliderSpeed(lv_event_t * e) {
    int speed = lv_slider_get_value(ui_SliderSpeed);
    send_gcode_fmt("M220 S%d", speed);
}

// ====================== JOG SCREEN ======================
void ui_eventBtnYPlus(lv_event_t * e)  { send_gcode("G91\nG0 Y10 F3000\nG90"); }
void ui_eventBtnYMinus(lv_event_t * e) { send_gcode("G91\nG0 Y-10 F3000\nG90"); }
void ui_eventBtnXPlus(lv_event_t * e)  { send_gcode("G91\nG0 X10 F3000\nG90"); }
void ui_eventBtnXMinus(lv_event_t * e) { send_gcode("G91\nG0 X-10 F3000\nG90"); }
void ui_eventBtnZPlus(lv_event_t * e)  { send_gcode("G91\nG0 Z5 F1000\nG90"); }
void ui_eventBtnZMinus(lv_event_t * e) { send_gcode("G91\nG0 Z-5 F1000\nG90"); }

void ui_eventBtnHomeAll(lv_event_t * e) { send_gcode("G28"); }
void ui_eventBtnHomeX(lv_event_t * e)   { send_gcode("G28 X"); }
void ui_eventBtnHomeY(lv_event_t * e)   { send_gcode("G28 Y"); }
void ui_eventBtnHomeZ(lv_event_t * e)   { send_gcode("G28 Z"); }

void ui_eventBtnAutoZAlign(lv_event_t * e)  { send_gcode("G28\nG34"); }
void ui_eventBtnAutoBedLevel(lv_event_t * e){ send_gcode("G28\nG29"); }

void ui_eventBtnLoadMesh(lv_event_t * e)    { send_gcode("M420 S1"); }
void ui_eventBtnSaveMesh(lv_event_t * e)    { send_gcode("M500"); }

void ui_eventSliderBabyZ(lv_event_t * e) {
    int val = lv_slider_get_value(ui_SliderBabyZ);
    send_gcode_fmt("M290 Z%.3f", val / 100.0);
}

// ====================== TMC SCREEN ======================
// X Tab
void ui_eventSliderXCurrent(lv_event_t * e) {}
void ui_eventDropdownXMicrosteps(lv_event_t * e) {}
void ui_eventSliderXHybrid(lv_event_t * e) {}
void ui_eventSliderXSGT(lv_event_t * e) {}
void ui_eventDropdownXMode(lv_event_t * e) {}

// Y Tab
void ui_eventSliderYCurrent(lv_event_t * e) {}
void ui_eventDropdownYMicrosteps(lv_event_t * e) {}
void ui_eventSliderYHybrid(lv_event_t * e) {}
void ui_eventSliderYSGT(lv_event_t * e) {}
void ui_eventDropdownYMode(lv_event_t * e) {}

// Z1 Tab
void ui_eventSliderZ1Current(lv_event_t * e) {}
void ui_eventDropdownZ1Microsteps(lv_event_t * e) {}
void ui_eventSliderZ1Hybrid(lv_event_t * e) {}
void ui_eventSliderZ1SGT(lv_event_t * e) {}
void ui_eventDropdownZ1Mode(lv_event_t * e) {}

// Z2 Tab
void ui_eventSliderZ2Current(lv_event_t * e) {}
void ui_event(lv_event_t * e) {}                    // SquareLine empty name
void ui_eventSliderZ2Hybrid(lv_event_t * e) {}
void ui_eventSliderZ2SGT(lv_event_t * e) {}
void ui_eventDropdownZ2Mode(lv_event_t * e) {}

// Z3 Tab
void ui_eventSliderZ3Current(lv_event_t * e) {}
void ui_eventDropdownZ3Microsteps(lv_event_t * e) {}
void ui_eventSliderZ3Hybrid(lv_event_t * e) {}
void ui_eventSliderZ3SGT(lv_event_t * e) {}
void ui_eventDropdownZ3Mode(lv_event_t * e) {}

// E0 Tab
void ui_eventSliderE0Current(lv_event_t * e) {}
void ui_eventDropdownE0Microsteps(lv_event_t * e) {}
void ui_eventSliderE0Hybrid(lv_event_t * e) {}
void ui_eventSliderE0SGT(lv_event_t * e) {}
void ui_eventDropdownE0Mode(lv_event_t * e) {}

// TMC Apply Buttons
void ui_eventBtnApplyAllTMC(lv_event_t * e) {      // X Tab
    int curr = lv_slider_get_value(ui_SliderXCurrent);
    send_gcode_fmt("M906 X%d", curr);
    send_gcode("M500");
    lv_label_set_text(ui_LabelTMCStatus, "X Settings Applied");
}

void ui_eventBtnApplyAllTMC_Y(lv_event_t * e) {
    int curr = lv_slider_get_value(ui_SliderYCurrent);
    send_gcode_fmt("M906 Y%d", curr);
    send_gcode("M500");
    lv_label_set_text(ui_LabelTMCStatus, "Y Settings Applied");
}

void ui_eventBtnApplyAllTMC_Z1(lv_event_t * e) {
    int curr = lv_slider_get_value(ui_SliderZ1Current);
    send_gcode_fmt("M906 Z%d", curr);
    send_gcode("M500");
    lv_label_set_text(ui_LabelTMCStatus, "Z1 Settings Applied");
}

void ui_eventBtnApplyAllTMC_Z2(lv_event_t * e) {
    int curr = lv_slider_get_value(ui_SliderZ2Current);
    send_gcode_fmt("M906 Z%d", curr);
    send_gcode("M500");
    lv_label_set_text(ui_LabelTMCStatus, "Z2 Settings Applied");
}

void ui_eventBtnApplyAllTMC_Z3(lv_event_t * e) {
    int curr = lv_slider_get_value(ui_SliderZ3Current);
    send_gcode_fmt("M906 Z%d", curr);
    send_gcode("M500");
    lv_label_set_text(ui_LabelTMCStatus, "Z3 Settings Applied");
}

void ui_eventBtnApplyAllTMC_E0(lv_event_t * e) {
    int curr = lv_slider_get_value(ui_SliderE0Current);
    send_gcode_fmt("M906 E%d", curr);
    send_gcode("M500");
    lv_label_set_text(ui_LabelTMCStatus, "E0 Settings Applied");
}

void ui_eventBtnSaveTMC(lv_event_t * e) {
    send_gcode("M500");
}

void ui_eventBtnRefreshTMC(lv_event_t * e) {
    send_gcode("M906\nM913\nM914\nM122");
}

// ====================== PID TUNING (Temperature Screen) ======================
void ui_eventBtnPIDHotend(lv_event_t * e) {
    send_gcode("M303 E0 S200 C8");
    lv_label_set_text(ui_LabelPIDStatus, "?? Hotend PID Tuning Started... (200°C)");
    lv_obj_set_style_text_color(ui_LabelPIDStatus, lv_color_hex(0xFFAA00), LV_PART_MAIN);
}

void ui_eventBtnPIDBed(lv_event_t * e) {
    send_gcode("M303 E-1 S60 C8");
    lv_label_set_text(ui_LabelPIDStatus, "?? Bed PID Tuning Started... (60°C)");
    lv_obj_set_style_text_color(ui_LabelPIDStatus, lv_color_hex(0x4488FF), LV_PART_MAIN);
}

void ui_eventBtnSavePID(lv_event_t * e) {
    send_gcode("M500");
    lv_label_set_text(ui_LabelPIDStatus, "? PID Values Saved to EEPROM");
    lv_obj_set_style_text_color(ui_LabelPIDStatus, lv_color_hex(0x00FF88), LV_PART_MAIN);
}

// ====================== FILAMENT ======================
void ui_eventSwitchRunout(lv_event_t * e) {
    bool en = lv_obj_has_state(ui_SwitchRunout, LV_STATE_CHECKED);
    send_gcode_fmt("M412 S%d", en ? 1 : 0);
}

void ui_eventSwitchJam(lv_event_t * e) {
    bool en = lv_obj_has_state(ui_SwitchJam, LV_STATE_CHECKED);
    send_gcode_fmt("M412 S%d", en ? 1 : 0);
}

// ====================== FILE BROWSER ======================
void ui_eventListFiles(lv_event_t * e) {
    lv_obj_t *btn = lv_event_get_target(e);
    selected_file = lv_label_get_text(lv_obj_get_child(btn, 0));
    lv_label_set_text_fmt(ui_LabelSelectedFile, "Selected:\n%s", selected_file.c_str());
}

void ui_eventBtnPrintSelected(lv_event_t * e) {
    if (selected_file.length() == 0) return;
    send_gcode_fmt("M23 %s", selected_file.c_str());
    send_gcode("M24");
    lv_scr_load(ui_ScreenPrintStatus);
}

void ui_eventBtnRefreshFiles(lv_event_t * e) {
    lv_obj_clean(ui_ListFiles);
    send_gcode("M20");
}

// ====================== NUMBER PAD ======================
void show_numpad(lv_obj_t * target_textarea) {
    lv_obj_set_user_data(ui_TxtNumPadInput, target_textarea);
    numpad_buffer = lv_textarea_get_text(target_textarea);
    lv_textarea_set_text(ui_TxtNumPadInput, numpad_buffer.c_str());
    lv_obj_clear_flag(ui_PanelNumPad, LV_OBJ_FLAG_HIDDEN);
}

void ui_eventNumPadDigit(lv_event_t * e) {
    lv_obj_t *btn = lv_event_get_target(e);
    const char *txt = lv_label_get_text(lv_obj_get_child(btn, 0));
    numpad_buffer += txt;
    lv_textarea_set_text(ui_TxtNumPadInput, numpad_buffer.c_str());
}

void ui_eventNumPadBackspace(lv_event_t * e) {
    if (numpad_buffer.length() > 0) {
        numpad_buffer.remove(numpad_buffer.length() - 1);
        lv_textarea_set_text(ui_TxtNumPadInput, numpad_buffer.c_str());
    }
}

void ui_eventNumPadEnter(lv_event_t * e) {
    lv_obj_t *target = (lv_obj_t*)lv_obj_get_user_data(ui_TxtNumPadInput);
    if (target) {
        lv_textarea_set_text(target, numpad_buffer.c_str());
    }
    lv_obj_add_flag(ui_PanelNumPad, LV_OBJ_FLAG_HIDDEN);
    numpad_buffer = "";
}

void ui_eventNumPadCancel(lv_event_t * e) {
    lv_obj_add_flag(ui_PanelNumPad, LV_OBJ_FLAG_HIDDEN);
    numpad_buffer = "";
}

// ====================== SETTINGS ======================
void ui_eventTxtXStepsClicked(lv_event_t * e)   { show_numpad(ui_TxtXSteps); }
void ui_eventTxtYStepsClicked(lv_event_t * e)   { show_numpad(ui_TxtYSteps); }
void ui_eventTxtZStepsClicked(lv_event_t * e)   { show_numpad(ui_TxtZSteps); }
void ui_eventTxtEStepsClicked(lv_event_t * e)   { show_numpad(ui_TxtESteps); }
void ui_eventTxtFilDiaClicked(lv_event_t * e)   { show_numpad(ui_TxtFilDia); }

void ui_eventSliderFlow(lv_event_t * e) {
    int flow = lv_slider_get_value(ui_SliderFlow);
    send_gcode_fmt("M221 S%d", flow);
}

void ui_eventSliderBrightness(lv_event_t * e) {
    int val = lv_slider_get_value(ui_SliderBrightness);
    lcd.setBrightness(val);
}


// ====================== FILAMENT, FILES, NUMBER PAD, SETTINGS, ABOUT ======================
void ui_eventBtnCheckUpdate(lv_event_t * e) {
    lv_label_set_text(ui_LabelStatus, "Checking for updates...");
}

void ui_eventBtnShowLogs(lv_event_t * e) {
    send_gcode("M122\nM115");
}

void ui_eventBtnFactoryReset(lv_event_t * e) {
    send_gcode("M502");
    send_gcode("M500");
}

// ====================== IMPROVED SERIAL PARSER ======================
void parse_marlin_response(const String& line) {
    String trimmed = line;
    trimmed.trim();
    if (trimmed.length() == 0) return;

    // Temperature Update
    if (trimmed.startsWith("T:")) {
        float hcur = 0, hset = 0, bcur = 0, bset = 0;
        sscanf(trimmed.c_str(), "T:%f/%f B:%f/%f", &hcur, &hset, &bcur, &bset);

        if (lv_scr_act() == ui_ScreenPrintStatus) {
            lv_label_set_text_fmt(ui_LabelHotend, "%.0f/%.0f°C", hcur, hset);
            lv_label_set_text_fmt(ui_LabelBed, "%.0f/%.0f°C", bcur, bset);
        }
    }

    // PID Tuning Feedback
    if (trimmed.indexOf("PID Autotune finished") != -1) {
        lv_label_set_text(ui_LabelPIDStatus, "? PID Autotune Finished!");
        lv_obj_set_style_text_color(ui_LabelPIDStatus, lv_color_hex(0x00FF88), LV_PART_MAIN);
    }

    // Extract Kp, Ki, Kd values
    if (trimmed.indexOf("Kp:") != -1 && trimmed.indexOf("Ki:") != -1) {
        float Kp = 0, Ki = 0, Kd = 0;
        sscanf(trimmed.c_str(), "Kp: %f Ki: %f Kd: %f", &Kp, &Ki, &Kd);

        char buf[128];
        snprintf(buf, sizeof(buf), "? PID Values:\nKp: %.2f   Ki: %.2f   Kd: %.2f", Kp, Ki, Kd);
        
        lv_label_set_text(ui_LabelPIDStatus, buf);
        lv_obj_set_style_text_color(ui_LabelPIDStatus, lv_color_hex(0x00FF88), LV_PART_MAIN);
    }

    // Error handling
    if (trimmed.indexOf("Error") != -1 || trimmed.indexOf("timeout") != -1) {
        lv_label_set_text(ui_LabelPIDStatus, "? PID Tuning Failed or Timed Out");
        lv_obj_set_style_text_color(ui_LabelPIDStatus, lv_color_hex(0xFF4444), LV_PART_MAIN);
    }

    // Debug output
    Serial.println(">> " + trimmed);
}