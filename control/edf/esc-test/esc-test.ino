#include "ESC.h"
#include <Servo.h>

Servo myESC;
void setup() {
  myESC.attach(9,1000,2000);
  calib();
  delay(2000);
}
void loop()
{
  myESC.write(150);
  
}
void arm()
{
  myESC.writeMicroseconds(500);
}

void calib()
{
  myESC.attach(9);
  myESC.writeMicroseconds(2000);
  delay(8000);
  myESC.writeMicroseconds(1000);
  delay(8000);
  arm();
}
