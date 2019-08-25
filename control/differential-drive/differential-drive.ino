// Pins used on arduino
#define rEncoder 3
#define lEncoder 2
#define rpwm 16
#define ldir 4
#define rdir 7
#define lpwm 17

// Variables used in interrupts
double rightPulse;
double rightTime;
double rightWheel;

double leftPulse;
double leftTime;
double leftWheel;

float rightSpeed = 0, leftSpeed = 0; // Actual Speed in Relvolutions Per Second (RPS)
float desiredRPS = 0.70; // Desired Speed in Relvolutions Per Second (RPS)
int desiredBotSpeed = 255; // Fixed disired Robot Wheel Speed (PWM value to motor)
int rightWheelSpeed = 160; // Variable Robot Wheel Speed (PWM value to motor)
int leftWheelSpeed = 160; // Variable Robot Wheel Speed (PWM value to motor)

void setup(){
  
  Serial.begin(9600);
  
  pinMode(rEncoder, INPUT);
  pinMode(lEncoder, INPUT);
  
  pinMode(rpwm, OUTPUT);
  pinMode(rdir, OUTPUT);
  pinMode(lpwm, OUTPUT);
  pinMode(ldir, OUTPUT);
  
  // Enable the pull up resistors for the encoders
  digitalWrite(rEncoder, HIGH);
  digitalWrite(lEncoder, HIGH);
  // Enable interrupts 0 and 1 on pins D2 and D3
  attachInterrupt(1, rightEncoderISR, CHANGE);
  attachInterrupt(0, leftEncoderISR, CHANGE);
  
  // Turn on motors
  analogWrite(rpwm, rightWheelSpeed);
  analogWrite(lpwm, leftWheelSpeed);
  
}// End Setup

void loop(){
  digitalWrite(ldir, HIGH);
  digitalWrite(rdir, LOW);
  rightSpeed = ((rightPulse*0.073170732)/1000); // microseconds to seconds, 1 pulse is equal to 0.07317032 degree
  leftSpeed = ((leftPulse*0.073170732)/1000);
  Serial.print(rightSpeed);
  Serial.print('\t');
  Serial.println(leftSpeed);
}

void rightEncoderISR(){
  rightPulse = millis() - rightTime;
  rightTime = millis();
}

void leftEncoderISR(){
  leftPulse = millis() - leftTime;
  leftTime = millis();
}
