#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include<ArduinoJson.h>

RF24 radio(7, 8);

const byte rxAddr[6] = "00001";

const int elbowFlex = 0;
const int wristFlex = 1;
const int shoulderFlex = 2;

int elbowFlexOld = 0;
int wristFlexOld = 0;
int shoulderFlexOld = 0;

void setup()
{
  // put your setup code here, to run once:
  radio.begin();
  Serial.begin(9600);
  radio.setRetries(15, 15);
  radio.openWritingPipe(rxAddr);
  radio.stopListening();
 // radio.printDetails();

}

void loop()
{
  int wristFlexPos;
  int elbowFlexPos;
  int shoulderFlexPos;

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& flexData = jsonBuffer.createObject();

  int wristFlexNew = analogRead(wristFlex);
  int elbowFlexNew = analogRead(elbowFlex);
  int shoulderFlexNew = analogRead(shoulderFlex);

  int wristServoPos;
  int elbowServoPos;
  int shoulderServoPos;
  if (wristFlexOld >= (wristFlexNew + 15) || wristFlexOld <= (wristFlexNew + 15))
  {
    wristFlexPos = wristFlexNew;
  }
  else
  {
    wristFlexPos = wristFlexOld;
  }
  if (elbowFlexOld >= (elbowFlexNew + 15) || elbowFlexOld <= (elbowFlexNew + 15))
  {
    elbowFlexPos = elbowFlexNew;
  }
  else
  {
    elbowFlexPos = elbowFlexOld;
  }
  if (shoulderFlexOld >= (shoulderFlexNew + 15) || shoulderFlexOld <= (shoulderFlexNew + 15))
  {
    shoulderFlexPos = shoulderFlexNew;
  }
  else
  {
    shoulderFlexPos = shoulderFlexOld;
  }
  Serial.println("Wrist:Elbow:Shoulder"); //max: w:813 769 755; min: w:793 771 753 //795 751 0



  Serial.println(wristFlexPos);
  Serial.println(elbowFlexPos);
  shoulderFlexPos = 0;
  Serial.println(shoulderFlexPos);
  char wrist[8];
  char elbow[8];
  char shoulder[8];
  wristServoPos = map(wristFlexPos, 823,780, 0, 90); //high: 1020 low: 954
  wristServoPos = constrain(wristServoPos, 0, 90);
  elbowServoPos = map(elbowFlexPos, 790, 745, 0, 90);// high: 740 low: 694
  elbowServoPos = constrain(elbowServoPos, 0, 90);
  shoulderServoPos = map(shoulderFlexPos, 768, 744, 0, 90);//high: 1010 low: 905
  shoulderServoPos = constrain(shoulderServoPos, 0, 90);
  itoa(wristServoPos, wrist, 10);
  itoa(elbowServoPos, elbow, 10);
  itoa(shoulderServoPos, shoulder, 10);
  flexData["w"] = wrist;
  flexData["e"] = elbow;
  flexData["s"] = shoulder;
  char flexCombo[128];
  flexData.printTo(flexCombo, sizeof(flexCombo));
  Serial.println("Flex data to be sent is: ");
  
  for (int count = 0; count < strlen(flexCombo); count++)
  {
    Serial.print(flexCombo[count]);
  }
  
  Serial.println();
  radio.write(&flexCombo, sizeof(flexCombo));
  delay(100);
}
