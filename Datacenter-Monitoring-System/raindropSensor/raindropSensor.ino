#include<ArduinoJson.h>

const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;  // sensor maximum

void setup() {
  // initialize serial communication @ 9600 baud:
  Serial.begin(9600);
}

int getExternalWaterLevel()
{
  int sensorReading = analogRead(A0);
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3); //0 is overflow; 1 is wet; 2 is dry
  Serial.println();
  // range value:
  switch (range) {
    case 0:    // Sensor getting wet
      Serial.println("Flood");
      break;
    case 1:    // Sensor getting wet
      Serial.println("Rain Warning");
      break;
    case 2:
      Serial.println("Not Raining");
      break;
  }
    return range;
}

void loop() {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& externalWaterLevelData = jsonBuffer.createObject();
  externalWaterLevelData["externalWaterLevel"] = getExternalWaterLevel();
  Serial.println();
  externalWaterLevelData.printTo(Serial);
  Serial.println();
  delay(1000);  // delay between reads
}
