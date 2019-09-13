#include <PID_v1.h>  //Left motor header
//--------------- ENCODER PINS/VARIABLES FOR LEFT -----------------//

#define encoderPinLA 2
#define encoderPinLB 4
int PPR = 4920;  // Encoder Pulse per revolution.
int angle = 360; // Maximum degree of motion.
int left_aState;
int left_counter;

//--------------- ENCODER PINS/VARIABLES FOR RIGHT -----------------//

#define encoderPinRinterrupt 1
#define encoderPinRA 3
#define encoderPinRB 7
//int PPR = 4920;  // Encoder Pulse per revolution.
//int angle = 360; // Maximum degree of motion.
int right_aState;
int right_counter;

//---------------- MOTOR PINS/VARIABLES FOR LEFT ------------------//

#define LEnable 5 
#define LDir  17 //Direction pin low moves the bot forward
int User_InputL = 30;  // left Positive angle is down
int REVL = 0;
int linkanglel = 0;

//---------------- MOTOR PINS/VARIABLES FOR RIGHT ------------------//

#define REnable 6
#define RDir  16 //Direction pin low moves the bot forward
int User_InputR = 0;
int REVR = 0;
int linkangler = 0;

//------------------- PID VARIABLES FOR RIGHT----------------------//
double error = 0;
double angleInp = 0; //make it NEGATIVE
double setpointR = 0;
double thetar = 0;
int overshootflagr = 0;
double errord = 0;
double preverror = 0;
double errori = 0;
double controlinput = 0;
double dt = 0;

//JACK PROOF
double kpr = 5.0, kir = 0, kdr = 0 /10000; // modify for optimal performance
double inputr = 0, outputr = 0, setpointr = 0;


//------------------- PID VARIABLES FOR LEFT ----------------------//

//IF THE MOTOR DRIVER HEATS UP, THE MOTORS GO CRAZY
//TO BE FINE TUNED
int i = 45; //Link angles

double kpl = 0.0, kil = 0.000, kdl = 0/10000; // modify for optimal performance
//double kpl = 0.3, kil = 0.000, kdl = 0/10000; // modify for optimal performance
//double kpl = 0.015, kil = 0.000, kdl = 0/10000; // impedance left paramters for springy action
double inputl = 0, outputl = 0, setpointl = 0;
double thetal = 0;
int overshootflagl = 0;

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
  motorSetupL();
  motorSetupR();
  //Serial.begin(9600); //initialize serial comunication
  encoderSetupL();      //Serial communication is messing with the timers and analog pin output
  encoderSetupR();
  

  //--------- Timer setup ----------//
  TCCR1B = TCCR1B & 0b11111000 | 1;
  
  myPIDL.SetMode(AUTOMATIC);          //set PID in Auto mode
  myPIDL.SetSampleTime(1);            //refresh rate of PID controller
  myPIDL.SetOutputLimits(-255, 255);  //this is the MAX PWM value to move motor, here change in value reflect change in speed of motor.
   //--------- Timer setup ----------//
  TCCR1B = TCCR1B & 0b11111000 | 1;
  //analogWrite(REnable,0);
 
}

