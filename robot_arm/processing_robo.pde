import oscP5.*;
import netP5.*;
import processing.serial.*;  // Add the serial library

Serial port;  // Declare the Serial object
OscP5 oscP5;
NetAddress remoteLocation;

void setup() {
  size(400, 400);
  
  // Initialize serial connection to Arduino (adjust the port number as needed)
  println("Available serial ports:");
  printArray(Serial.list());
  port = new Serial(this, Serial.list()[3], 9600);  // Adjust the index if necessary
  
  // Initialize OSC communication and specify the remote location (receiver IP and port)
  oscP5 = new OscP5(this, 12000);  // Listening for incoming messages on port 12000
  remoteLocation = new NetAddress("127.0.0.1", 12000);  // Sending to localhost (port 12000)
}

void draw() {
  background(200);  // Visual representation of the mouse position
  fill(0);
  ellipse(mouseX, mouseY, 10, 10);  // Display mouse cursor as a circle

  // Send OSC message with mouse position
  sendMousePositionAsOSC();
}

// Function to send mouse position as an OSC message
void sendMousePositionAsOSC() {
  OscMessage msg = new OscMessage("/arm/move");
  
  // Add current mouse X and Y positions
  msg.add((float)mouseX);  // Cast to float for consistency
  msg.add((float)mouseY);
  
  // Send the message to the remote location
  oscP5.send(msg, remoteLocation);
  
  println("Sent OSC message: X = " + mouseX + ", Y = " + mouseY);
}

// Function to receive incoming OSC messages and forward them to Arduino
void oscEvent(OscMessage theOscMessage) {
  if (theOscMessage.checkAddrPattern("/arm/move")) {
    float xPos = theOscMessage.get(0).floatValue();  // Get the first OSC argument (xPos)
    float yPos = theOscMessage.get(1).floatValue();  // Get the second OSC argument (yPos)
    
    // Optionally print the positions to the console for debugging
    println("Received OSC message: X = " + xPos + ", Y = " + yPos);
    
    // Format the data into a string to send to the Arduino over serial
    String dataToSend = xPos + "," + yPos + "\n";  // Comma-separated values
    
    // Send data to the Arduino via serial
    port.write(dataToSend);
  }
}
