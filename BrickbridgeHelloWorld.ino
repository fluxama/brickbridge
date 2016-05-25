/* 
 *  Hello World sketch for Mondo Brickbridge
 */

#include <Wire.h>

#define SLAVE_ADDRESS 0x04

void setup() 
{
    Serial.begin(9600);         // start serial for output
    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(receiveData);
    Wire.onRequest(sendData);
    Serial.println("Ready!");
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
}

int analogVal = 0;
int val = 0;
boolean receivedData = false;

void loop()
{
  if (receivedData) {
     Serial.print(val);
     receivedData = false;
   }
  analogVal = analogRead(A0);
}

// callback for receiving data
void receiveData(int byteCount)
{
    while (Wire.available()>0) {
      val=Wire.read();
      receivedData = true;
    }
    digitalWrite(13, LOW);
    delay(100);
    digitalWrite(13, HIGH);
}

// callback for sending data
void sendData()
{
  Wire.write(analogVal);
  digitalWrite(13, LOW);
  delay(100);
  digitalWrite(13, HIGH);
}

