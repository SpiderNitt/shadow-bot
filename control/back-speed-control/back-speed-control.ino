#define rEncoder 3
#define REnable 16
#define RRev  14
#define RFwd  15

#define LEnable 17
#define LFwd  18  
#define LRev  19

double rightPulse = 0.0;
double rightTime = 0.0;
double rightSpeed = 0.0;

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
  pinMode(REnable, OUTPUT);
  pinMode(RFwd, OUTPUT); 
  pinMode(RRev, OUTPUT); 

  pinMode(LEnable, OUTPUT);
  pinMode(LFwd, OUTPUT); 
  pinMode(LRev, OUTPUT);  
  attachInterrupt(1, rightEncoderISR, CHANGE);
}

void loop()
{  
  rightSpeed = 0.0;
}
void pidr()
{
  setpointR = 20/10000000;  //Revolutions per 0.1 Seconds
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
    forwardl();
    analogWrite(LEnable,controlinput);
    analogWrite(REnable,controlinput);
  }
  else if(controlinput < -30)
  {
    reverser();    
    analogWrite(REnable,abs(controlinput));
    reversel();    
    analogWrite(LEnable,abs(controlinput));    
  }
  else 
  {
    finishr();
    finishl();
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
void rightEncoderISR()
{
  rightPulse = micros();
  rightPulse = rightPulse - rightTime;
  rightTime = micros();
  rightSpeed = ((rightPulse)*0.073170732); //Rotations per MICROSECOND
  pidr();  
}
