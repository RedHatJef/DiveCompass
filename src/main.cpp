#include <Arduino.h>

void setup() {
    cli();
    _PROTECTED_WRITE(CLKCTRL.OSCHFCTRLA, CLKCTRL_FREQSEL_24M_gc);
    sei();

    Serial.begin(115200);
    Serial.println("Hello!");
}

void loop() {
// write your code here
}