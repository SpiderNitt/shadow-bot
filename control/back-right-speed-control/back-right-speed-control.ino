#define rEncoder 3
#define REnable 16
#define RRev  14
#define RFwd  15

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
double kpr = 100.0, kir = 0, kdr = 0 /10000; // modify for optimal performance

void setup() 
{
  Serial.begin(9600); 
  pinMode(rEncoder, INPUT);
  pinMode(REnable, OUTPUT);
  pinMode(RFwd, OUTPUT); 
  pinMode(RRev, OUTPUT); 
  attachInterrupt(1, rightEncoderISR, HIGH);
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
  errord = (error -preverror);
  errori += (error);
  controlinput = (kpr*error) + (kdr*errord) + (kir*errori);
  preverror = error;
   if(controlinput > 255)
  {
    controlinput = 255;
  }
  else if( controlinput < -200)
  {
    controlinput = -200;
  }
  if (controlinput>10)
  {
    forwardr();
    analogWrite(REnable,controlinput);
  }
  else if(controlinput < -10)
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
void rightEncoderISR()
{
  rightPulse = micros();
  rightPulse = rightPulse - rightTime;
  rightTime = micros();
  rightSpeed = ((rightPulse)*0.073170732); //Rotations per MICROSECOND
  pidr();  
}
