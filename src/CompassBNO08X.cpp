#include "CompassBNO08X.h"
#include <Arduino.h>
#include <Wire.h>

static uint8_t _nextSlot = 0;

void CompassBNO08X::setReports() {
    sh2_activate(_sh2Slot);
    Serial.println(F("BNO08x: enabling sensor reports..."));

    if (myIMU.enableMagnetometer(10)) {
        Serial.println(F("  [OK] Magnetometer (10ms interval, for calibration status)"));
    } else {
        Serial.println(F("  [FAIL] Magnetometer could not be enabled"));
    }

    if (myIMU.enableARVRStabilizedRotationVector(10)) {
        Serial.println(F("  [OK] ARVR Stabilized Rotation Vector (10ms interval)"));
    } else {
        Serial.println(F("  [FAIL] ARVR Stabilized Rotation Vector could not be enabled"));
    }
}

void CompassBNO08X::init(uint8_t addr, int intPin, int rstPin) {
    _sh2Slot = _nextSlot++;

    Serial.printf(F("BNO08x[%d]: initializing  INT:%d  RST:%d  addr:0x%02X\r\n"),
                  _sh2Slot, intPin, rstPin, addr);

    if (intPin != -1) pinMode(intPin, INPUT);
    if (rstPin != -1) pinMode(rstPin, OUTPUT);

    Serial.printf(F("BNO08x[%d]: calling begin()...\r\n"), _sh2Slot);
    delay(100);

    sh2_activate(_sh2Slot);
    if (!myIMU.begin(addr, Wire, intPin, rstPin)) {
        Serial.printf(F("BNO08x[%d]: [FAIL] not detected. Halting.\r\n"), _sh2Slot);
        while (1);
    }
    Serial.printf(F("BNO08x[%d]: [OK] device found and responding\r\n"), _sh2Slot);
    delay(1000);

    Serial.printf(F("BNO08x[%d]: sending calibration config...\r\n"), _sh2Slot);
    calibrate();

    Serial.printf(F("BNO08x[%d]: enabling reports...\r\n"), _sh2Slot);
    delay(500);
    setReports();

    Serial.printf(F("BNO08x[%d]: init complete\r\n"), _sh2Slot);
    delay(500);
}

static void printAccuracyLevel(uint8_t n) {
    if      (n == 0) Serial.print(F("Unreliable"));
    else if (n == 1) Serial.print(F("Low"));
    else if (n == 2) Serial.print(F("Medium"));
    else             Serial.print(F("High"));
}

static unsigned long previousMillis[2] = {0, 0};
#define DEBUG_INTERVAL_MS 500

static void quatToEuler(float qi, float qj, float qk, float qr,
                        float &yaw, float &pitch, float &roll) {
    float sqr = sq(qr), sqi = sq(qi), sqj = sq(qj), sqk = sq(qk);
    yaw   = atan2(2.0f * (qi * qj + qk * qr),  (sqi - sqj - sqk + sqr));
    pitch = asin(-2.0f * (qi * qk - qj * qr)  / (sqi + sqj + sqk + sqr));
    roll  = atan2(2.0f * (qj * qk + qi * qr), (-sqi - sqj + sqk + sqr));
}

bool CompassBNO08X::update() {
    sh2_activate(_sh2Slot);

    if (myIMU.wasReset()) {
        Serial.printf(F("BNO08x[%d]: sensor was reset\r\n"), _sh2Slot);
        setReports();
    }

    if (myIMU.getSensorEvent()) {
        if (myIMU.getSensorEventID() == SENSOR_REPORTID_MAGNETIC_FIELD) {
            magAccuracy = myIMU.getMagAccuracy();
        }
        else if (myIMU.getSensorEventID() == SENSOR_REPORTID_AR_VR_STABILIZED_ROTATION_VECTOR) {
            float qi = myIMU.getQuatI();
            float qj = myIMU.getQuatJ();
            float qk = myIMU.getQuatK();
            float qr = myIMU.getQuatReal();
            quatToEuler(qi, qj, qk, qr, yaw, pitch, roll);

            float b = fmod(degrees(yaw) + 90.0f, 360.0f);
            if (b < 0) b += 360.0f;
            heading = b;
        }
    }

    if ((millis() - previousMillis[_sh2Slot]) > DEBUG_INTERVAL_MS) {
        Serial.printf(F("[%d] Heading:%.3f  pitch=%.3f  roll=%.3f  mag="),
                      _sh2Slot, heading, degrees(pitch), degrees(roll));
        printAccuracyLevel(magAccuracy);
        Serial.println();
        previousMillis[_sh2Slot] = millis();
    }

    return false;
}

void CompassBNO08X::calibrate() {
    sh2_activate(_sh2Slot);
    Serial.printf(F("BNO08x[%d]: enabling dynamic calibration (accel+gyro+mag)...\r\n"), _sh2Slot);
    if (myIMU.setCalibrationConfig(SH2_CAL_ACCEL | SH2_CAL_GYRO | SH2_CAL_MAG)) {
        Serial.printf(F("BNO08x[%d]:   [OK] calibration config accepted\r\n"), _sh2Slot);
    } else {
        Serial.printf(F("BNO08x[%d]:   [FAIL] calibration config rejected. Halting.\r\n"), _sh2Slot);
        while (1) delay(10);
    }
}

bool CompassBNO08X::saveCalibration() {
    sh2_activate(_sh2Slot);
    bool ok = myIMU.saveCalibration();
    Serial.printf(F("BNO08x[%d]: calibration save %s\r\n"), _sh2Slot, ok ? "OK" : "FAILED");
    return ok;
}

double  CompassBNO08X::getHeading()     const { return heading; }
double  CompassBNO08X::getYaw()         const { return degrees(yaw); }
double  CompassBNO08X::getPitch()       const { return degrees(pitch); }
double  CompassBNO08X::getRoll()        const { return degrees(roll); }
uint8_t CompassBNO08X::getMagAccuracy() const { return magAccuracy; }
