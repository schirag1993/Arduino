// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

int in1 = 10;
int in2 = 9;
int in3 = 8;
int in4 = 7;

int enA = 6;
int enB = 5;

int count = 0;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
}

void loop()
{ // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  float distance = (sonar.ping_cm());
  while ((distance > 5) || (distance == 0))
  {
    analogWrite(enA, 190);
    analogWrite(enB, 190);

    digitalWrite(in1, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in4, HIGH);
    distance = (sonar.ping_cm());
  }

  if (distance <= 5 && distance != 0)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in4, LOW);
    delay(300);
    while (distance <= 5 && distance != 0 )
    {
      analogWrite(enA, 190);
      analogWrite(enB, 190);

      digitalWrite(in1, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in4, HIGH);
      delay(200);
      distance = (sonar.ping_cm());
      count = count + 1;
      if (count >= 5)
      {
        analogWrite(enA, 190);
        analogWrite(enB, 190);
        digitalWrite(in1, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in4, LOW);
        delay(500);
        digitalWrite(in1, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in4, LOW);
      }
    }
  }
}
