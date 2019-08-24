#include <PID_v1.h>

//--------------- ENCODER PINS/VARIABLES -----------------//

#define encoderPinLA 2
#define encoderPinLB 4
int PPR = 4920;  // Encoder Pulse per revolution.
int angle = 360; // Maximum degree of motion.
int left_aState;
int left_counter;

//---------------- MOTOR PINS/VARIABLES ------------------//

#define LEnable 17 //Motor Enamble pin Runs on PWM signal
#define LFwd  19  // Motor Forward pin
#define LRev  18 // Motor Reverse pin
int User_InputL = 0;
int REVL = 0;

//------------------- PID VARIABLES ----------------------//

double kpl = 20, kil = 0, kdl = 10 /10000; // modify for optimal performance
double inputl = 0, outputl = 0, setpointl = 0;
PID myPIDL(&inputl, &outputl, &setpointl, kpl, kil, kdl, DIRECT);

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
  
  myPIDL.SetMode(AUTOMATIC);          //set PID in Auto mode
  myPIDL.SetSampleTime(1);            //refresh rate of PID controller
  myPIDL.SetOutputLimits(-200, 200);  //this is the MAX PWM value to move motor, here change in value reflect change in speed of motor.
}

void loop() 
{
  User_InputL = 0;
  REVL = remap(User_InputL);
  //Serial.print("REVL: "); 
 // Serial.print(REVL);
  //Serial.print("\t"); 

  setpointl = REVL;
  inputl = left_counter;
 // Serial.print("LC: ");
  Serial.println(inputl);
  
  myPIDL.Compute();
  pwmOutl(outputl);
}

void motorSetup()
{
  pinMode(LEnable, OUTPUT);
  pinMode(LFwd, OUTPUT); 
  pinMode(LRev, OUTPUT);
}

void encoderSetup()
{
  pinMode(encoderPinLA, INPUT_PULLUP); 
  pinMode(encoderPinLB, INPUT_PULLUP);
  digitalWrite(encoderPinLA, HIGH); //turn pullup resistor on
  digitalWrite(encoderPinLB, HIGH); //turn pullup resistor on
  attachInterrupt(0, updateLEncoder, CHANGE); 
}

void updateLEncoder()
{
  left_aState = digitalRead(encoderPinLA); 
    
     if(digitalRead(encoderPinLB) != left_aState) 
     { 
       left_counter ++;
     } 
     else 
     {
       left_counter --;
     }
}

void pwmOutl(int outl) 
{
  if (outl > 0) 
  {                                   // if REV > encoderValue motor move in forward direction.    
    analogWrite(LEnable, outl);       // Enabling motor enable pin to reach the desire angle
    forwardl();                       // calling motor to move forward
  }
  else 
  {
    analogWrite(LEnable, abs(outl));  // if REV < encoderValue motor move in forward direction.                      
    reversel();                       // calling motor to move reverse
  }
}

void forwardl () 
{
  digitalWrite(LFwd, HIGH); 
  digitalWrite(LRev, LOW); 
}

void reversel () 
{
  digitalWrite(LFwd, LOW); 
  digitalWrite(LRev, HIGH); 
}

void finishl () 
{
  digitalWrite(LFwd, LOW); 
  digitalWrite(LRev, LOW); 
}

int remap (int theta)
{
  int pulse = floor(13.667 * theta);
  return pulse;
}
