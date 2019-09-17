#include<ESC.h>

#define SPEED_MIN (1000)                                  // Set the Minimum Speed in microseconds
#define SPEED_MAX (2000)                                  // Set the Minimum Speed in microseconds

# define interrupt_pin 2

ESC e (9, SPEED_MIN, SPEED_MAX, 500);
int state = 0;

Servo esc;

void setup()
{
  e.arm();
  delay(5000);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin),state_check,CHANGE);
}

void loop()
{
  if(state == 0) e.speed(1000);
  else if(state == 1) e.speed(1200);
  else if(state == 2) e.speed(1400);
  else if(state == 3) e.speed(1600);
  else if(state == 4) e.speed(1800);
  else e.speed(2000);
  delay(5000);
}

void state_check()
{
  state = (state + 1) % 5;
}
