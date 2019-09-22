
//Code to rotate both Front motors in fwd direction
#define LEnable 17
#define LFwd  18  
#define LRev  19
#define REnable 16
#define RRev  14
#define RFwd  15
int then,now;
int i=0;
void setup() 
  {
  pinMode(REnable, OUTPUT);
  pinMode(RFwd, OUTPUT); 
  pinMode(RRev, OUTPUT);
  pinMode(LEnable, OUTPUT);
  pinMode(LFwd, OUTPUT); 
  pinMode(LRev, OUTPUT);
  Serial.begin(9600);
  digitalWrite(RRev,LOW);
  digitalWrite(LRev,LOW);
    delay(2000);
    then = millis();
  }
void loop()
{ 
    now= millis();

    if(abs(then-now)>300 && abs(then-now)<370)
    {
     analogWrite(REnable,255);       
     analogWrite(LEnable,255);
     digitalWrite(LRev,HIGH);
     digitalWrite(RRev,HIGH);
     delay(50); 
     analogWrite(REnable,0);       
     analogWrite(LEnable,0);
     digitalWrite(LFwd,LOW);
     digitalWrite(RFwd,LOW);
     digitalWrite(LRev,LOW);
     digitalWrite(RRev,LOW);
    }
    else if(abs(then-now)<300)
    {
          analogWrite(REnable,255);
    digitalWrite(RFwd,HIGH);       
    analogWrite(LEnable,255);
    digitalWrite(LFwd,HIGH);
    delay(100);
    /*digitalWrite(LFwd,LOW);
    digitalWrite(RFwd,LOW);
    delay(1);*/
    }


}
