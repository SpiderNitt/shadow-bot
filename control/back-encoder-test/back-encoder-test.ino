#define rEncoder 3
#define lEncoder 2
double leftPulse = 0.0;
double leftTime = 0.0;
double rightPulse = 0.0;
double rightTime = 0.0;
double rightSpeed = 0.0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  pinMode(rEncoder, INPUT);
  pinMode(lEncoder, INPUT);
  attachInterrupt(1, rightEncoderISR, HIGH);
  attachInterrupt(0, leftEncoderISR, CHANGE);
  

}

void loop()
{  rightSpeed = 0.0;
  // put your main code here, to run repeatedly:
  /*Serial.print(leftPulse/1000.0);
  Serial.print('\t');*/
  //Serial.println(rightPulse);
  //Serial.println('0');
  //Serial.println(rightSpeed);
;
  //rightSpeed = 0;
}
void rightEncoderISR()
{
  rightPulse = micros() - rightTime;
  rightTime = micros();
  rightSpeed = ((rightPulse)*0.073170732);
  //Serial.println(rightSpeed);
}

void leftEncoderISR()
{
  leftPulse = micros() - leftTime;
  leftTime = micros();
  //Serial.println('2');
}
