#include <NewPing.h>
#include <Servo.h>
#include <AFMotor.h>

// Pin definitions
#define RIGHT A2              // Right IR sensor connected to analog pin A2 of Arduino Uno
#define LEFT A3               // Left IR sensor connected to analog pin A3 of Arduino Uno
#define TRIGGER_PIN A1        // Trigger pin connected to analog pin A1 of Arduino Uno
#define ECHO_PIN A0           // Echo pin connected to analog pin A0 of Arduino Uno
#define MAX_DISTANCE 100      // Maximum ping distance

// Variables
unsigned int distance = 0;    // Variable to store ultrasonic sensor distance
unsigned int Right_Value = 0; // Variable to store Right IR sensor value
unsigned int Left_Value = 0;  // Variable to store Left IR sensor value

// Create objects
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup
AF_DCMotor Motor1(1, MOTOR12_1KHZ);
AF_DCMotor Motor2(2, MOTOR12_1KHZ);
AF_DCMotor Motor3(3, MOTOR34_1KHZ);
AF_DCMotor Motor4(4, MOTOR34_1KHZ);
Servo myservo;

void setup() {
  Serial.begin(9600); // Initialize serial communication
  myservo.attach(10); // Attach servo to pin 10
  pinMode(RIGHT, INPUT); // Set RIGHT IR sensor as input
  pinMode(LEFT, INPUT);  // Set LEFT IR sensor as input
}

void loop() {
  delay(50);                             // Wait 50ms between pings
  distance = sonar.ping_cm();            // Measure distance using ultrasonic sensor
  Right_Value = digitalRead(RIGHT);      // Read the value from Right IR sensor
  Left_Value = digitalRead(LEFT);        // Read the value from Left IR sensor

  Serial.print("Distance: ");
  Serial.println(distance);              // Print the distance in serial monitor
  Serial.print("Right: ");
  Serial.println(Right_Value);           // Print the Right IR sensor value
  Serial.print("Left: ");
  Serial.println(Left_Value);            // Print the Left IR sensor value

  // If object is detected within 10-30 cm range
  if (distance >= 10 && distance <= 30) {
    if (Right_Value == 1 && Left_Value == 1) {
      // Move forward
      Motor1.setSpeed(160);
      Motor1.run(FORWARD);
      Motor2.setSpeed(160);
      Motor2.run(FORWARD);
      Motor3.setSpeed(160);
      Motor3.run(FORWARD);
      Motor4.setSpeed(160);
      Motor4.run(FORWARD);
    } else if (Right_Value == 0 && Left_Value == 1) {
      // Turn right
      Motor1.setSpeed(250);
      Motor1.run(FORWARD);
      Motor2.setSpeed(250);
      Motor2.run(FORWARD);
      Motor3.setSpeed(150);
      Motor3.run(BACKWARD);
      Motor4.setSpeed(150);
      Motor4.run(BACKWARD);
    } else if (Right_Value == 1 && Left_Value == 0) {
      // Turn left
      Motor1.setSpeed(150);
      Motor1.run(BACKWARD);
      Motor2.setSpeed(150);
      Motor2.run(BACKWARD);
      Motor3.setSpeed(250);
      Motor3.run(FORWARD);
      Motor4.setSpeed(250);
      Motor4.run(FORWARD);
    }
  } else {
    // Stop when no object is in range
    Motor1.setSpeed(0);
    Motor1.run(RELEASE);
    Motor2.setSpeed(0);
    Motor2.run(RELEASE);
    Motor3.setSpeed(0);
    Motor3.run(RELEASE);
    Motor4.setSpeed(0);
    Motor4.run(RELEASE);
  }
}
