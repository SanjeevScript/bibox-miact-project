#include "RoofControl.h"
#include "Arduino.h"

RoofControl::RoofControl(int servoPin, int openAngle, int closeAngle)
    : openAngle(openAngle), closeAngle(closeAngle), roofState(false) {
    roofServo.attach(servoPin);
    roofServo.write(closeAngle); // Initialize roof closed
}

void RoofControl::openRoof() {
    if (!roofState) {
        roofServo.write(openAngle);
        roofState = true;
        logStatus("Roof opened.");
    }
}

void RoofControl::closeRoof() {
    if (roofState) {
        roofServo.write(closeAngle);
        roofState = false;
        logStatus("Roof closed.");
    }
}

bool RoofControl::isRoofOpen() {
    return roofState;
}

void RoofControl::logStatus(const char* message) {
    if (DEBUG_MODE) {
        Serial.println(message);
    }
}
