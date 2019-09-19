
#include <Servo.h> //Use the Servo librarey for generating PWM
Servo ESC; //name the servo object, here ESC

void setup()
{
  ESC.attach(9); //Generate PWM in pin 9 of Arduino
  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(14,INPUT);
  pinMode(8,OUTPUT);
  digitalWrite(4,LOW);
  digitalWrite(2,HIGH);
  digitalWrite(8,HIGH);
//  Serial.begin(9600);
}

void loop()
{
int throttle = analogRead(14); //Read the voltage from POT
//Serial.println(throttle);
throttle = map(throttle, 0, 1023, 0, 180); //Map the values of 0-102 from pot to 0-180 bcs servo works only from 0-180
//Serial.println(throttle);
if(millis()<40000)
ESC.write(throttle); //based on the value of throttle generate PWM signal
else
ESC.write(180);
}
