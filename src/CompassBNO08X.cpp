//
// Created by redha on 2/15/2025.
//

#include <SparkFun_BNO08x_Arduino_Library.h>
#include "CompassBNO08X.h"

static BNO08x myIMU;

// For the most reliable interaction with the SHTP bus, we need
// to use hardware reset control, and to monitor the H_INT pin.
// The H_INT pin will go low when its okay to talk on the SHTP bus.
// Note, these can be other GPIO if you like.
// Define as -1 to disable these features.
#define BNO08X_INT  9
//#define BNO08X_INT  -1
#define BNO08X_RST  10
//#define BNO08X_RST  -1

#define BNO08X_ADDR 0x4B  // SparkFun BNO08x Breakout (Qwiic) defaults to 0x4B
//#define BNO08X_ADDR 0x4A // Alternate address if ADR jumper is closed

// Here is where you define the sensor outputs you want to receive
void CompassBNO08X::setReports() {
    Serial.println("Setting desired reports");
    if (myIMU.enableMagnetometer(1) == true) {
        Serial.println(F("Magnetometer enabled"));
        Serial.println(F("Output in form x, y, z, in uTesla"));
    } else {
        Serial.println("Could not enable magnetometer");
    }

    if (myIMU.enableGameRotationVector(1) == true) {
        Serial.println(F("Game Rotation vector enabled"));
        Serial.println(F("Output in form i, j, k, real"));
    } else {
        Serial.println("Could not enable game rotation vector");
    }
}

void CompassBNO08X::init() {
    Serial.println("Initializing BNO08x");

    pinMode(BNO08X_INT, INPUT);
    pinMode(BNO08X_RST, OUTPUT);

    //if (myIMU.begin() == false) {  // Setup without INT/RST control (Not Recommended)
    if (!myIMU.begin(BNO08X_ADDR, Wire, BNO08X_INT, BNO08X_RST)) {
        Serial.println("BNO08x not detected at default I2C address. Check your jumpers and the hookup guide. Freezing...");
        while (1);
    }

    Serial.println("BNO08x found!");
    calibrate();

    setReports();
    Serial.println("Reading events");
}

//Given a accuracy number, print what it means
void printAccuracyLevel(byte accuracyNumber)
{
    if(accuracyNumber == 0) Serial.print(F("Unreliable"));
    else if(accuracyNumber == 1) Serial.print(F("Low"));
    else if(accuracyNumber == 2) Serial.print(F("Medium"));
    else if(accuracyNumber == 3) Serial.print(F("High"));
}

unsigned long previousMillis = 0;
#define DEBUG_INTERVAL_MS 500

bool CompassBNO08X::update() {
    if(myIMU.wasReset()) {
        Serial.print("sensor was reset ");
        setReports();
    }

    // Has a new event come in on the Sensor Hub Bus?
    if (myIMU.getSensorEvent() == true) {
        // is the event a report of the magnetometer?
        if (myIMU.getSensorEventID() == SENSOR_REPORTID_MAGNETIC_FIELD) {
            mx = myIMU.getMagX();
            my = myIMU.getMagY();
            mz = myIMU.getMagZ();
            magAccuracy = myIMU.getMagAccuracy();
        }
            // is the event a report of the game rotation vector?
        else if (myIMU.getSensorEventID() == SENSOR_REPORTID_GAME_ROTATION_VECTOR) {
            quatI = myIMU.getGameQuatI();
            quatJ = myIMU.getGameQuatJ();
            quatK = myIMU.getGameQuatK();
            quatReal = myIMU.getGameQuatReal();
        }
    }

    // time since last debug data printed to terminal
    unsigned long microsSinceLastSerialPrint = (millis() - previousMillis);

    // Only print data to the terminal at a user deficed interval
    if(microsSinceLastSerialPrint > DEBUG_INTERVAL_MS)
    {
        //float azimuth = atan2(mx, my) * 180.0 / PI;

        float sqr = sq(quatReal);
        float sqi = sq(quatI);
        float sqj = sq(quatJ);
        float sqk = sq(quatK);

        float yaw = atan2(2.0 * (quatI * quatJ + quatK * quatReal), (sqi - sqj - sqk + sqr));
        float pitch = asin(-2.0 * (quatI * quatK - quatJ * quatReal) / (sqi + sqj + sqk + sqr));
        float roll = atan2(2.0 * (quatJ * quatK + quatI * quatReal), (-sqi - sqj + sqk + sqr));

        float sinRoll = sin(roll);
        float cosRoll = cos(roll);
        float sinPitch = sin(pitch);
        float cosPitch = cos(pitch);

        float LHS = -mx * cosPitch + my * sinPitch*sinRoll + mz * sinPitch * cosRoll;
        float RHS = mz * sinRoll - my * cosRoll;
        float bearing = atan2(-LHS, RHS) * 57.3;
        bearing += 90;
        if(bearing < 0) bearing += 360;

        Serial.printf(F("Reading: (%f), yaw=%f, pitch=%f, roll=%f"), bearing, yaw, pitch, roll);
        printAccuracyLevel(magAccuracy);
        Serial.println();

//        Serial.print(mx, 2);
//        Serial.print("\t\t");
//        Serial.print(my, 2);
//        Serial.print("\t\t");
//        Serial.print(mz, 2);
//        Serial.print("\t\t");
//        printAccuracyLevel(magAccuracy);
//        Serial.print("\t\t");
//
//        Serial.print(quatI, 2);
//        Serial.print("\t\t");
//        Serial.print(quatJ, 2);
//        Serial.print("\t\t");
//        Serial.print(quatK, 2);
//        Serial.print("\t\t");
//        Serial.print(quatReal, 2);
//        Serial.print("\t\t");
//
//        Serial.print(microsSinceLastSerialPrint);
//        Serial.println();
        previousMillis = millis();
    }

    if(Serial.available())
    {
        byte incoming = Serial.read();

        if(incoming == 's')
        {
            // Saves the current dynamic calibration data (DCD) to memory
            // Note, The BNO08X stores updated Dynamic Calibration Data (DCD) to RAM
            // frequently (every 5 seconds), so this command may not be necessary
            // depending on your application.
            if (myIMU.saveCalibration() == true) {
                Serial.println(F("Calibration data was saved successfully"));
            } else {
                Serial.println("Save Calibration Failure");
            }
        }
    }

    return false;
}

void CompassBNO08X::calibrate() {
    // Enable dynamic calibration for desired sensors (accel, gyro, and mag)
    // uncomment/comment out as needed to try various options
    if (myIMU.setCalibrationConfig(SH2_CAL_ACCEL || SH2_CAL_GYRO || SH2_CAL_MAG)) { // all three sensors
        //if (myIMU.setCalibrationConfig(SH2_CAL_ACCEL || SH2_CAL_MAG) == true) { // Default settings
        //if (myIMU.setCalibrationConfig(SH2_CAL_ACCEL) == true) { // only accel
        Serial.println(F("Calibration Command Sent Successfully"));
    } else {
        Serial.println("Could not send Calibration Command. Freezing...");
        while(1) delay(10);
    }
}

int CompassBNO08X::getHeading() const {
    return 0;
}

double CompassBNO08X::getYaw() const {
    return 0;
}

double CompassBNO08X::getPitch() const {
    return 0;
}

double CompassBNO08X::getRoll() const {
    return 0;
}
