#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include<ArduinoJson.h>

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

void setup() {
  Serial.begin(9600);
  dht1.begin();
  dht2.begin();
  dht3.begin();
  dht4.begin();
  dht5.begin();
  sensor_t sensor;
  dht1.temperature().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Temperature");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" *C");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" *C");
  Serial.println("------------------------------------");
  // Print humidity sensor details.
  dht1.humidity().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Humidity");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println("%");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println("%");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println("%");
  Serial.println("------------------------------------");
  dht2.temperature().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Temperature");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" *C");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" *C");
  Serial.println("------------------------------------");
  // Print humidity sensor details.
  dht2.humidity().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Humidity");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println("%");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println("%");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println("%");
  Serial.println("------------------------------------");
  dht3.temperature().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Temperature");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" *C");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" *C");
  Serial.println("------------------------------------");
  // Print humidity sensor details.
  dht3.humidity().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Humidity");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println("%");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println("%");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println("%");
  Serial.println("------------------------------------");
  dht4.temperature().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Temperature");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" *C");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" *C");
  Serial.println("------------------------------------");
  // Print humidity sensor details.
  dht4.humidity().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Humidity");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println("%");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println("%");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println("%");
  Serial.println("------------------------------------");
  dht5.temperature().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Temperature");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" *C");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" *C");
  Serial.println("------------------------------------");
  // Print humidity sensor details.
  dht5.humidity().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Humidity");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println("%");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println("%");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println("%");
  Serial.println("------------------------------------");
}

JsonObject& getTempAndHumidity()
{
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& rackData = jsonBuffer.createObject();
  JsonArray& tempr = rackData.createNestedArray("temp");
  JsonArray& hum = rackData.createNestedArray("hum");
  // Delay between measurements.
  delay(1500);
  sensors_event_t event[6];

  Serial.println("DHT11 #1");
  dht1.temperature().getEvent(&event[0]);
  if (isnan(event[0].temperature)) {
    Serial.println("Error reading temperature!");
    tempr.add("NAN");
  }
  else {
    Serial.println(event[0].temperature);
    tempr.add(event[0].temperature);
  }
  // Get humidity event and print its value.
  dht1.humidity().getEvent(&event[0]);
  if (isnan(event[0].relative_humidity)) {
    Serial.println("Error reading humidity!");
    hum.add("NAN");
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
    tempr.add("NAN");
  }
  else {
    Serial.println(event[1].temperature);
    tempr.add(event[1].temperature);
  }
  // Get humidity event and print its value.
  dht2.humidity().getEvent(&event[1]);
  if (isnan(event[1].relative_humidity)) {
    Serial.println("Error reading humidity!");
    hum.add("NAN");
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
    tempr.add("NAN");
  }
  else {
    Serial.println(event[2].temperature);
    tempr.add(event[2].temperature);
  }
  // Get humidity event and print its value.
  dht3.humidity().getEvent(&event[2]);
  if (isnan(event[2].relative_humidity)) {
    Serial.println("Error reading humidity!");
    hum["02"] = "NAN";
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
    tempr.add("NAN");
  }
  else {
    Serial.println(event[3].temperature);
    tempr.add(event[3].temperature);
  }
  // Get humidity event and print its value.
  dht4.humidity().getEvent(&event[3]);
  if (isnan(event[3].relative_humidity)) {
    Serial.println("Error reading humidity!");
    hum.add("NAN");
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
    tempr.add("NAN");
  }
  else {
    Serial.println(event[4].temperature);
    tempr.add(event[4].temperature);
  }
  // Get humidity event and print its value.
  dht5.humidity().getEvent(&event[4]);
  if (isnan(event[4].relative_humidity)) {
    Serial.println("Error reading humidity!");
    hum.add("NAN");
  }
  else {
    Serial.print("Humidity: ");
    Serial.print(event[4].relative_humidity);
    Serial.println("%");
    hum.add(event[4].relative_humidity);
  }
  Serial.println("||||||||||||||||");
  rackData.printTo(Serial);
  char msg[128];
  rackData.printTo(msg, sizeof(msg));
  Serial.println();
  Serial.println("||||||||||||||||");
  return rackData;
}

void loop() {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& rackData = jsonBuffer.createObject();
  JsonArray& dht11 = rackData.createNestedArray("dht11");
  JsonObject& tempAndHumResult = getTempAndHumidity();
  Serial.println();
  Serial.println("The message returned from function is ");
  dht11.add(tempAndHumResult);
  Serial.println();
  Serial.println("The completed string in JSON is ");
  Serial.println();
  rackData.printTo(Serial);
  Serial.println();
}
