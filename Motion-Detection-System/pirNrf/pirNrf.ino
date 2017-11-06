#include <SPI.h>
#include <nRF24L01.h>
#include<ArduinoJson.h>
#include <RF24.h> //try using nrf mirf lib instead

RF24 radio(7, 8); //radio digital ports on Arduino

const byte rxAddr[6] = "00001";

int calibrationTime = 20;

//the time when the sensor outputs a low impulse
long unsigned int lowIn;

//the amount of milliseconds the sensor has to be low
//before we assume all motion has stopped
long unsigned int pause = 5000;

boolean lockLow = true;
boolean takeLowTime;

int pirPin = 3;

char motion[4];

//SETUP
void setup()
{
  radio.begin();
  radio.setRetries(15, 15);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(rxAddr);
  radio.stopListening();
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  digitalWrite(pirPin, LOW);

  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
  for (int i = 0; i < calibrationTime; i++)
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("done");
  Serial.println("SENSOR IS ONLINE");
  delay(50);
}

////////////////////////////
//LOOP
void loop()
{
  StaticJsonBuffer<200> jsonBuffer;
  Serial.println("Generating JSON string");
  JsonObject& pirData = jsonBuffer.createObject();
  char pirSignal[128];
  pirData["sensr"] = "pir";

  if (digitalRead(pirPin) == HIGH)
  {
    strcpy(motion, "on");
    pirData["sig"] = "Y";
    pirData.printTo(pirSignal, sizeof(pirSignal));
    Serial.print("Sending the following string: ");
    Serial.println(pirSignal);
    radio.write(&pirSignal, sizeof(pirSignal));
    Serial.println("Data sent");
    delay(100);

    if (lockLow)
    {
      //makes sure we wait for a transition to LOW before any further output is made:
      lockLow = false;
      Serial.println("---");
      Serial.print("motion detected at ");
      Serial.print(millis() / 1000);
      Serial.println(" sec");
      delay(50);
    }
    takeLowTime = true;
  }
  if (digitalRead(pirPin) == LOW)
  {
    strcpy(motion, "off");
    pirData["sig"] = "N";
    pirData.printTo(pirSignal, sizeof(pirSignal));
    Serial.print("Sending the following string: ");
    Serial.println(pirSignal);
    radio.write(&pirSignal, sizeof(pirSignal));
    Serial.println("Data sent");
    delay(100);

    if (takeLowTime)
    {
      lowIn = millis();          //save the time of the transition from high to LOW
      takeLowTime = false;       //make sure this is only done at the start of a LOW phase
    }
    //if the sensor is low for more than the given pause,
    //we assume that no more motion is going to happen
    if (!lockLow && millis() - lowIn > pause)
    {
      //makes sure this block of code is only executed again after
      //a new motion sequence has been detected
      lockLow = true;
      Serial.print("motion ended at ");      //output
      Serial.print((millis() - pause) / 1000);
      Serial.println(" sec");
      delay(50);
    }
  }
}
