#include<ESC.h>

#define SPEED_MIN (1000)                                  // Set the Minimum Speed in microseconds
#define SPEED_MAX (2000)                                  // Set the Minimum Speed in microseconds

ESC e (9, SPEED_MIN, SPEED_MAX, 500);

Servo esc;

void setup()
{
  pinMode(8,OUTPUT);
  e.arm();
  delay(2000);
}

void loop()
{
  digitalWrite(8,HIGH);
//  e.speed(1750);
//  delay(10);
  for (int oESC = SPEED_MIN+500; oESC <= SPEED_MAX; oESC += 5) {  // goes from 1000 microseconds to 2000 microseconds
    e.speed(oESC);                                    // tell ESC to go to the oESC speed value
    delay(10);  }                                          // waits 10ms for the ESC to reach speed
  
}
