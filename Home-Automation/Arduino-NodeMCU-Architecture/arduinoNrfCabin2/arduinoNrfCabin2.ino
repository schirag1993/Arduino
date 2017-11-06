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
  Serial.begin(115200);
  Serial.println("Starting radio");
  pinMode(relayPin, OUTPUT);
  radio.begin();
  radio.openReadingPipe(0, rxAddr);
  radio.startListening();
  Serial.println("Radio started");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (radio.available())
  {
    Serial.println("Radio available!");
    StaticJsonBuffer<200> jsonBuffer;
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
    if (command > 3 && command < 5)
    {
      if(command==4)
      {
        digitalWrite(relayPin, HIGH);
      }
      else
      {
        digitalWrite(relayPin, LOW);
      }
    }
    else if(command<2)
    {
      if(command==1)
      {
        digitalWrite(relayPin, HIGH);
      }
      else
      {
        digitalWrite(relayPin, LOW);
      }
    }
  }
  else
  {
  }
}
