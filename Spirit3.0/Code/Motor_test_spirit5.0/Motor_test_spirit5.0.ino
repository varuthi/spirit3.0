// Motor Test for L298N
const int PWMA = 5; 
const int AIN2 = 7;
const int AIN1 = 6;
const int STBY = 8;
const int BIN1 = 9;
const int BIN2 = 10;
const int PWMB = 11;

void setup() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);
  
  digitalWrite(STBY, HIGH); // Enable motor driver
}

void loop() {
  // Forward
  motorA(200);
  motorB(200);
  delay(2000);
  
  // Backward
  motorA(-200);
  motorB(-200);
  delay(2000);
  
  // Turn Right
  motorA(200);
  motorB(-200);
  delay(1000);
  
  // Turn Left
  motorA(-200);
  motorB(200);
  delay(1000);
  
  // Stop
  motorA(0);
  motorB(0);
  delay(1000);
}

void motorA(int speed) {
  if (speed >= 0) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  } else {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    speed = -speed;
  }
  analogWrite(PWMA, constrain(speed, 0, 255));
}

void motorB(int speed) {
  if (speed >= 0) {
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  } else {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    speed = -speed;
  }
  analogWrite(PWMB, constrain(speed, 0, 255));
}
