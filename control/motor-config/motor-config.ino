//Code to rotate both Front motors in fwd direction
#define LEnable 17
#define LFwd  19  
#define LRev  18
#define REnable 16
#define RRev  15  
#define RFwd  14
void setup() 
  {
  pinMode(REnable, OUTPUT);
  pinMode(RFwd, OUTPUT); 
  pinMode(RRev, OUTPUT);
  pinMode(LEnable, OUTPUT);
  pinMode(LFwd, OUTPUT); 
  pinMode(LRev, OUTPUT);
  Serial.begin(9600);     
  }
void loop()
{
    analogWrite(REnable,200);
    digitalWrite(RFwd,HIGH);          
    analogWrite(LEnable,200);
    digitalWrite(LFwd,HIGH);
}
