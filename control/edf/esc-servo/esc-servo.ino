
#include <Servo.h>
Servo ESC;     // create servo object to control the ESC

void setup() {
  // Attach the ESC on pin 9
  ESC.attach(9,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  pinMode(8,OUTPUT);
  digitalWrite(8,HIGH);
}
void loop() 
  {
  ESC.write(150);    // Send the signal to the ESC
  }
