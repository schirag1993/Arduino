#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include<ArduinoJson.h>

RF24 radio(7, 8);

char msgBody[32];
char sensr[5] = "pir";

char off[3] = "N";
char on[3] = "Y";

int ledPin=2;

unsigned long previousMillis = 0; 

bool state=false;

const byte rxAddr[6] = "00001"; //address of receiver

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  radio.begin(); //activates radio
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(0, rxAddr);
  radio.startListening();
}

void loop()
{
  unsigned long currentMillis = millis();
  // put your main code here, to run repeatedly:
  StaticJsonBuffer<200> jsonBuffer;
  if(state)
  {
    digitalWrite(ledPin, HIGH);
  }
  else
  {
    digitalWrite(ledPin, LOW);
  }
  Serial.println("Looking for radio");
  if (radio.available()) //checks if radio received anything
  {
    Serial.println("Radio available");
    radio.read(msgBody, sizeof(msgBody));
    Serial.println(msgBody);
    JsonObject& root = jsonBuffer.parseObject(msgBody);

    // Test if parsing succeeds.
    if (!root.success())
    {
      Serial.println("parseObject() failed");
      return;
    }

    const char* sensor = root["sensr"];
    const char* pirState = root["sig"];
    if (strcmp(sensor, sensr) == 0)
    {
      if (strcmp(pirState, on)==0)
      {
        digitalWrite(ledPin,HIGH);
        Serial.println("LED on");
        state=true;
      }
      if (strcmp(pirState, off)==0)
      {
        digitalWrite(ledPin,LOW);
        Serial.println("led off");
        state=false;
      }
    }
  }
}
