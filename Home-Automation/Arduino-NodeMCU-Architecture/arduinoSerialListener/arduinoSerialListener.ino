#include <SoftwareSerial.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include<ArduinoJson.h>

RF24 radio(7, 8);
SoftwareSerial mySerial(9, 10); //- See more at: http://www.esp8266.com/viewtopic.php?f=32&t=10853#sthash.h0OCPHK3.dpuf

const byte rxAddr[6] = "00001";

int ledPin = 13;
int oldValue = -1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mySerial.begin(115200);
  radio.begin();
  pinMode(ledPin, OUTPUT);
  radio.openWritingPipe(rxAddr);
  radio.stopListening();
}

void loop() {
  // put your main code here, to run repeatedly:
  int command = -1;
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& controlData = jsonBuffer.createObject();
  if (mySerial.available())
  {
    delay(100);
    command = mySerial.read();
    if (command > -1 && oldValue != command)
    {
      Serial.println("Command is ");
      Serial.println(command);
      oldValue = command;
      controlData["mcu"] = "0";
      char cmd[8];
      itoa(command, cmd, 10);
      controlData["control"] = cmd;
      char stringCmd[64];
      controlData.printTo(stringCmd, sizeof(stringCmd));
      Serial.println("stringCmd: ");
      Serial.println(stringCmd);
      radio.write(&stringCmd, sizeof(stringCmd));
      delay(100);
    }
  }
}
