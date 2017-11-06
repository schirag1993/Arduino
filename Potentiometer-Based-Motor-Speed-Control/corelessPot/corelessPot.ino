int sensorPin = A0;

int sensorValue = 0;

int outputValue = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(sensorPin)/4;
  Serial.println(sensorValue);
  outputValue = map(sensorValue, 0, 255, 0, 255);
  Serial.println(outputValue);
  analogWrite(3, sensorValue);
}
