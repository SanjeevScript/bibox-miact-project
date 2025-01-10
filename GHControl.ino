#include "config.h"
#include "RoofControl.h"

RoofControl roof(SERVO_PIN, SERVO_OPEN_ANGLE, SERVO_CLOSE_ANGLE);
unsigned long lastRainTime = 0;

void setup() {
    if (DEBUG_MODE) {
        Serial.begin(9600);
        Serial.println("Greenhouse System Initialized.");
    }
}

void loop() {
    int rainValue = analogRead(RAIN_SENSOR_PIN);

    if (DEBUG_MODE) {
        Serial.print("Rain Sensor Value: ");
        Serial.println(rainValue);
    }

    int dynamicThreshold = RAIN_THRESHOLD_BASE + (rainValue / 10);
    if (rainValue > dynamicThreshold) {
        lastRainTime = millis();
        roof.openRoof();
    } else if (millis() - lastRainTime > RAIN_DELAY) {
        roof.closeRoof();
    }

    delay(1000); // Small delay to reduce polling frequency
}
