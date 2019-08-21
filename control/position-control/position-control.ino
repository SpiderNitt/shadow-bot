#include <PID_v1.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(14,15);// 

#define LEnable 10 //Motor Enamble pin Runs on PWM signal
#define LFwd  11  // Motor Forward pin
#define LRev  12 // Motor Reverse pin
#define REnable 9
#define RRev 4  //find out fwd and rev pins
#define RFwd 5
#define encoderPinLA 2
#define encoderPinLB 6
#define encoderPinRA 3
#define encoderPinRB 7
                      
//String readString; //This while store the user input data
int User_InputL = 0; // This while convert input string into integer
int User_InputR = 0;

int right_aState;
int right_counter;
int left_aState;
int left_counter;
int PPR = 4920;  // Encoder Pulse per revolution.
int angle = 360; // Maximum degree of motion.
int REVL = 0;          // Set point REQUIRED ENCODER VALUE
int REVR = 0;

// kp = 0.22, ki = 0.09, kd = 0;L

 
double kpl = 0.25, kil = 0, kdl = 0;// modify for optimal performance
double kpr = 0.25, kir = 0, kdr = 0;
double inputl = 0, outputl = 0, setpointl = 0;
double inputr = 0, outputr = 0, setpointr = 0;
int ch = 0;

PID myPIDL(&inputl, &outputl, &setpointl, kpl, kil, kdl, DIRECT);
PID myPIDR(&inputr, &outputr, &setpointr, kpr, kir, kdr, DIRECT); 




void setup() {
  pinMode(LEnable, OUTPUT);
  pinMode(LFwd, OUTPUT); 
  pinMode(LRev, OUTPUT);
  pinMode(REnable, OUTPUT);
  pinMode(RFwd, OUTPUT); 
  pinMode(RRev, OUTPUT); 
  Serial.begin(9600); //initialize serial comunication
  Serial.flush();
  
   pinMode(encoderPinLA, INPUT_PULLUP); 
  pinMode(encoderPinLB, INPUT_PULLUP);
  
   pinMode(encoderPinRA, INPUT_PULLUP); 
  pinMode(encoderPinRB, INPUT_PULLUP);

  digitalWrite(encoderPinLA, HIGH); //turn pullup resistor on
  digitalWrite(encoderPinLB, HIGH); //turn pullup resistor on
  digitalWrite(encoderPinRA, HIGH); //turn pullup resistor on
  digitalWrite(encoderPinRB, HIGH); //turn pullup resistor on

  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, updateLEncoder, CHANGE); 
  attachInterrupt(1, updateREncoder, CHANGE);

  TCCR1B = TCCR1B & B11111000 | B00000001;
  myPIDL.SetMode(AUTOMATIC);   //set PID in Auto mode
  myPIDL.SetSampleTime(1);  // refresh rate of PID controller
  myPIDL.SetOutputLimits(-200, 200); // this is the MAX PWM value to move motor, here change in value reflect change in speed of motor.
  myPIDR.SetMode(AUTOMATIC);   //set PID in Auto mode
  myPIDR.SetSampleTime(1);  // refresh rate of PID controller
  myPIDR.SetOutputLimits(-200, 200); // this is the MAX PWM value to move motor, here change in value reflect change in speed of motor.
}


void loop() {
  
User_InputL = 0;//angle control
User_InputR = -20;
 //REV = map (User_Input, 0, 360, 0, 4920); // mapping degree into pulse
 REVL = remap(User_InputL);
 REVR = remap(User_InputR);
//Serial.print("REVL: "); 
//Serial.print(REVR);               // printing REV value  
/*Serial.print("\t");
Serial.print("REVR: "); 
Serial.print(REVR);               // printing REV value  
Serial.print("\t");*/
setpointl = REVL;                    //PID while work to achive this value consider as SET value
setpointr = REVR;                    //PID while work to achive this value consider as SET value

  inputl = left_counter ;   // data from encoder consider as a Process value
  inputr = right_counter;
 Serial.print("LC: ");
 Serial.println(left_counter);
 //L̥Serial.print("\t");
 //Serial.print("RC: ");
 //Serial.println(right_counter);
  // myPIDL.Compute();                 // calculate new output
  //uncomment for actuation
  myPIDR.Compute();
  pwmOutr(outputr);  
  pwmOutl(outputr);
//Serial.println(outputr);
//Serial.println(outputl);// if REV > encoderValue motor move in forward direction.    
}
void pwmOutl(int outl) {                               
  if (outl > 0) {                         // if REV > encoderValue motor move in forward direction.    
    analogWrite(LEnable, outl);         // Enabling motor enable pin to reach the desire angle
    
    forwardl();                           // calling motor to move forward
  }
  else {
    analogWrite(LEnable, abs(outl));          // if REV < encoderValue motor move in forward direction.                      
    reversel();                            // calling motor to move reverse
  }
  //readString=""; // Cleaning User input, ready for new Input
}
void pwmOutr(int outr) {                               
  if (outr > 0) {
   // Serial.println(outr);// if REV > encoderValue motor move in forward direction.    
    analogWrite(REnable, outr);         // Enabling motor enable pin to reach the desire angle
    forwardr();   
  //  reversel();// calling motor to move forward
  }
  else {
    analogWrite(REnable, abs(outr));          // if REV < encoderValue motor move in forward direction.                      
    reverser(); 
    //forwardr();// calling motor to move reverse
  }
  //readString=""; // Cleaning User input, ready for new Input
}

void updateLEncoder(){
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
void updateREncoder(){
  right_aState = digitalRead(encoderPinRA); 
    
     if(digitalRead(encoderPinRB)!= right_aState) 
     { 
       right_counter ++;
     } 
     else 
     {
       right_counter --;
     }
}

void forwardl () {
  digitalWrite(LFwd, HIGH); 
 digitalWrite(LRev, LOW); 
  
}

void reversel () {
  digitalWrite(LFwd, LOW); 
 digitalWrite(LRev, HIGH); 
  
}
void finishl () {
  digitalWrite(LFwd, LOW); 
 digitalWrite(LRev, LOW); 
}

void forwardr () {
  digitalWrite(RFwd, HIGH); 
 digitalWrite(RRev, LOW); 
  
}

void reverser () {
  digitalWrite(RFwd, LOW); 
 digitalWrite(RRev, HIGH); 
  
}
void finishr () {
  digitalWrite(RFwd, LOW); 
 digitalWrite(RRev, LOW); 
}

int remap (int theta)
{
  int pulse = floor(13.667 * theta);
  return pulse;
}
