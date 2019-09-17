
#include "ESC.h"                                  
#define SPEED_MIN (1000)                                  // Set the Minimum Speed in microseconds
#define SPEED_MAX (2000)                                  // Set the Minimum Speed in microseconds

ESC myESC (9, SPEED_MIN, SPEED_MAX, 500);                 // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Default Speed, Arm Value)
int oESC;                                                 // Variable for the speed sent to the ESC

void setup() 
{
  pinMode(8,OUTPUT);
  digitalWrite(8,HIGH);
  myESC.arm();                                            // Send the Arm value so the ESC will be ready to take commands
  delay(2000);                                            // Wait for a while
}

void loop() 
{
  for (oESC = SPEED_MIN + 500; oESC <= SPEED_MAX; oESC += 1) {  // goes from 1000 microseconds to 2000 microseconds
    myESC.speed(oESC);                                    // tell ESC to go to the oESC speed value
    delay(10);                                            // waits 10ms for the ESC to reach speed
  }
  delay(8000);
  for (oESC = SPEED_MAX; oESC >= SPEED_MIN - 500; oESC -= 1) {  // goes from 2000 microseconds to 1000 microseconds
    myESC.speed(oESC);                                    // tell ESC to go to the oESC speed value
    delay(10);                                            // waits 10ms for the ESC to reach speed  
   }
  delay(5000);                                            // Wait for a while befor restart
}
