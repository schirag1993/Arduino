#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(D7, D8);

const char* ssid = "Gxrrma8MjXdrYOMp";   // WiFi SSID
const char* password = "ghjklasdf1=/";            // WiFi Password
String azure_mqtt_server = "azure-devices.net";   // Azure IoT Hub URL
String IoTHub = "ChiragTestHub";               // IoTHub Name
String device_id = "nodeMCU";        // Device ID
String deviceSAS = "SharedAccessSignature sr=CtHub.azure-devices.net%2Fdevices%2FnodeMCU&sig=Nraza6NXjME4e4H8ZAcldQ4hc3d3xonpA%3D&se=1525875060";

String inTopic = "devices/" + device_id + "/messages/devicebound/#";
String outTopic = "devices/" + device_id + "/messages/events/";
String qualifiedHubName = IoTHub + "." + azure_mqtt_server;
const char* mqtt_server = qualifiedHubName.c_str();
String hubUsername = IoTHub + "." + azure_mqtt_server + "/" + device_id;
const char* hubuser = hubUsername.c_str();
const char* hubpass = deviceSAS.c_str();

const int signalPin = D4;

WiFiClientSecure espClient;
PubSubClient client(espClient);

void setup_wifi() {

  delay(10); // We start by connecting to a WiFi network Serial.println();
  Serial.print("Connecting to "); Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IPaddress: "); Serial.println(WiFi.localIP());
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  char message[length];
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    char var = (char)payload[i];
    message[i] = var;
  }
  Serial.println("Message is ");
  Serial.println(message);
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& mqttMsg = jsonBuffer.parseObject(message);
  //int command;
  //command = atoi(message);
  Serial.println("Parsed payload is ");
  mqttMsg.printTo(Serial);
  controlFunc(mqttMsg);
 // roomControl(command);
}

void controlFunc(JsonObject& mqttMsg)
{
  Serial.println();
  Serial.println("Inside control func, recieved: ");
  mqttMsg.printTo(Serial);
  mqttMsg.printTo(mySerial);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    if (client.connect(device_id.c_str(), hubuser, hubpass)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(outTopic.c_str(), "hello world");
      // ... and resubscribe
      client.subscribe(inTopic.c_str());
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void roomControl(int command)
{
  Serial.println("Inside room control");
  Serial.println("Command value is ");
  Serial.println(command);
  int control = command;
  switch (control)
  {
    case 0:
    Serial.println("case 0");
      allLightsOff();
      break;

    case 1:
    Serial.println("Case 1");
      allLightsOn();
      break;

    case 2:
    Serial.println("Case 2");
      cabinOneOn();
      break;

    case 3:
    Serial.println("case 3");
      cabinOneOff();
      break;
      /*
          case 0100:
            cabinTwoOn();
            break;

          case 0101:
            cabinTwoOff();
            break;

          case 0110:
            cabinThreeOn();
            break;

          case 1000:
            cabinThreeOff();
            break;
      */
  }
}

void allLightsOn()
{
  Serial.println("Inside all lights on");
  int value = 1;
  sendSignal(value);
}

void allLightsOff()
{
  sendSignal(0);
}

void cabinOneOn()
{
  sendSignal(2);
}

void cabinOneOff()
{
  sendSignal(3);
}

void sendSignal(int value)
{
  int commandValue = value;
  Serial.println("value is ");
  Serial.println(value);
  Serial.println("data received is ");
  Serial.println(commandValue);
  Serial.println("Writing to Serial");
  Serial.println("Writing: ");
  Serial.println(commandValue);
  mySerial.write(commandValue);
  Serial.println("Success");
}

void setup(void)
{
  pinMode(signalPin, OUTPUT);
  Serial.begin(115200);
  mySerial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 8883);
  client.setCallback(callback);
}

void loop(void)
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

