#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "Devices.h"

static Devices devices;
static Display display;

void setup() {
    cli();
    _PROTECTED_WRITE(CLKCTRL.OSCHFCTRLA, CLKCTRL_FREQSEL_24M_gc);
    sei();

    Wire.begin();
    Wire.setClock(10000000);
    SPI.setClockDivider(0);

    devices.display = &display;

    display.init();

    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1024_gc | TCA_SINGLE_ENABLE_bm;
    TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_NORMAL_gc;
    TCA0.SINGLE.PER = 39061;
    TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;

    Serial.begin(115200);
    Serial.println("Hello!");

    display.beginCalibration();
    delay(11000);
    display.endCalibration();
    delay(100);
    display.clear();
}

void loop() {
// write your code here
}

ISR(TCA0_OVF_vect) {
    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
    display.updateFromISR();
}