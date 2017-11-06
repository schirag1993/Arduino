#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include<ArduinoJson.h>

int arduinoNumber = 0;
int relayPin = 4;

RF24 radio(7, 8);

const byte rxAddr[6] = "00001";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  radio.begin();
  radio.openReadingPipe(0, rxAddr);
  radio.startListening();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (radio.available())
  {
    StaticJsonBuffer<200> jsonBuffer;
    //Serial.println("Radio found");
    char msgBody[128];
    radio.read(&msgBody, sizeof(msgBody));
    Serial.println(msgBody);
    JsonObject& root = jsonBuffer.parseObject(msgBody);
    if (!root.success())
    {
      Serial.println("parseObject() failed");
      return;
    }
    const char* cmd = root["control"];
    int command = atoi(cmd);
  }
  else
  {
  }
}
