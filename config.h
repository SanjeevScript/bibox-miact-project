#ifndef CONFIG_H
#define CONFIG_H

// Rain Sensor Configuration
const int RAIN_SENSOR_PIN = A0;   
const int RAIN_THRESHOLD_BASE = 500; 

// Servo Motor Configuration
const int SERVO_PIN = 9;          
const int SERVO_OPEN_ANGLE = 90;  
const int SERVO_CLOSE_ANGLE = 0; 

// Timing Configuration
const unsigned long RAIN_DELAY = 300000; /=

const bool DEBUG_MODE = true;    

#endif 
