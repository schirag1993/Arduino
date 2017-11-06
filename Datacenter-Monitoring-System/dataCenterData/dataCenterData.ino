#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include<ArduinoJson.h>

int rackID = 0;

#define DHTPIN1            2         // Pin which is connected to the DHT sensor.
#define DHTPIN2            3
#define DHTPIN3            4
#define DHTPIN4            5
#define DHTPIN5            6

// Uncomment the type of sensor in use:
#define DHTTYPE           DHT11

DHT_Unified dht1(DHTPIN1, DHTTYPE);
DHT_Unified dht2(DHTPIN2, DHTTYPE);
DHT_Unified dht3(DHTPIN3, DHTTYPE);
DHT_Unified dht4(DHTPIN4, DHTTYPE);
DHT_Unified dht5(DHTPIN5, DHTTYPE);

const int gasPin1 = 7;
const int gasPin2 = 8;
int s01 = 0;
int s02 = 0;

const int externalWaterLevelSensor = A7;
int value;

const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;

void setup()
{
  Serial1.begin(115200);
  dht1.begin();
  dht2.begin();
  dht3.begin();
  dht4.begin();
  dht5.begin();
  sensor_t sensor;

}

int getExternalWaterLevel()
{
  // read the sensor on analog A0:
  int sensorReading = analogRead(A0);

  // map the sensor range (four options):
  // ex: 'long int map(long int, long int, long int, long int, long int)'
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
  if (s01)
  {
    Serial.println("Fire on the dance floor!!");
  }
  if (s02)
  {
    Serial.println("Fire in another dance floor!!");
  }
  delay(1000); // Print value every 1 sec.
  return rackData;
}

int rackWaterLevel()
{
  value = analogRead(externalWaterLevelSensor);
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
  return currentWaterLevel;
}

JsonObject& getDHT11Data()
{
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& dht11Data = jsonBuffer.createObject();
  JsonArray& tempr = dht11Data.createNestedArray("temp");
  JsonArray& hum = dht11Data.createNestedArray("hum");
  // Delay between measurements.
  delay(1500);
  sensors_event_t event[6];

  Serial.println("DHT11 #1");
  dht1.temperature().getEvent(&event[0]);
  if (isnan(event[0].temperature)) {
    Serial.println("Error reading temperature!");
    tempr.add(999);
  }
  else {
    Serial.println(event[0].temperature);
    tempr.add(event[0].temperature);
  }
  // Get humidity event and print its value.
  dht1.humidity().getEvent(&event[0]);
  if (isnan(event[0].relative_humidity)) {
    Serial.println("Error reading humidity!");
    hum.add(999);
  }
  else {
    Serial.print("Humidity: ");
    Serial.print(event[0].relative_humidity);
    Serial.println("%");
    hum.add(event[0].relative_humidity);
  }

  Serial.println("DHT11 #2");
  dht2.temperature().getEvent(&event[1]);
  if (isnan(event[1].temperature)) {
    Serial.println("Error reading temperature!");
    tempr.add(999);
  }
  else {
    Serial.println(event[1].temperature);
    tempr.add(event[1].temperature);
  }
  // Get humidity event and print its value.
  dht2.humidity().getEvent(&event[1]);
  if (isnan(event[1].relative_humidity)) {
    Serial.println("Error reading humidity!");
    hum.add(999);
  }
  else {
    Serial.print("Humidity: ");
    Serial.print(event[1].relative_humidity);
    Serial.println("%");
    hum.add(event[1].relative_humidity);
  }

  Serial.println("DHT11 #3");
  dht3.temperature().getEvent(&event[2]);
  if (isnan(event[2].temperature)) {
    Serial.println("Error reading temperature!");
    tempr.add(999);
  }
  else {
    Serial.println(event[2].temperature);
    tempr.add(event[2].temperature);
  }
  // Get humidity event and print its value.
  dht3.humidity().getEvent(&event[2]);
  if (isnan(event[2].relative_humidity)) {
    Serial.println("Error reading humidity!");
    hum.add(999);
  }
  else {
    Serial.print("Humidity: ");
    Serial.print(event[2].relative_humidity);
    Serial.println("%");
    hum.add(event[2].relative_humidity);
  }

  Serial.println("DHT11 #4");
  dht4.temperature().getEvent(&event[3]);
  if (isnan(event[3].temperature)) {
    Serial.println("Error reading temperature!");
    tempr.add(999);
  }
  else {
    Serial.println(event[3].temperature);
    tempr.add(event[3].temperature);
  }
  // Get humidity event and print its value.
  dht4.humidity().getEvent(&event[3]);
  if (isnan(event[3].relative_humidity)) {
    Serial.println("Error reading humidity!");
    hum.add(999);
  }
  else {
    Serial.print("Humidity: ");
    Serial.print(event[3].relative_humidity);
    Serial.println("%");
    hum.add(event[3].relative_humidity);
  }

  Serial.println("DHT11 #5");
  dht5.temperature().getEvent(&event[4]);
  if (isnan(event[4].temperature)) {
    Serial.println("Error reading temperature!");
    tempr.add(999);
  }
  else {
    Serial.println(event[4].temperature);
    tempr.add(event[4].temperature);
  }
  // Get humidity event and print its value.
  dht5.humidity().getEvent(&event[4]);
  if (isnan(event[4].relative_humidity)) {
    Serial.println("Error reading humidity!");
    hum.add(999);
  }
  else {
    Serial.print("Humidity: ");
    Serial.print(event[4].relative_humidity);
    Serial.println("%");
    hum.add(event[4].relative_humidity);
  }
  return dht11Data;
}

void loop()
{
  StaticJsonBuffer<400> jsonBuffer;
  JsonObject& rackData = jsonBuffer.createObject();

  int rackLevelWater = rackWaterLevel();
  rackData["rackWaterLevel"] = rackLevelWater;

  JsonObject& tempAndHumResult = getDHT11Data();
  rackData["Temp"] = tempAndHumResult["temp"];
  rackData["Hum"] = tempAndHumResult["hum"];


  JsonArray& smokeLevel = rackData.createNestedArray("smokeLevel");
  JsonObject& smokeData = getSmokeData();
  smokeLevel.add(smokeData["smoke"][0]);
  smokeLevel.add(smokeData["smoke"][1]);

  int externalWaterLevel = getExternalWaterLevel();
  rackData["externalWaterLevel"] = externalWaterLevel;

  Serial.println("||||");
  rackData.printTo(Serial);
  Serial.println();
  Serial.println("||||");
  unsigned char msg[2048];
  Serial.println("Sending data to Raspberry. msgToRaspberry is: ");
  rackData.printTo(Serial1);
  delay(5000);
  }
