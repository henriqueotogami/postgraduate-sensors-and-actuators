#include <Stepper.h>

const int stepsPerRevolution = 2048;

int actualSpeed = 12;
long sortNumber = 0;
long lastStep = 0;

Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  myStepper.setSpeed(actualSpeed);
  myStepper.step(stepsPerRevolution);
  Serial.begin(9600);
  myStepper.step(0);
  delay(500);
}

void loop() {

  if (sortNumber == 0) {
    randomSeed(analogRead(A0));
    sortNumber = random(1, 200);
    Serial.print(F("Numero sorteado: "));
    Serial.println(sortNumber);
  }

  if(actualSpeed <= 0) {
    lastStep = 0;
    sortNumber = 0;
    actualSpeed = 2;
    myStepper.setSpeed(actualSpeed);
    myStepper.step(lastStep);
    Serial.print(F("RESET"));
  }

  if (lastStep < sortNumber) {
    actualSpeed-=2;
    lastStep+=20;
    Serial.print(F("Posicao: "));
    Serial.println(lastStep);
    myStepper.setSpeed(actualSpeed);
    myStepper.step(5);
  }
}