#include <Servo.h>

Servo servo;

const int PIN_SERVO = 9;
const int PIN_SENSOR_LEFT = A0;
const int PIN_SENSOR_RIGHT = A1;
const int lastposition = 90;
const int STEP_ANGLE = 5;

void setup() {
  Serial.begin(9600);
  servo.attach(PIN_SERVO);
  servo.write(lastposition);
  delay(1000);
}

void loop() {

  int sensorLeft = analogRead(PIN_SENSOR_LEFT);
  int sensorRight = analogRead(PIN_SENSOR_RIGHT);

  boolean isInsideLimit = (abs((sensorRight - sensorLeft)) >= 10);
  boolean isGreaterLuxRight = (sensorRight > sensorLeft);

  if (isInsideLimit) {
    lastposition = isGreaterLuxRight ? (lastposition+STEP_ANGLE) : (lastposition-STEP_ANGLE);
    lastposition = constrain(lastposition, 0, 180);
    servo.write(lastposition);
  }
  delay(30);
}