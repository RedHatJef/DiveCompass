//
// Created by redha on 2/16/2025.
//

#include "Display.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GC9A01A.h>
#include <avr/io.h>
#include <Fonts/FreeMonoBold24pt7b.h>
//#include <Fonts/FreeMonoBold12pt7b.h>

#define TFT_CS 7 // Chip select
#define TFT_DC 8 // Data/command

// Display constructor for primary hardware SPI connection -- the specific
// pins used for writing to the display are unique to each board and are not
// negotiable. "Soft" SPI (using any pins) is an option but performance is
// reduced; it's rarely used, see header file for syntax if needed.
Adafruit_GC9A01A tft(TFT_CS, TFT_DC);

void Display::init() {
    tft.begin();
    tft.fillScreen(GC9A01A_BLACK);
    tft.setFont(&FreeMonoBold24pt7b);
    tft.setTextSize(0);
    tft.setTextColor(GC9A01A_WHITE);
    tft.setCursor(50,120);
    tft.write("Hello");
    tft.endWrite();
}

void Display::update() {

}
