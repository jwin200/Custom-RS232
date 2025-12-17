#include <PWM.h>
#include <SoftwareSerial.h>

#define CARRIER_PIN 5
#define TX_PIN 3
#define RX_PIN 0

SoftwareSerial soft_serial(RX_PIN, TX_PIN);
String serialMessage = "";
String receivedMessage;

void setup() {
  SetPinFrequency(CARRIER_PIN, 38000);   // Create 38kHz carrier wave
  Serial.begin(2400);
  soft_serial.begin(2400);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(CARRIER_PIN, OUTPUT);  // Set pin 5 as PWM
  pinMode(TX_PIN, OUTPUT);  // Set pin 3 as software serial out
  pinMode(RX_PIN, INPUT);
}

void loop() {
  // If data is available, receive
  while(soft_serial.available() > 0) {
    digitalWrite(LED_BUILTIN, HIGH);  // Visual confirmation of data receipt
    char receivedChar = Serial.read();
    if (receivedChar == '\n') {
      receivedMessage += receivedChar;  // End message and print at line breaks
      Serial.println(receivedMessage);
      receivedMessage = "";
      digitalWrite(LED_BUILTIN, LOW);
      break;
    } else {
      receivedMessage += receivedChar;
    }
  }

  //If no data being received, transmit
  int i = 0;
  digitalWrite(LED_BUILTIN, HIGH);
  while (i < 50) {  // Print message 50 times
    soft_serial.println("Hi there! This is my final project.");
    i += 1;
  }
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

