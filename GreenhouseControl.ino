#include <Servo.h>

// Pin Definitions
const int rainSensorPin = A0;     
const int rainThresholdBase = 500;
const int heavyRainThreshold = 800;
const int servoPin = 9;          

Servo roofServo;                
bool isRoofOpen = false;         
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

  // Check if it's heavy rain
  if (rainValue > heavyRainThreshold) {
    Serial.println("Heavy rain detected! Roof will not open.");
    lastRainTime = millis(); 
    if (isRoofOpen) {
      closeRoof();
    }
  }
  
  else if (rainValue > dynamicThreshold) {
    lastRainTime = millis(); 
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
  delay(1000); 
  Serial.println("Roof is now open.");
}

void closeRoof() {
  Serial.println("No rain detected for 5 minutes. Closing the roof...");
  roofServo.write(0); // Rotate servo back to 0° to close roof
  isRoofOpen = false;
  delay(1000); 
  Serial.println("Roof is now closed.");
}
