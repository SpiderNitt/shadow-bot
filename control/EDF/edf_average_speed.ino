#include<Servo.h>

Servo esc;

void setup() 
{
  esc.attach(8);
  esc.writeMicroseconds(1000);
  Serial.begin(9600);
}

void loop() 
{
  esc.writeMicroseconds(1500);
}