void loop() 
{

  angleInp = -60;     //right, negative here is downward in bot
  User_InputL = 45;   //left, positive here is downward in bot
  
  REVL = remapl(User_InputL);
  setpointl = REVL;
  inputl = left_counter;
  linkanglel = (left_counter*0.073170732); // To print left link angle if reqd.
  linkanglel = linkanglel%360;
 
  
  myPIDL.Compute();
  pwmOutl(outputl);
  setpointR = angleInp;
  thetar = invRemap(right_counter);
  thetal = invRemap(left_counter);
 /* if (overshootflagl == 1)
  {
    //Serial.println("Left Cutoff");
    finishl();
    delay(100);
  }
  if (overshootflagr == 1)
  {
    //Serial.println("Right Cutoff");
    finishr();
    delay(100);
  }*/
  error = thetar - setpointR;
  errord = (error -preverror);
  errori += (error);
  controlinput = (kpr*error) + (kdr*errord) + (kir*errori);

  
  if(controlinput > 230)
  {
    controlinput = 230;
  }
  else if( controlinput < -230)
  {
    controlinput = -230;
  }
    if(controlinput < 120 && controlinput > 10)
  {
    controlinput = 120;
  }
  else if( controlinput > -120 && controlinput< -10 )
  {
    controlinput = -120;
  }
  if (controlinput>120)
  {
    forwardr();
    analogWrite(REnable,controlinput);
  }
  else if(controlinput < -120)
  {
    reverser();
    analogWrite(REnable,abs(controlinput));
  }
  else 
  {
    finishr();
  }
 
  preverror = error;
}

void motorSetupL()
{
  pinMode(LEnable, OUTPUT);
  pinMode(LDir, OUTPUT); 
}
void motorSetupR()
{
  pinMode(REnable, OUTPUT);
  pinMode(RDir, OUTPUT); 
}

void encoderSetupL()
{
  pinMode(encoderPinLA, INPUT_PULLUP); 
  pinMode(encoderPinLB, INPUT_PULLUP);
  digitalWrite(encoderPinLA, HIGH); //turn pullup resistor on
  digitalWrite(encoderPinLB, HIGH); //turn pullup resistor on
  attachInterrupt(0, updateLEncoder, CHANGE); 
}
void encoderSetupR()
{
  pinMode(encoderPinRA, INPUT_PULLUP); 
  pinMode(encoderPinRB, INPUT_PULLUP);
  digitalWrite(encoderPinRA, HIGH); //turn pullup resistor on
  digitalWrite(encoderPinRB, HIGH); //turn pullup resistor on
  attachInterrupt(encoderPinRinterrupt, updateREncoder, CHANGE); 
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
  if(thetal > 95 )
    overshootflagl = 1;
  else if(thetal < -90 )
    overshootflagl = 1;
  else
    overshootflagl = 0;
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
  if(thetar > 90 )
    overshootflagr = 1;
  else if(thetar < -95 )
    overshootflagr = 1;     
  else
    overshootflagr = 0;
}

void pwmOutl(int controlinput) 
{
  if(controlinput > 230)
  {
    controlinput = 230;
  }
  else if( controlinput < -230)
  {
    controlinput = -230;
  }
  
  if(controlinput < 150 && controlinput >10)
  {
    controlinput = 150;
  }
  else if( controlinput > -150 && controlinput < -10)
  {
    controlinput = -150;
  }
  if (controlinput>=150)
  {
    forwardl();
    analogWrite(LEnable,controlinput);
    //forwardr();
    //analogWrite(REnable,controlinput);

  }
  else if(controlinput <= -150)
  {
    reversel();
    analogWrite(LEnable,abs(controlinput));
    //reverser();
    //analogWrite(REnable,abs(controlinput));
  }
  else 
  {
    finishl();
  }
    //Serial.println(controlinput);
}

void forwardl () 
{
  digitalWrite(LDir, LOW); 
}

void reversel () 
{ 
  digitalWrite(LDir, HIGH); 
}

void finishl () 
{
  digitalWrite(LEnable, LOW);  
}
void forwardr () 
{
  digitalWrite(RDir, LOW); 
}

void reverser () 
{
  digitalWrite(RDir, HIGH); 
}

void finishr () 
{
  digitalWrite(REnable, LOW);  
}

int remapl (int thetal)
{
  int pulsel = floor(13.667 * thetal);
  return pulsel;
}
int remapr (int thetar)
{
  int pulser = floor(13.667 * thetar);
  return pulser;
}
int invRemap(int counter)
{
  int angle = counter*0.073170732;
  linkangler = (angle%360);
  return linkangler;
}
