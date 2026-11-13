#include <Stepper.h>

const int IN1 = 8;   //Bobina 1
const int IN2 = 9;   //Bobina 2
const int IN3 = 10;  //Bobina 3
const int IN4 = 11;  //Bobina 4
const int step = 2;  //tempo de cada pulso (ms)

void setup() {
  pinMode(IN1, OUTPUT);  //Pinos como saídas
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  digitalWrite(IN1, LOW);  //Bobinas desligadas
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {
  // Stepper myStepper = Stepper(step, IN1, IN2, IN3, IN4);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
