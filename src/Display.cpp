#include "Display.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT  64
#define SCREEN_ADDR  0x3C

static Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void Display::setup(const Devices* _devices) {
    devices = _devices;
    Serial.println(F("Display: initializing SSD1306..."));
    if (!oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDR)) {
        Serial.println(F("Display: [FAIL] SSD1306 not found"));
        return;
    }

    oled.clearDisplay();
    oled.setTextColor(SSD1306_WHITE);
    oled.setTextSize(1);
    oled.setCursor(0, 0);
    oled.print(F("DiveCompass"));
    oled.display();
    Serial.println(F("Display: [OK] SSD1306 ready"));
}

static const char* magLabel(uint8_t acc) {
    switch (acc) {
        case 1:  return "Low";
        case 2:  return "Med";
        case 3:  return "High";
        default: return "Unrel";
    }
}

void Display::update() {
    char buf[22];
    char v0[9], v1[9];

    const CompassBNO08X* c0 = devices->compass0;
    const CompassBNO08X* c1 = devices->compass1;

    oled.clearDisplay();

    oled.setTextColor(SSD1306_WHITE);

    oled.setTextSize(1);
    double h1 = c0->getHeading();
    double h2 = c1->getHeading();
    snprintf(buf, sizeof(buf), "H: %03.2f %03.2f", h1, h2);
    oled.setCursor(0, 0);
    oled.print(buf);

    double diff = fabs(h1 - h2);
    double diffPercent = diff/360.0*100.0;
    snprintf(buf, sizeof(buf), "Diff: %03.2f%%", diffPercent);
    oled.setCursor(0, 22);
    oled.print(buf);

    snprintf(buf, sizeof(buf), "P: %03.2f %03.2f", c0->getPitch(), c1->getPitch());
    oled.setCursor(0, 33);
    oled.print(buf);

    snprintf(buf, sizeof(buf), "R: %03.2f %03.2f", c0->getRoll(), c1->getRoll());
    oled.setCursor(0, 44);
    oled.print(buf);

    oled.setCursor(0, 55);
    snprintf(buf, sizeof(buf), "Mag:%s-%s", magLabel(c0->getMagAccuracy()), magLabel(c1->getMagAccuracy()));
    oled.print(buf);

    oled.display();
}

void Display::showCalibrating(uint8_t acc0, uint8_t acc1) {
    char buf[22];
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(0,  0); oled.print(F("** CALIBRATING **"));
    oled.setCursor(0, 16); oled.print(F("Move in figure-8"));
    oled.setCursor(0, 32); snprintf(buf, sizeof(buf), "Fwd : %s", magLabel(acc0)); oled.print(buf);
    oled.setCursor(0, 42); snprintf(buf, sizeof(buf), "Rear: %s", magLabel(acc1)); oled.print(buf);
    oled.display();
}

void Display::showCalibrationSaved() {
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(0, 20); oled.print(F("  Calibration"));
    oled.setCursor(0, 32); oled.print(F("    Saved!"));
    oled.display();
}
