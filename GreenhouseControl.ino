#include <Servo.h>

// Pin Definitions
const int rainSensorPin = A0;     // Rain sensor analog pin
const int rainThresholdBase = 500; // Base rain threshold
const int servoPin = 9;          // Servo motor connected to pin 9

Servo roofServo;                 // Servo motor object
bool isRoofOpen = false;         // Tracks the current state of the roof
unsigned long lastRainTime = 0;  // Tracks the last time rain was detected
const unsigned long delayDuration = 300000; // 5 minutes delay in milliseconds

void setup() {
  pinMode(rainSensorPin, INPUT); // Set rain sensor as input
  roofServo.attach(servoPin);    // Attach servo to its pin
  roofServo.write(0);            // Start with roof closed

  Serial.begin(9600);            // Start Serial Monitor
  Serial.println("Greenhouse System Initialized.");
  Serial.println("Roof is closed. Awaiting rain detection...");
}

void loop() {
  int rainValue = analogRead(rainSensorPin);  // Read rain sensor value
  Serial.print("Current Rain Sensor Value: ");
  Serial.println(rainValue);

  int dynamicThreshold = calculateDynamicThreshold(); // Adjust threshold
  Serial.print("Dynamic Rain Threshold: ");
  Serial.println(dynamicThreshold);

  if (rainValue > dynamicThreshold) {
    lastRainTime = millis(); // Update last rain time
    if (!isRoofOpen) {
      openRoof(); // Open the roof if it's not already open
    }
  } else if (millis() - lastRainTime > delayDuration) {
    if (isRoofOpen) {
      closeRoof(); // Close the roof if rain hasn't been detected for 5 minutes
    }
  }

  delay(1000); // Small delay to avoid rapid polling
}

int calculateDynamicThreshold() {
  // Simulates dynamic threshold adjustment
  return rainThresholdBase + (analogRead(rainSensorPin) / 10); // Example logic
}

void openRoof() {
  Serial.println("Rain detected! Opening the roof...");
  roofServo.write(90); // Rotate servo to 90° to open roof
  isRoofOpen = true;
  delay(1000); // Ensure stable state
  Serial.println("Roof is now open.");
}

void closeRoof() {
  Serial.println("No rain detected for 5 minutes. Closing the roof...");
  roofServo.write(0); // Rotate servo back to 0° to close roof
  isRoofOpen = false;
  delay(1000); // Ensure stable state
  Serial.println("Roof is now closed.");
}
