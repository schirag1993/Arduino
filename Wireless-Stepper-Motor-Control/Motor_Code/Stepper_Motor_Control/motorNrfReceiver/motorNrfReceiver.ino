#include <Stepper.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);

const byte rxAddr[6] = "00001"; //address of receiver
int i = 0; //for incrementation

Stepper stepper2(200, 5, 4, 3, 2); //initialize stepper obj
int previous = 0;
void setup()
{
  stepper2.setSpeed(50); //setting speed of motor
  while (!Serial); //waits until serial is opened
  Serial.begin(9600);

  radio.begin(); //activates radio
  radio.openReadingPipe(0, rxAddr);

  radio.startListening(); //waits for data
}

void loop()
{
  if (radio.available()) //checks if radio received anything
  {
    char text[32] = {0};
    radio.read(&text, sizeof(text)); //send the data received to variable text
    int valuex = atoi(text);
    stepper2.step(valuex - previous);
    previous = valuex;
  }
  else
  {
    // put something here to perform operations during zero data transmission
    Serial.println("No data received");
  }
}
