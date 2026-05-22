/**
 * lgfx_conf.h - CrowPanel 7" ESP32-S3
 * With PCA9557 + GT911 Touch Reset
 * Compatible with LVGL 8.3.11
 */

#pragma once

#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <lgfx/v1/platforms/esp32s3/Panel_RGB.hpp>
#include <lgfx/v1/platforms/esp32s3/Bus_RGB.hpp>
#include <PCA9557.h>

class LGFX : public lgfx::LGFX_Device
{
public:
    lgfx::Bus_RGB     _bus_instance;
    lgfx::Panel_RGB   _panel_instance;
    lgfx::Light_PWM   _light_instance;
    lgfx::Touch_GT911 _touch_instance;

    PCA9557 pca = PCA9557(0x18);   // CrowPanel 7" V3.0 I2C address

    LGFX(void)
    {
        // ==================== PCA9557 + GT911 Reset ====================
        Wire.begin(19, 20);           // SDA=19, SCL=20
        delay(10);

        pca.reset();
        pca.setMode(IO_OUTPUT);

        pca.setState(IO0, IO_LOW);    // RST Low
        delay(20);
        pca.setState(IO0, IO_HIGH);   // RST High
        delay(100);

        pca.setMode(IO1, IO_INPUT);   // INT as input

        Serial.println("✅ PCA9557 + GT911 Reset Complete");

        // ==================== RGB Panel Config ====================
        {
            auto cfg = _panel_instance.config();
            cfg.memory_width   = 800;
            cfg.memory_height  = 480;
            cfg.panel_width    = 800;
            cfg.panel_height   = 480;
            _panel_instance.config(cfg);
        }

        // ==================== RGB Bus Config ====================
        {
            auto cfg = _bus_instance.config();
            cfg.panel = &_panel_instance;

            cfg.pin_d0  = GPIO_NUM_14;  // R0
            cfg.pin_d1  = GPIO_NUM_21;  // R1
            cfg.pin_d2  = GPIO_NUM_47;  // R2
            cfg.pin_d3  = GPIO_NUM_48;  // R3
            cfg.pin_d4  = GPIO_NUM_45;  // R4
            cfg.pin_d5  = GPIO_NUM_9;   // G0
            cfg.pin_d6  = GPIO_NUM_46;  // G1
            cfg.pin_d7  = GPIO_NUM_3;   // G2
            cfg.pin_d8  = GPIO_NUM_8;   // G3
            cfg.pin_d9  = GPIO_NUM_16;  // G4
            cfg.pin_d10 = GPIO_NUM_1;   // B0
            cfg.pin_d11 = GPIO_NUM_15;  // B1
            cfg.pin_d12 = GPIO_NUM_7;   // B2
            cfg.pin_d13 = GPIO_NUM_6;   // B3
            cfg.pin_d14 = GPIO_NUM_5;   // B4
            cfg.pin_d15 = GPIO_NUM_4;   // B5

            cfg.pin_hsync = GPIO_NUM_40;
            cfg.pin_vsync = GPIO_NUM_39;
            cfg.pin_de    = GPIO_NUM_41;
            cfg.pin_pclk  = GPIO_NUM_0;

            cfg.hsync_polarity    = 0;
            cfg.hsync_front_porch = 40;
            cfg.hsync_pulse_width = 48;
            cfg.hsync_back_porch  = 40;

            cfg.vsync_polarity    = 0;
            cfg.vsync_front_porch = 1;
            cfg.vsync_pulse_width = 31;
            cfg.vsync_back_porch  = 13;

            cfg.pclk_active_neg   = 1;
            cfg.prefer_speed      = 16000000;

            _bus_instance.config(cfg);
        }
        _panel_instance.setBus(&_bus_instance);

        // ==================== Backlight ====================
        {
            auto cfg = _light_instance.config();
            cfg.pin_bl = GPIO_NUM_2;
            cfg.invert = false;
            cfg.freq   = 20000;
            _light_instance.config(cfg);
            _panel_instance.light(&_light_instance);
        }

        // ==================== GT911 Touch ====================
        {
            auto cfg = _touch_instance.config();
            cfg.x_min = 0;
            cfg.x_max = 799;
            cfg.y_min = 0;
            cfg.y_max = 479;
            cfg.pin_int = -1;
            cfg.pin_rst = -1;
            cfg.bus_shared = false;
            cfg.i2c_port = 0;
            cfg.pin_sda  = GPIO_NUM_19;
            cfg.pin_scl  = GPIO_NUM_20;
            cfg.freq     = 400000;
            cfg.i2c_addr = 0x5D;        // Try 0x14 if touch doesn't work

            _touch_instance.config(cfg);
            _panel_instance.setTouch(&_touch_instance);
        }

        setPanel(&_panel_instance);
    }
};

// Global display object
LGFX lcd;