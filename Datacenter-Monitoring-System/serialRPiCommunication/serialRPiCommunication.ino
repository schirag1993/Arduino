void setup()
{
Serial.begin(9600);
Serial3.begin(9600);
Serial.println("Enter 100, 200 or 300");
}

void loop()
{
  if(Serial.available())
  {
    int number = Serial.read();
    Serial3.write(number);
  }
}
