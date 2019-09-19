#include<Servo.h>
                   
#define SPEED_MIN (1000)          // Set the Minimum Speed in microseconds
#define SPEED_MAX (2000)          // Set the Minimum Speed in microseconds
#define armValue (500)

Servo e;


void setup() 
{
  pinMode(8, OUTPUT);   
  calib(); // Send the Arm value so the ESC will be ready to take commands
  digitalWrite(8, HIGH);                                            // Wait for a while
}

void loop() 
{
  e.writeMicroseconds(1750);                                           // Wait for a while befor restart
}

void arm()
{
  e.writeMicroseconds(armValue);
}

void stop()
{
  e.writeMicroseconds(500);
}

void calib()
{
  e.attach(9);
  e.writeMicroseconds(SPEED_MAX);
  delay(8000);
  e.writeMicroseconds(SPEED_MIN);
  delay(8000);
  arm();
}
