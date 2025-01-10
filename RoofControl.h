#ifndef ROOF_CONTROL_H
#define ROOF_CONTROL_H

#include <Servo.h>

class RoofControl {
public:
    RoofControl(int servoPin, int openAngle, int closeAngle);
    void openRoof();
    void closeRoof();
    bool isRoofOpen();
    void logStatus(const char* message);

private:
    Servo roofServo;
    bool roofState; // True if open, false if closed
    int openAngle;
    int closeAngle;
};

#endif // ROOF_CONTROL_H
