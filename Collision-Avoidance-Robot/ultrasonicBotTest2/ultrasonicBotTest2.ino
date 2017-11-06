// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

int in1 = 10;
int in2 = 9;
int in3 = 6;
int in4 = 5;

int motorSpeed = 170;

int count = 0;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup()
{
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop()
{
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  float distance = (sonar.ping_cm());
  while ((distance > 8) || (distance == 0))
  {
    analogWrite(in4, motorSpeed); //right forward
    analogWrite(in3, LOW); //right backward

    analogWrite(in2, motorSpeed); //left forward
    analogWrite(in1, LOW); //left backward
    distance = (sonar.ping_cm());
    Serial.println("Moving forward, distance is ");
    Serial.println(distance);
  }

  if (distance < 8 && distance != 0)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in4, LOW);
    Serial.println(" Obstacle detected, stopping");
    delay(300);
    while (distance <= 8 && distance != 0 )
    {
      Serial.println("Changing direction now");
      analogWrite(in4, motorSpeed); //right forward
      analogWrite(in3, LOW); //right backward
      analogWrite(in2, LOW); //left forward
      analogWrite(in1, motorSpeed); //left backward
      delay(180);
      distance = (sonar.ping_cm());
      digitalWrite(in1, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in4, LOW);
      delay(190);
      count = count + 1;
      if (count >= 5)
      {
        Serial.println("Reversing");
        analogWrite(in4, LOW); //right forward
        analogWrite(in3, motorSpeed); //right backward

        analogWrite(in2, LOW); //left forward
        analogWrite(in1, motorSpeed); //left backward
        delay(500);
        Serial.println("Stopped reverse");
        digitalWrite(in1, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in4, LOW);
      }
    }
  }
}
