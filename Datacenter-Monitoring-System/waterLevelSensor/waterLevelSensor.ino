#include<ArduinoJson.h>

const int waterLevelSensor = A7;
int value;

void setup()
{
  //Begin serial communication
  Serial.begin(9600);

}

int rackWaterLevel()
{
  value = analogRead(waterLevelSensor); //Read data from analog pin and store it to value variable
  int currentWaterLevel = 0;
  if (value <= 480) {
    Serial.println("Water level: 0mm - Empty!");
    currentWaterLevel = 0;
  }
  else if (value > 480 && value <= 530) {
    Serial.println("Water level: 0mm to 5mm");
    currentWaterLevel = 5;
  }
  else if (value > 530 && value <= 615) {
    Serial.println("Water level: 5mm to 10mm");
    currentWaterLevel = 10;
  }
  else if (value > 615 && value <= 660) {
    Serial.println("Water level: 10mm to 15mm");
    currentWaterLevel = 15;
  }
  else if (value > 660 && value <= 680) {
    Serial.println("Water level: 15mm to 20mm");
    currentWaterLevel = 20;
  }
  else if (value > 680 && value <= 690) {
    Serial.println("Water level: 20mm to 25mm");
    currentWaterLevel = 25;
  }
  else if (value > 690 && value <= 700) {
    Serial.println("Water level: 25mm to 30mm");
    currentWaterLevel = 30;
  }
  else if (value > 700 && value <= 705) {
    Serial.println("Water level: 30mm to 35mm");
    currentWaterLevel = 35;
  }
  else if (value > 705) {
    Serial.println("Water level: 35mm to 40mm");
    currentWaterLevel = 40;
  }
  Serial.println();
  delay(1000); // Check for new value every 5 sec
  return currentWaterLevel;
}

void loop()
{
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& rackData = jsonBuffer.createObject();
  JsonArray& rckWL = rackData.createNestedArray("rckWL");
  int rackLevelWater = rackWaterLevel();
  rckWL.add(rackLevelWater);
  rackData.printTo(Serial);
  Serial.println();
}

