#include "arduino_secrets.h"

#include <IRremote.hpp>

// Motor Pins
int LFront_IN1 = 7;
int LFront_IN2 = 8;
int LRear_IN3 = 9;
int LRear_IN4 = 10;

int RFront_IN1 = 2;
int RFront_IN2 = 3;
int RRear_IN3 = 4;
int RRear_IN4 = 5;

// Ultrasonic Sensor Pins
const int trigPin = 12;
const int echoPin = 11;

// IR Remote Control Pin
const int RECV_PIN = 6;

// Variables
long duration;
int distance;

bool firstCheck = true;
bool autoMode = false; // Start in automatic mode

void setup() {
  // Set motor pins as output
  pinMode(LFront_IN1, OUTPUT);
  pinMode(LFront_IN2, OUTPUT);
  pinMode(LRear_IN3, OUTPUT);
  pinMode(LRear_IN4, OUTPUT);

  pinMode(RFront_IN1, OUTPUT);
  pinMode(RFront_IN2, OUTPUT);
  pinMode(RRear_IN3, OUTPUT);
  pinMode(RRear_IN4, OUTPUT);

  // Set sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Start serial communication
  Serial.begin(9600);

  // Start IR receiver
  IrReceiver.begin(RECV_PIN,ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()) {
    handleIRInput(IrReceiver.decodedIRData.decodedRawData); // Handle remote control input
    Serial.println(IrReceiver.decodedIRData.decodedRawData);
    
    IrReceiver.resume();
  }

  if (autoMode) {
    automaticMode();
  } else {
    manualMode();
  }
}

void handleIRInput(unsigned long input) {
  // Replace 0xFF02FD with the actual code of the button to switch modes
  if (input == 3208707840) { // Example: 'Play/Pause' button
    autoMode = !autoMode; // Toggle mode
    Serial.println(autoMode ? "Auto Mode" : "Manual Mode");
    stopMotors(); // Stop motors on mode change
  }

  if (!autoMode) {
    // Handle manual control commands
    switch (input) {
      case 4127850240: // 'Up' button
        moveForward();
        break;
      case 4161273600: // 'Down' button
        reverseMotors();
        break;
      case 3141861120: // 'Left' button
        turnLeft();
        break;
      case 3158572800: // 'Right' button
        turnRight();
        break;
      case 3125149440: // 'Stop' button
        stopMotors();
        break;
    }
  }
}

void automaticMode() {
  distance = measureDistance();
  
  if (firstCheck) {
    turnAround();
  }

  // If an object is close
  if (distance < 15 && !firstCheck) {
    stopMotors();
    delay(1000);
    
    int randomNumber = random(1, 4);
    if (randomNumber == 1) {
      turnRight(); 
    } else if (randomNumber == 2) {
      turnLeft();
    } else {
      turnAround();
    }
    delay(1000);
  } else if(!firstCheck) {
    moveForward();
  }

  if (firstCheck) {
    firstCheck = !firstCheck;
  }
}

void manualMode() {
  // Do nothing, just wait for remote inputs
}

void moveForward() {
  // Forward for left motors
  digitalWrite(LFront_IN1, LOW);
  digitalWrite(LFront_IN2, HIGH);
  digitalWrite(LRear_IN3, LOW);
  digitalWrite(LRear_IN4, HIGH);

  // Forward for right motors
  digitalWrite(RFront_IN1, LOW);
  digitalWrite(RFront_IN2, HIGH);
  digitalWrite(RRear_IN3, LOW);
  digitalWrite(RRear_IN4, HIGH);
}

void reverseMotors() {
  // Reverse for left motors
  digitalWrite(LFront_IN1, HIGH);
  digitalWrite(LFront_IN2, LOW);
  digitalWrite(LRear_IN3, HIGH);
  digitalWrite(LRear_IN4, LOW);

  // Reverse for right motors
  digitalWrite(RFront_IN1, HIGH);
  digitalWrite(RFront_IN2, LOW);
  digitalWrite(RRear_IN3, HIGH);
  digitalWrite(RRear_IN4, LOW);
}

void stopMotors() {
  // Stop all motors
  digitalWrite(LFront_IN1, LOW);
  digitalWrite(LFront_IN2, LOW);
  digitalWrite(LRear_IN3, LOW);
  digitalWrite(LRear_IN4, LOW);

  digitalWrite(RFront_IN1, LOW);
  digitalWrite(RFront_IN2, LOW);
  digitalWrite(RRear_IN3, LOW);
  digitalWrite(RRear_IN4, LOW);
}

void turnRight() {
  // Turn right by reversing left motors and stopping right motors
  digitalWrite(LFront_IN1, HIGH);
  digitalWrite(LFront_IN2, LOW);
  digitalWrite(LRear_IN3, HIGH);
  digitalWrite(LRear_IN4, LOW);

  digitalWrite(RFront_IN1, LOW);
  digitalWrite(RFront_IN2, HIGH);
  digitalWrite(RRear_IN3, LOW);
  digitalWrite(RRear_IN4, HIGH);
}

void turnLeft() {
  // Turn left by reversing right motors and stopping right motors
  digitalWrite(LFront_IN1, LOW);
  digitalWrite(LFront_IN2, HIGH);
  digitalWrite(LRear_IN3, LOW);
  digitalWrite(LRear_IN4, HIGH);

  digitalWrite(RFront_IN1, HIGH);
  digitalWrite(RFront_IN2, LOW);
  digitalWrite(RRear_IN3, HIGH);
  digitalWrite(RRear_IN4, LOW);
}

void turnAround() {
  // left motors reversed
  digitalWrite(LFront_IN1, HIGH);
  digitalWrite(LFront_IN2, LOW);
  digitalWrite(LRear_IN3, HIGH);
  digitalWrite(LRear_IN4, LOW);
  
  // right motors forward
  digitalWrite(RFront_IN1, LOW);
  digitalWrite(RFront_IN2, HIGH);
  digitalWrite(RRear_IN3, LOW);
  digitalWrite(RRear_IN4, HIGH);

  delay(500);
  stopMotors();
}

int measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  return distance;
}
