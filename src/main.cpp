#include <Arduino.h>
#include "Devices.h"

static Devices devices;
static Display display;

void setup() {
    cli();
    _PROTECTED_WRITE(CLKCTRL.OSCHFCTRLA, CLKCTRL_FREQSEL_24M_gc);
    sei();

    devices.display = &display;

    display.init();

    Serial.begin(115200);
    Serial.println("Hello!");
}

void loop() {
// write your code here
}