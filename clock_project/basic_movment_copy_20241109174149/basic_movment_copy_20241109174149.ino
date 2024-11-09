#include <Servo.h>

Servo myservo;
int servoPos = 0;           // Current position of the servo
int servoIncrement = 1;     // Step size (1 degree at a time)
unsigned long lastServoMove = 0; // Time of last servo movement
const int servoInterval = 15;    // Interval for servo movement in ms

#define IN1 12
#define IN2 11
#define IN3 10
#define IN4 9

int Steps = 0;
boolean Direction = false;
unsigned long last_time;
unsigned long currentMillis;
int steps_left = 4095;
long time;

void setup() {
  Serial.begin(115200);

  // Stepper motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Servo motor setup
  myservo.attach(8);
  myservo.write(servoPos);
}

void loop() {
  // Non-blocking servo movement
  unsigned long currentMillis = millis();
  if (currentMillis - lastServoMove >= servoInterval) {
    lastServoMove = currentMillis;
    servoPos += servoIncrement;

    if (servoPos >= 180 || servoPos <= 0) {
      servoIncrement = -servoIncrement;  // Reverse direction
    }
    myservo.write(servoPos);  // Move the servo to the new position
  }

  // Stepper motor control
  if (Serial.available() > 0) {
    int input = Serial.parseInt();
    if (input == 1) {
      Direction = !Direction;
    }
  }

  if (steps_left > 0) {
    currentMillis = micros();
    if (currentMillis - last_time >= 1000) {
      stepper(1);
      time = time + micros() - last_time;
      last_time = micros();
      steps_left--;
    }
  } else {
    Serial.println(time);
    Serial.println("Wait...!");
    steps_left = 4095;
  }
}

void stepper(int xw) {
  for (int x = 0; x < xw; x++) {
    switch (Steps) {
      case 0:
        digitalWrite(IN1, LOW); 
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        break; 
      case 1:
        digitalWrite(IN1, LOW); 
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, HIGH);
        break; 
      case 2:
        digitalWrite(IN1, LOW); 
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        break; 
      case 3:
        digitalWrite(IN1, LOW); 
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        break; 
      case 4:
        digitalWrite(IN1, LOW); 
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        break; 
      case 5:
        digitalWrite(IN1, HIGH); 
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        break; 
      case 6:
        digitalWrite(IN1, HIGH); 
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        break; 
      case 7:
        digitalWrite(IN1, HIGH); 
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        break; 
      default:
        digitalWrite(IN1, LOW); 
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        break; 
    }
    SetDirection();
  }
}

void SetDirection() {
  if (Direction) { 
    Steps++;
  } else {
    Steps--; 
  }
  if (Steps > 7) { Steps = 0; }
  if (Steps < 0) { Steps = 7; }
}
