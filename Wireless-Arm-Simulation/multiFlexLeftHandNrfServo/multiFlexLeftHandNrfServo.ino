#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include<ArduinoJson.h>
#include <Servo.h>

RF24 radio(40, 53);
Servo wristServo;
Servo elbowServo;
Servo shoulderServo;

const byte rxAddr[6] = "00001";
int i = 0;

void setup()
{
  while (!Serial);
  Serial.begin(9600);
// Serial.println("Hello");
  radio.begin();
  radio.openReadingPipe(0, rxAddr);
  radio.startListening();
  wristServo.attach(13);
  elbowServo.attach(12);
  shoulderServo.attach(11);
}

void loop()
{
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
    const char* wristAngle = root["w"];
    const char* elbowAngle = root["e"];
    const char* shoulderAngle = root["s"];
    int w = atoi(wristAngle);
    int e = atoi(elbowAngle);
    int s = atoi(shoulderAngle);
    wristServo.write(w);
    elbowServo.write(e);
    shoulderServo.write(s);
    delay(10);
  }
  else
  {
  }
}
