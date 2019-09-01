// Pins used on arduino
#define rEncoder 3

#define REnable 16
#define RRev  14
#define RFwd  15

#define LEnable 17
#define LFwd  18  
#define LRev  19

// Variables used in interrupts
double rightPulse;
double rightTime;
double rightWheel;


float rightSpeed = 0;       // Actual Speed in Relvolutions Per Second (RPS)
float desiredRPS = 0.70;    // Desired Speed in Relvolutions Per Second (RPS)
int rightWheelSpeed = 160;  // Variable Robot Wheel Speed (PWM value to motor)

//------------------- PID VARIABLES FOR RIGHT----------------------//
double error = 0;
double speedInp = 0; //make it NEGATIVE
double setpointR = 0;
double speedr = 0;
int overshootflagr = 0;
double errord = 0;
double preverror = 0;
double errori = 0;
double controlinput = 0;
double kpr = 500.0, kir = 0, kdr = 0 /10000; // modify for optimal performance


void setup()
{
  
  Serial.begin(9600);
  
  pinMode(rEncoder, INPUT);
  
  pinMode(rEncoder, INPUT);
  pinMode(REnable, OUTPUT);
  pinMode(RFwd, OUTPUT); 
  pinMode(RRev, OUTPUT); 

  pinMode(LEnable, OUTPUT);
  pinMode(LFwd, OUTPUT); 
  pinMode(LRev, OUTPUT);  
  pinMode(rEncoder, INPUT_PULLUP); 
  attachInterrupt(1, rightEncoderISR, CHANGE);
  
  // Turn on motors
  
}

void loop(){
  analogWrite(LEnable, 150);
  digitalWrite(LFwd, HIGH);
  analogWrite(REnable, 150);
  digitalWrite(RFwd, HIGH);
  rightSpeed = ((rightPulse*0.073170732)); // microseconds to seconds, 1 pulse is equal to 0.07317032 degree
}

void rightEncoderISR(){
  rightPulse = micros() - rightTime;
  rightTime = micros();
  Serial.println(rightSpeed);
  pidr();
}
void pidr()
{ /*
    right,left :: 30,150 Straight line
    
  */
  setpointR = 2/10000000;  //Revolutions per 0.1 Seconds
  speedr = rightSpeed;
  error = speedr - setpointR;
  Serial.println(error);
  errord = (error -preverror);
  errori += (error);
  controlinput = (kpr*error) + (kdr*errord) + (kir*errori);
  preverror = error;
   if(controlinput > 255)
  {
    controlinput = 255;
  }
  else if( controlinput < -255)
  {
    controlinput = -255;
  }
  if (controlinput>30)
  {
    forwardr();
    analogWrite(LEnable,controlinput);
    
  }
  else if(controlinput < -30)
  {
    reverser();    
    analogWrite(REnable,abs(controlinput));
  }
  else 
  {
    finishr();
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
