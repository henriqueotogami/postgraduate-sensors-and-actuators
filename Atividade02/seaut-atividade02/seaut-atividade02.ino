#include <Servo.h>

Servo servo;

const int PIN_SERVO = 9;
const int PIN_LDR = A0;
const int LOW_LIGHT = 900;
const int STEP = 5;
const int SERVO_LIMIT = 180;

const int SHORT_PRESS_CYCLES = 2;
const int LONG_PRESS_CYCLES = 5;

int countTimeLowLight = 0;
int lastDegree = 0;
bool wasHighLight = true;
bool isRunning = false;

void setup() {
  Serial.begin(9600);
  servo.attach(PIN_SERVO);
  servo.write(lastDegree);
  pinMode(PIN_LDR, INPUT);
}

void loop() {
  int readLDR = analogRead(PIN_LDR);
  bool isLowLight = (readLDR < LOW_LIGHT);
  bool isLowEdge = wasHighLight && isLowLight;

  if (isLowLight) {
    countTimeLowLight++;
  }

  if (countTimeLowLight >= LONG_PRESS_CYCLES) {
    Serial.println(">> Evento: TOQUE LONGO (RESET) <<");
    isRunning = false;
    countTimeLowLight = 0;
    lastDegree = 0;
    servo.write(lastDegree);
  }

  bool isHighEdge = !wasHighLight && !isLowLight;
  if (isHighEdge) {
    if (countTimeLowLight > 0 && countTimeLowLight < LONG_PRESS_CYCLES) {
      isRunning = !isRunning; // Alterna estado (Liga / Pausa)
      Serial.print(">> Evento: TOQUE CURTO -> Cronometro: ");
      Serial.println(isRunning ? "RODANDO" : "PAUSADO");
    }
    countTimeLowLight = 0;
  }

  
  if (isRunning) {
    if (lastDegree < SERVO_LIMIT) {
      lastDegree += STEP;
      lastDegree = constrain(lastDegree, 0, SERVO_LIMIT);
      
      Serial.print("Cronometro ativo | Grau: ");
      Serial.println(lastDegree);
      servo.write(lastDegree);
    } else {
      Serial.println("Cronometro atingiu o limite!");
      isRunning = false;
    }
  }

  wasHighLight = !isLowLight;
  delay(1000);
}