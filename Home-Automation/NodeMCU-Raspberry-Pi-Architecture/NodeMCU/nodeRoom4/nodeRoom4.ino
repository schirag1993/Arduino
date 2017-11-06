#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// Update these with values suitable for your network.

const char* ssid = "CloudThat_IoT_Lab2_2.4GHz";
const char* password = "ghjklasdf1*&";
const char* mqtt_server = "192.168.10.110";

int relayPin[4] = {D0, D1, D2, D3};
int arduinoInterrupt = D4;

String thing01 = "light01";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {

  Serial.begin(115200);
  setup_wifi();
  pinMode(relayPin[0], OUTPUT);
  pinMode(relayPin[1], OUTPUT);
  pinMode(relayPin[2], OUTPUT);
  pinMode(relayPin[3], OUTPUT);
  pinMode(arduinoInterrupt, OUTPUT);
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  char message[length];
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    char var = (char)payload[i];
    message[i] = var;
  }
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& mqttMsg = jsonBuffer.parseObject(message);
  Serial.println("Parsed payload is ");
  mqttMsg.printTo(Serial);
  controlFunc(mqttMsg);
  Serial.println();
}

void controlFunc(JsonObject& mqttMsg)
{
  Serial.println();
  Serial.println("Inside control func, recieved: ");
  mqttMsg.printTo(Serial);
  JsonObject& queueData = mqttMsg;
  String thingName = queueData["thingId"];
  int thingValue = queueData["thingState"];
  Serial.println();
  Serial.println("Thing name is ");
  Serial.println(thingName);
  Serial.println("thing value is ");
  Serial.println(thingValue);
  if (thingName == thing01)
  {
    Serial.println("Inside light01");
    digitalWrite(relayPin[0], thingValue);
  }
  else
  {
    Serial.println("Inside else");
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("Node04", "root", "root")) {
      Serial.println("connected to node04");
      client.subscribe("node04..");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
