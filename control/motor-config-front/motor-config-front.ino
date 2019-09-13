//Code to rotate both Front motors in fwd direction
#define LEnable 5
#define LDir  17    //Direction pin low moves the bot forward
#define REnable 6
#define RDir  16  //Direction pin low moves the bot forward


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
    analogWrite(LEnable,0);
    digitalWrite(LFwd,LOW);
    digitalWrite(LRev,LOW);
}
