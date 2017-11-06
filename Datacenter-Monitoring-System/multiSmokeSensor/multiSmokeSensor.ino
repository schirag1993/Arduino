#include<ArduinoJson.h>

const int gasPin1 = 7;
const int gasPin2 = 8;
int s01 = 0;
int s02 = 0;

void setup()
{
  Serial.begin(9600); //Initialize serial port - 9600 bps
}

JsonObject& getSmokeData()
{
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& rackData = jsonBuffer.createObject();
  s01 = digitalRead(gasPin1);
  s02 = digitalRead(gasPin2);
  Serial.println(s01);
  Serial.println(s02);
  JsonArray& smoke = rackData.createNestedArray("smoke");
  smoke.add(s01);
  smoke.add(s02);
  if(s01)
  {
    Serial.println("Fire on the dance floor!!");
  }
  if(s02)
  {
    Serial.println("Fire in another dance floor!!");
  }
  delay(1000); // Print value every 1 sec.
  return rackData;
}

void loop()
{
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& rackData = jsonBuffer.createObject();
  JsonArray& smoke = rackData.createNestedArray("smoke");
  JsonObject& smokeData = getSmokeData();
  smoke.add(smokeData["smoke"][0]);
  smoke.add(smokeData["smoke"][1]);
  Serial.println();
  rackData.printTo(Serial);
  Serial.println();
}
