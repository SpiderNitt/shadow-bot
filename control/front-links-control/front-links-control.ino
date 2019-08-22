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
double error = 0;
double angleInp = 45;
double setpointR = 0;
double theta = 0;
double errord = 0;
double preverror = 0;
double errori = 0;
double controlinput = 0;
unsigned long then = 0;
unsigned long now = 0;
double dt = 0;

double kpr = 100.0, kir = 0, kdr = 0/10000; // modify for optimal performance
double inputr = 0, outputr = 0, setpointr = 0;

//------------------------------------------------------------------//

void setup() 
{
  motorSetup();
  Serial.begin(9600); //initialize serial comunication
  encoderSetup();

  //--------- Timer setup ----------//
  TCCR1B = TCCR1B & 0b11111000 | 1;
  analogWrite(REnable,0);
}

void loop() 
{
  now = millis();
  dt = (now - then);
  setpointR = angleInp;
  theta = invRemap(right_counter);
  error = theta - setpointR;
  errord = (error -preverror);
  errori += (error);
  controlinput = (kpr*error) + (kdr*errord) + (kir*errori);

  
  if( controlinput > 255)
  {
    controlinput = 255;
  }
  else if( controlinput < -255)
  {
    controlinput = -255;
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
  //Serial.println(error);
  //Serial.println(theta);
  preverror = error;
  then = millis();
}

void motorSetup()
{
  pinMode(REnable, OUTPUT);
  pinMode(RFwd, OUTPUT); 
  pinMode(RRev, OUTPUT);
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

void encoderSetup()
{
  pinMode(encoderPinRA, INPUT_PULLUP); 
  pinMode(encoderPinRB, INPUT_PULLUP);
  digitalWrite(encoderPinRA, HIGH); //turn pullup resistor on
  digitalWrite(encoderPinRB, HIGH); //turn pullup resistor on
  attachInterrupt(encoderPinRinterrupt, updateREncoder, CHANGE); 
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
  // jack-proof
  int pulse = floor(13.667 * theta);
  return pulse;
}

int invRemap(int counter)
{
  // jack-proof
  int angle = counter*0.073170732;
  return angle%(360);
}
