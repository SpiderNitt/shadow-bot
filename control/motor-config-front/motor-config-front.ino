//Code to rotate both Front motors in fwd direction
#define LEnable 18
#define LFwd  17  
#define LRev  18
#define REnable 15
#define RRev  16  
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
    analogWrite(REnable,0);
    digitalWrite(RFwd,LOW);
    digitalWrite(RRev,LOW);          
    analogWrite(LEnable,255);
    digitalWrite(LFwd,LOW);
    digitalWrite(LRev,LOW);
}
