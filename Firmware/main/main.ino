// =====================================================
// main.ino - FULL FINAL INTEGRATED VERSION
// CrowPanel 7" Marlin HMI - LVGL 8.3.11
// =====================================================

#include <Arduino.h>

// IMPORTANT: lgfx_conf.h must be first (includes LovyanGFX + PCA9557)
#include "lgfx_conf.h"

#include <lvgl.h>

// SquareLine UI files
#include "ui.h"
#include "ui_events.c"

HardwareSerial MarlinSerial(1);

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[800 * 480 / 10];

// ====================== DISPLAY FLUSH ======================
void my_disp_flush(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_p) {
    lcd.pushImageDMA(area->x1, area->y1,
                     area->x2 - area->x1 + 1,
                     area->y2 - area->y1 + 1,
                     (uint16_t*)color_p);
    lv_disp_flush_ready(drv);
}

// ====================== MINIMAL SERIAL PARSER ======================
void parse_marlin_response(const String& line) {
    String trimmed = line;
    trimmed.trim();
    if (trimmed.length() == 0) return;

    // Temperature - Update Top Bar Small Labels
if (trimmed.startsWith("T:")) {
    float hcur = 0, hset = 0, bcur = 0, bset = 0;
    sscanf(trimmed.c_str(), "T:%f/%f B:%f/%f", &hcur, &hset, &bcur, &bset);

    // Update Print Status Screen (if open)
    if (lv_scr_act() == ui_ScreenPrintStatus) {
        lv_label_set_text_fmt(ui_LabelHotend, "%.0f/%.0f°C", hcur, hset);
        lv_label_set_text_fmt(ui_LabelBed, "%.0f/%.0f°C", bcur, bset);
    }

    // Update Top Bar on Main Menu (always visible)
    lv_label_set_text_fmt(ui_LabelHotendSmall, "%.0f°C", hcur);
    lv_label_set_text_fmt(ui_LabelBedSmall, "%.0f°C", bcur);
}

    // Print Progress
    if (trimmed.indexOf("SD printing byte") != -1) {
        int percent = 0;
        sscanf(trimmed.c_str(), "SD printing byte %*d/%*d", &percent);
        if (percent > 0 && percent <= 100 && lv_scr_act() == ui_ScreenPrintStatus) {
            lv_bar_set_value(ui_BarProgress, percent, LV_ANIM_ON);
            lv_label_set_text_fmt(ui_LabelBigPercent, "%d%%", percent);
        }
    }

    // Steps (M92) for Settings Screen
    if (trimmed.startsWith("M92 X")) {
        float x, y, z, e;
        sscanf(trimmed.c_str(), "M92 X%f Y%f Z%f E%f", &x, &y, &z, &e);
        if (lv_scr_act() == ui_ScreenSettings) {
            lv_textarea_set_text(ui_TxtXSteps, String(x, 2).c_str());
            lv_textarea_set_text(ui_TxtYSteps, String(y, 2).c_str());
            lv_textarea_set_text(ui_TxtZSteps, String(z, 2).c_str());
            lv_textarea_set_text(ui_TxtESteps, String(e, 2).c_str());
        }
    }

    // Debug: Show all Marlin responses in Serial Monitor
    Serial.println(">> " + trimmed);
}

// ====================== SETUP ======================
void setup() {
    Serial.begin(115200);
    MarlinSerial.begin(250000);

    Serial.println("\n=== CrowPanel 7\" Marlin HMI Starting ===\n");

    // PCA9557 + GT911 Touch Reset
    Wire.begin(19, 20);
    delay(50);
    reset_GT911();

    lcd.begin();
    lcd.setBrightness(220);

    lv_init();
    lv_disp_draw_buf_init(&draw_buf, buf1, NULL, 800*480/10);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = 800;
    disp_drv.ver_res = 480;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    ui_init();

    Serial.println("✅ HMI Ready! Touch & Marlin Communication Active.\n");
}

// ====================== LOOP ======================
void loop() {
    lv_timer_handler();        // Must be called frequently

    // Periodic polling
    static uint32_t last_poll = 0;
    if (millis() - last_poll > 1400) {
        MarlinSerial.println("M105");   // Temperatures
        MarlinSerial.println("M27");    // Progress
        last_poll = millis();
    }

    // Read responses from Marlin
    while (MarlinSerial.available()) {
        String line = MarlinSerial.readStringUntil('\n');
        parse_marlin_response(line);
    }

    delay(5);
}