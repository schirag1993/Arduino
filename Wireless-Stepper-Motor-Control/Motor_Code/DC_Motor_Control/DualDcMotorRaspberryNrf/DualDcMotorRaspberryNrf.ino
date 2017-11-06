#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include<ArduinoJson.h>

RF24 radio(9, 10);
const uint64_t pipes[2] = { 0xABCDABCD71LL, 0x544d52687CLL };

int result = 0;

int motorPinA1 = 2;
int motorPinA2 = 3;
int motorPinB1 = 5;
int motorPinB2 = 4;

char forward[4] = "F";
char right[4] = "R";
char left[4] = "L";
char halt[4] = "H";
char rotateHalt[4] = "H";
char head_right[4] = "HR";
char head_left[4] = "HL";
char head_halt[4] = "HH";

char msgBody[54];
char previousXaxis[2] = {0};
char previousYaxis[2] = {0};

void setup()
{
  // put your setup code here, to run once:
  while (!Serial); //waits until serial is opened
  Serial.begin(9600);

  radio.begin();
  radio.setChannel(0x4c);
  radio.setAutoAck(1);
  radio.setRetries(15, 15);
  radio.setDataRate(RF24_1MBPS);
  radio.setPayloadSize(32);                // Here we are sending 1-byte payloads to test the call-response speed
  radio.openReadingPipe(1, pipes[1]);
  radio.startListening();                 // Start listening
  radio.printDetails();
}

void loop()
{
  StaticJsonBuffer<200> jsonBuffer;
  Serial.println("Looking for radio");
  if (radio.available()) //checks if radio received anything
  {
    Serial.println("Radio available");
    radio.read(&msgBody, sizeof(msgBody));
    Serial.println("The string is ");
    Serial.println(msgBody);
    Serial.println("End of string");
    Serial.println();
    JsonObject& root = jsonBuffer.parseObject(msgBody);

    // Test if parsing succeeds.
    if (!root.success())
    {
      Serial.println("parseObject() failed");
      return;
    }

    const char* sensor = root["sensr"];
    const char* xaxis = root["x"];
    const char* yaxis = root["y"];

    Serial.println("The decoded values are: ");
    Serial.print("Sensor: ");
    Serial.println(sensor);
    Serial.print("X-Axis: ");
    Serial.println(xaxis);
    Serial.print("Y-Axis: ");
    Serial.println(yaxis);

    if (strcmp(previousXaxis, xaxis) == 0 && strcmp(previousYaxis, yaxis) == 0)
    {
      Serial.println("No NEW movement information detected");
    }
    else
    {
      if (strcmp(yaxis, forward) == 0)
      {
        Serial.println("Moving forward");
        digitalWrite(motorPinA1, HIGH); //FORWARD MARCH
        digitalWrite(motorPinA2, LOW);
        digitalWrite(motorPinB2, HIGH);
        digitalWrite(motorPinB1, LOW);
      }
      if (strcmp(xaxis, left) == 0)
      {
        Serial.println("Turning left");
        digitalWrite(motorPinA1, HIGH); //ABOUT LEFT
        digitalWrite(motorPinA2, LOW);
        digitalWrite(motorPinB2, LOW);
        digitalWrite(motorPinB1, HIGH);
      }
      if (strcmp(yaxis, halt) == 0 && strcmp(xaxis, rotateHalt) == 0)
      {
        Serial.println("Stopping");
        digitalWrite(motorPinA1, LOW); //COMPANY HALT
        digitalWrite(motorPinA2, LOW);
        digitalWrite(motorPinB2, LOW);
        digitalWrite(motorPinB1, LOW);
        Serial.println("Stopped!");
      }
      if (strcmp(xaxis, right) == 0)
      {
        Serial.println("Turning right");
        digitalWrite(motorPinA1, LOW); //ABOUT RIGHT
        digitalWrite(motorPinA2, HIGH);
        digitalWrite(motorPinB2, HIGH);
        digitalWrite(motorPinB1, LOW);
      }
      strcpy(previousYaxis, yaxis); //pass text's value to variable named previous
      strcpy(previousXaxis, xaxis);

      delay(3000);

      jsonBuffer = StaticJsonBuffer<200>();

    }
  }
}
