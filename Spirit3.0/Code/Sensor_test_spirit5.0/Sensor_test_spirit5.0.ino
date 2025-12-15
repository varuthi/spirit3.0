#include <QTRSensors.h>

QTRSensors qtr;

const uint8_t SensorCount = 13;
uint16_t sensorValues[SensorCount];

void setup() {
  Serial.begin(9600);

  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12}, SensorCount);

  // Calibrate sensors
  for (uint16_t i = 0; i < 200; i++) {
    qtr.calibrate();
  }
  Serial.println("Sensor calibration done!");   
}

void loop() {
  qtr.read(sensorValues);

  for (int i = 0; i < SensorCount; i++) {
    Serial.print(sensorValues[i]);
    Serial.print("\t");
  }
  Serial.println();
  delay(200); // small delay for readability
}
