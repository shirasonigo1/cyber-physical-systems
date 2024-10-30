import oscP5.*;
import netP5.*;
import processing.serial.*;

OscP5 oscP5;
Serial port;
int receivedNumber;

void setup() {
  size(400, 200);
  oscP5 = new OscP5(this, 12000); 
  
  println("Available serial ports:");
  printArray(Serial.list());
  port = new Serial(this, Serial.list()[3], 9600);
}

void draw() {
  background(255);
  fill(0);
  textSize(32);
  
  // Display received number
  if (receivedNumber == 1 || receivedNumber == 2) {
    text("Received: " + receivedNumber, width / 2 - 80, height / 2);
  }
}

void oscEvent(OscMessage msg) {
  if (msg.checkAddrPattern("/wek/outputs")) { // Check if message is from Wekinator's output
    float value = msg.get(0).floatValue(); // Get the first value in the message
    receivedNumber = (int) value;
    
    // Send received number to Arduino via serial
    port.write(str(receivedNumber)); 
    println("Sent to Arduino: " + receivedNumber);
  }
}
