#include <QTRSensors.h>

QTRSensors qtr;

const uint8_t SensorCount = 13;
uint16_t sensorValues[SensorCount];

const int PWMA = 11; 
const int AIN2 = 10;
const int AIN1 = 9;
const int STBY = 8;
const int BIN1 = 6;
const int BIN2 = 7;
const int PWMB = 5; 

const int LED_PIN = 13;

// PID constants (aggressive for speed)
float Kp = 0.25;
float Ki = 0;
float Kd = 4.0;

// Base speed values
int baseSpeed = 210;   // much higher
int maxSpeed = 230;    // max possible

int lastError = 0;

void setup() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(STBY, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12}, SensorCount);
  qtr.setTimeout(2500);

  digitalWrite(STBY, HIGH); 
  delay(1000);

  digitalWrite(LED_PIN, HIGH);  
  for (uint16_t i = 0; i < 200; i++) {
    qtr.calibrate(); 
    
    
  }
  delay(2000);
  digitalWrite(LED_PIN, LOW);  
}

void loop() {
  uint16_t position = qtr.readLineBlack(sensorValues);
  int error = position - 6500;

  // PID correction
  int motorSpeed = Kp * error + Kd * (error - lastError);
  lastError = error;

  // Fixed high speed (no slowdown)
  int leftMotorSpeed = baseSpeed + motorSpeed;
  int rightMotorSpeed = baseSpeed - motorSpeed;

  // Limit motor speeds
  leftMotorSpeed = constrain(leftMotorSpeed, -100, maxSpeed);// changed the reverse speed 
  rightMotorSpeed = constrain(rightMotorSpeed, -100, maxSpeed); // 

  // Drive motors
  digitalWrite(AIN1, leftMotorSpeed > 0 ? HIGH : LOW);
  digitalWrite(AIN2, leftMotorSpeed > 0 ? LOW : HIGH);
  analogWrite(PWMA, abs(leftMotorSpeed));

  digitalWrite(BIN1, rightMotorSpeed > 0 ? HIGH : LOW);
  digitalWrite(BIN2, rightMotorSpeed > 0 ? LOW : HIGH);
  analogWrite(PWMB, abs(rightMotorSpeed));
}
