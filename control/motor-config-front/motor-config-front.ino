//Code to rotate both Front motors in fwd direction
#define LEnable 5
#define LDir  18    //Direction pin low moves the bot forward
#define REnable 6
#define RDir  19  //Direction pin low moves the bot forward


void setup() 
  {
  pinMode(REnable, OUTPUT);
  pinMode(RDir, OUTPUT); 
  pinMode(LEnable, OUTPUT);
  pinMode(LDir, OUTPUT); 
  Serial.begin(9600);     
  }
void loop()
{
    analogWrite(REnable,60);
    digitalWrite(RDir,HIGH);
    analogWrite(LEnable,0);
    digitalWrite(LDir,LOW);
}
