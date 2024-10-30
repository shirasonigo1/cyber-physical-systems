const int ledPin1 = 2; // LED connected to pin D12
const int ledPin2 = 3; // LED connected to pin D11

void setup() {
  Serial.begin(9600); // Set baud rate to match Processing
  pinMode(ledPin1, OUTPUT); // Set D12 as an output
  pinMode(ledPin2, OUTPUT); // Set D11 as an output
}

void loop() {
  if (Serial.available() > 0) { // Check if data is available
    char incomingChar = Serial.read(); // Read the incoming byte
    Serial.println(incomingChar); // Print received value for debugging

    // Control LEDs based on received number
    if (incomingChar == '1') {
      digitalWrite(ledPin1, HIGH);  // Turn on LED at D12
      digitalWrite(ledPin2, LOW);   // Turn off LED at D11
    } else if (incomingChar == '2') {
      digitalWrite(ledPin1, LOW);   // Turn off LED at D12
      digitalWrite(ledPin2, HIGH);  // Turn on LED at D11
    } else {
      digitalWrite(ledPin2, HIGH);
    }
  }
}
