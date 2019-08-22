#include <PID_v1.h>

//--------------- ENCODER PINS/VARIABLES -----------------//

#define encoderPinRinterrupt 1
#define encoderPinRA 3
#define encoderPinRB 7
int PPR = 4920;  // Encoder Pulse per revolution.
int angle = 360; // Maximum degree of motion.
int right_aState;
int right_counter;

//---------------- MOTOR PINS/VARIABLES ------------------//

#define REnable 16 //Motor Enamble pin Runs on PWM signal
#define RFwd  14   // Motor Forward pin
#define RRev  15   // Motor Reverse pin
int User_InputR = 0;
int REVR = 0;

//------------------- PID VARIABLES ----------------------//

double kpr = 1.0, kir = 0, kdr = 0 /10000; // modify for optimal performance
double inputr = 0, outputr = 0, setpointr = 0;
PID myPIDR(&inputr, &outputr, &setpointr, kpr, kir, kdr, DIRECT);

//------------------- MODIFIED DYNAMICS CHART ----------------------//
/* ================================================================= /
 *  SPRING 1 => double kpl = 0.35, kil = 0, kdl = 0 /10000;
 *  SPRING 2 => double kpl = 0.65, kil = 0, kdl = 0 /10000;
 *  DAMPER 1 => double kpl = 0.65, kil = 0, kdl = 2 /10000;
 *  DAMPER 2 => double kpl = 0.65, kil = 0, kdl = 6 /10000;
   ================================================================ */
//------------------------------------------------------------------//


void setup() 
{
  motorSetup();
  Serial.begin(9600); //initialize serial comunication
  encoderSetup();

  //--------- Timer setup ----------//
  TCCR1B = TCCR1B & 0b11111000 | 1;
  
  myPIDR.SetMode(AUTOMATIC);          //set PID in Auto mode
  myPIDR.SetSampleTime(1);            //refresh rate of PID controller
  myPIDR.SetOutputLimits(-200, 200);  //this is the MAX PWM value to move motor, here change in value reflect change in speed of motor.
}

void loop() 
{
  User_InputR = 45;
  REVR = remap(User_InputR);
  //Serial.print("REVL: "); 
 // Serial.print(REVL);
  //Serial.print("\t"); 

  setpointr = REVR;
  inputr = right_counter;
 // Serial.print("LC: ");
  Serial.println(inputr);
  
  myPIDR.Compute();
  pwmOutr(outputr);
}

void motorSetup()
{
  pinMode(REnable, OUTPUT);
  pinMode(RFwd, OUTPUT); 
  pinMode(RRev, OUTPUT);
}

void encoderSetup()
{
  pinMode(encoderPinRA, INPUT_PULLUP); 
  pinMode(encoderPinRB, INPUT_PULLUP);
  digitalWrite(encoderPinRA, HIGH); //turn pullup resistor on
  digitalWrite(encoderPinRB, HIGH); //turn pullup resistor on
  attachInterrupt(encoderPinRinterrupt, updateREncoder, CHANGE); 
}

void updateREncoder()
{
  right_aState = digitalRead(encoderPinRA); 
    
     if(digitalRead(encoderPinRB) != right_aState) 
     { 
       right_counter ++;
     } 
     else 
     {
       right_counter --;
     }
}

void pwmOutr(int outr) 
{
  if (outr > 0) 
  {                                   // if REV > encoderValue motor move in forward direction.    
    analogWrite(REnable, outr);       // Enabling motor enable pin to reach the desire angle
    forwardr();                       // calling motor to move forward
  }
  else 
  {
    analogWrite(REnable, abs(outr));  // if REV < encoderValue motor move in forward direction.                      
    reverser();                       // calling motor to move reverse
  }
}

void forwardr () 
{
  digitalWrite(RFwd, HIGH); 
  digitalWrite(RRev, LOW); 
}

void reverser () 
{
  digitalWrite(RFwd, LOW); 
  digitalWrite(RRev, HIGH); 
}

void finishr () 
{
  digitalWrite(RFwd, LOW); 
  digitalWrite(RRev, LOW); 
}

int remap (int theta)
{
  int pulse = floor(13.667 * theta);
  return pulse;
}
