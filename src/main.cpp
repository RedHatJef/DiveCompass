#include <Arduino.h>
#include <Wire.h>
#include "Devices.h"
#include "Display.h"

static Devices        devices;
static CompassBNO08X  compass0;
static CompassBNO08X  compass1;
static Display        display;

static void i2cReset() {
    pinMode(PIN_WIRE_SDA, INPUT_PULLUP);
    pinMode(PIN_WIRE_SCL, OUTPUT);

    for (uint8_t i = 0; i < 9; i++) {
        digitalWrite(PIN_WIRE_SCL, LOW);
        delayMicroseconds(5);
        digitalWrite(PIN_WIRE_SCL, HIGH);
        delayMicroseconds(5);
        if (digitalRead(PIN_WIRE_SDA)) break;
    }

    pinMode(PIN_WIRE_SDA, OUTPUT);
    digitalWrite(PIN_WIRE_SDA, LOW);
    delayMicroseconds(5);
    digitalWrite(PIN_WIRE_SCL, HIGH);
    delayMicroseconds(5);
    digitalWrite(PIN_WIRE_SDA, HIGH);
    delayMicroseconds(5);

    pinMode(PIN_WIRE_SDA, INPUT);
    pinMode(PIN_WIRE_SCL, INPUT);

    pinMode(16, INPUT_PULLUP);
}


void setup() {
    cli();
    _PROTECTED_WRITE(CLKCTRL.OSCHFCTRLA, CLKCTRL_FREQSEL_24M_gc);
    sei();

    Serial.begin(115200);

    Serial.println(F("I2C: resetting bus..."));
    i2cReset();
    delay(100);
    Wire.begin();
    Wire.setClock(100000);
    Serial.println(F("I2C: ready at 100kHz"));

    devices.compass0 = &compass0;
    devices.compass1 = &compass1;

    display.setup(&devices);

    // Sensor 0: forward-facing, address 0x4B, INT=12, RST=14
    devices.compass0->init(0x4B, 12, 14);

    // Sensor 1: rear-facing (180° rotated), address 0x4A, INT=13, RST=15
    devices.compass1->init(0x4A, 13, 15);

    Serial.println(F("Setup complete."));
}

#define CAL_BUTTON_PIN  16
#define CAL_HOLD_MS   1000
#define CAL_TIMEOUT_MS 60000

static void runCalibration() {
    Serial.println(F("Calibration: started"));
    unsigned long start = millis();

    while (millis() - start < CAL_TIMEOUT_MS) {
        compass0.update();
        compass1.update();

        uint8_t acc0 = compass0.getMagAccuracy();
        uint8_t acc1 = compass1.getMagAccuracy();
        display.showCalibrating(acc0, acc1);

        if (acc0 == 3 && acc1 == 3) break;
    }

    compass0.saveCalibration();
    compass1.saveCalibration();
    display.showCalibrationSaved();
    delay(2000);
    Serial.println(F("Calibration: complete"));
}

static unsigned long buttonDownAt = 0;

void loop() {
    compass0.update();
    compass1.update();
    display.update();

    if (!digitalRead(CAL_BUTTON_PIN)) {
        if (buttonDownAt == 0) buttonDownAt = millis();
        else if (millis() - buttonDownAt >= CAL_HOLD_MS) {
            buttonDownAt = 0;
            runCalibration();
        }
    } else {
        buttonDownAt = 0;
    }
}
