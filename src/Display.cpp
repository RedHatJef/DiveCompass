//
// Created by redha on 2/16/2025.
//

#include "Display.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GC9A01A.h>
#include <avr/io.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>

#define TFT_CS 7 // Chip select
#define TFT_DC 8 // Data/command

#define MAX_CALIBRATION_TIME_MS 10000

// Display constructor for primary hardware SPI connection -- the specific
// pins used for writing to the display are unique to each board and are not
// negotiable. "Soft" SPI (using any pins) is an option but performance is
// reduced; it's rarely used, see header file for syntax if needed.
Adafruit_GC9A01A tft(TFT_CS, TFT_DC);

void Display::init() {
    tft.begin();
    clear();
}

void Display::clear() {
    tft.fillScreen(GC9A01A_BLACK);
    tft.setTextColor(GC9A01A_WHITE);
    tft.endWrite();
}

void Display::update() {

}

void Display::updateFromISR() {
    if(calibrationStartTime > 0) {
        unsigned long elapsedTime = millis() - calibrationStartTime;
        if(elapsedTime > MAX_CALIBRATION_TIME_MS) elapsedTime = MAX_CALIBRATION_TIME_MS;
        double percentComplete = ((double)elapsedTime) / MAX_CALIBRATION_TIME_MS;
        double radians = percentComplete * 2 * PI;
        double xEndD = 120 * cos(radians);
        double yEndD = 120 * sin(radians);
        double xStartD = xEndD / 120 * 110;
        double yStartD = yEndD / 120 * 110;

        int16_t xStart = round(xStartD) + 120;
        int16_t yStart = round(yStartD) + 120;
        int16_t xEnd = round(xEndD) + 120;
        int16_t yEnd = round(yEndD) + 120;

        if(xEnd != lastXEnd || yEnd != lastYEnd || xStart != lastXStart || yStart != lastYStart) {
            tft.drawLine(xStart, yStart, xEnd, yEnd, GC9A01A_CYAN);
            lastXStart = xStart;
            lastYStart = yStart;
            lastXEnd = xEnd;
            lastYEnd = yEnd;
        }
    }
}

void Display::beginCalibration() {
    clear();
    tft.setCursor(50,120);
    tft.setTextColor(GC9A01A_ORANGE);
    tft.setFont(&FreeMonoBold12pt7b);
    tft.write("CALIBRATING");
    tft.endWrite();

    calibrationStartTime = millis();
    if(calibrationStartTime == 0) {
        calibrationStartTime = 1;
    }
    lastXStart = lastYStart = lastXEnd = lastYEnd = 255;
}

void Display::endCalibration() {
    calibrationStartTime = 0;
}

