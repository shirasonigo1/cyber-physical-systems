#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// Store the target position for each servo
int targetPos1 = 90;
int targetPos2 = 100;
int targetPos3 = 140;
int targetPos4 = 180;

int currentPos1 = 100;
int currentPos2 = 100;
int currentPos3 = 50;
int currentPos4 = 0;

int speed = 1; // The smaller the value, the smoother the movement

String receivedData = "";
float xPos = 0;
float yPos = 0;

void setup() {
  Serial.begin(9600);
  // Attach each servo to its respective pin
  servo1.attach(3);   // attaches the base
  servo2.attach(10);  // attaches the shoulder
  servo3.attach(6);  // attaches the elbow
  servo4.attach(9);  // attaches the clow

  // Set initial positions
  servo1.write(currentPos1);
  servo2.write(currentPos2);
  servo3.write(currentPos3);
  servo4.write(currentPos4);
  Serial.println("Servos initialized to starting positions.");
}

void loop() {
  if (Serial.available() > 0) {
    // Read the incoming string until newline character
    String data = Serial.readStringUntil('\n');
    // Parse and execute the command
    getValues(data);
  }
}

void getValues(String data) {
  // Example: split the data into xPos and yPos based on comma
  int commaIndex = data.indexOf(',');  // Find the position of the comma
  
  if (commaIndex > 0) {
    String xPosString = data.substring(0, commaIndex);  // Extract the xPos part
    String yPosString = data.substring(commaIndex + 1);

      // Convert the extracted strings to floats
    float xPos = xPosString.toFloat();
    float yPos = yPosString.toFloat();

    bool isLeft = xPos < 185;
    bool isRight = xPos > 185;
    bool isUp = yPos < 185;
    bool isDown = yPos > 185;

    if (isLeft && isUp) {
      // Move left and up
      Serial.println("Moving servos to target positions..."); // Debug output
      smoothMoveToTarget(servo1, currentPos1, 60);
      smoothMoveToTarget(servo2, currentPos2, 100);
      smoothMoveToTarget(servo3, currentPos3, 140);
      smoothMoveToTarget(servo4, currentPos4, 90);
    } else if (isLeft && isDown) {
      // Move left and down
      Serial.println("Moving down"); // Debug output
      smoothMoveToTarget(servo1, currentPos1, 60);    
      smoothMoveToTarget(servo2, currentPos2, 160);  
      smoothMoveToTarget(servo3, currentPos3, 10);   
      smoothMoveToTarget(servo4, currentPos4, 0);    
    } else if (isRight && isUp) {
      // Up and right
      Serial.println("Moving down"); // Debug output
      smoothMoveToTarget(servo1, currentPos1, 120);    
      smoothMoveToTarget(servo2, currentPos2, 100);  
      smoothMoveToTarget(servo3, currentPos3, 140);   // Move back to starting pos3 = 50
      smoothMoveToTarget(servo4, currentPos4, 90);    // Move back to starting pos4 = 0
    }  else if (isRight && isDown){
        Serial.println("Moving down"); // Debug output
        smoothMoveToTarget(servo1, currentPos1, 120);   
        smoothMoveToTarget(servo2, currentPos2, 160);  // Move back to starting pos2 = 100
        smoothMoveToTarget(servo3, currentPos3, 10);   // Move back to starting pos3 = 50
        smoothMoveToTarget(servo4, currentPos4, 0);    // Move back to starting pos4 = 0
    } else {
       Serial.println("Unknown movement");
    }
  }
}

  // // Move each servo to the target position smoothly
  // Serial.println("Moving servos to target positions..."); // Debug output
  // smoothMoveToTarget(servo1, currentPos1, targetPos1);
  // smoothMoveToTarget(servo2, currentPos2, targetPos2);
  // smoothMoveToTarget(servo3, currentPos3, targetPos3);
  // smoothMoveToTarget(servo4, currentPos4, targetPos4);

  // // Wait for some time at the target position
  // delay(15); 
  // Serial.println("Reached target positions."); // Debug output

  // Serial.println("Moving down"); // Debug output
  // smoothMoveToTarget(servo1, currentPos1, 90);    // Move back to starting pos1 = 0
  // smoothMoveToTarget(servo2, currentPos2, 200);  // Move back to starting pos2 = 100
  // smoothMoveToTarget(servo3, currentPos3, 10);   // Move back to starting pos3 = 50
  // smoothMoveToTarget(servo4, currentPos4, 0);    // Move back to starting pos4 = 0

  // // Move each servo back to the original starting position smoothly
  // Serial.println("Moving servos back to starting positions..."); // Debug output
  // smoothMoveToTarget(servo1, currentPos1, 90);    // Move back to starting pos1 = 0
  // smoothMoveToTarget(servo2, currentPos2, 100);  // Move back to starting pos2 = 100
  // smoothMoveToTarget(servo3, currentPos3, 50);   // Move back to starting pos3 = 50
  // smoothMoveToTarget(servo4, currentPos4, 0);    // Move back to starting pos4 = 0

  // // Wait for some time before repeating the loop
  // delay(15); 


// Function to smoothly move the servo to the target position
void smoothMoveToTarget(Servo &servo, int &currentPos, int targetPos) {
  Serial.print("Current position: "); 
  Serial.print(currentPos); 
  Serial.print(" | Target position: "); 
  Serial.println(targetPos); 
  while (currentPos < targetPos) {
    currentPos += speed; // Increment position
    Serial.println(currentPos); 
    servo.write(currentPos);
    delay(15); // Control the speed of the movement
  }
  while (currentPos > targetPos) {
    currentPos -= speed; // Decrement position
    Serial.println(currentPos); 
    servo.write(currentPos);
    delay(15);
  }
}

