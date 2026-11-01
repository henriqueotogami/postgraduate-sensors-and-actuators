#include <Servo.h>

Servo servo;

const int PIN_SERVO = 9;
const int PIN_LDR = A0;
const int LOW_LIGHT_MIN = 1016;
const int LOW_LIGHT_MAX = 1018;
const int STEP = 5;
const int SERVO_LIMIT = 180;
const int SHORT_PRESS_CYCLES = 2;
const int LONG_PRESS_CYCLES = 5;
const unsigned long LDR_INTERVAL = 200;
const unsigned long SERVO_INTERVAL = 500;

int countTimeLowLight = 0;
int lastDegree = 0;

bool isLowLight = false;
bool wasHighLight = true;
bool isRunning = false;

unsigned long lastLdrSampleTime = 0;
unsigned long lastServoStepTime = 0;

void setup() {
  Serial.begin(9600);
  servo.attach(PIN_SERVO);
  servo.write(lastDegree);
  pinMode(PIN_LDR, INPUT);
}

void loop() {
  Serial.println("STARTING");
  unsigned long currentTime = millis();
  
  if (currentTime - lastLdrSampleTime >= LDR_INTERVAL) {
    lastLdrSampleTime = currentTime;

    Serial.println("LDR INTERVAL");
    int readLDR = analogRead(PIN_LDR);
    isLowLight = (LOW_LIGHT_MAX < readLDR);
    bool isLowEdge = wasHighLight && isLowLight;
    wasHighLight = !isLowLight;

    Serial.println(readLDR);

    if (isLowLight) {
      countTimeLowLight++;
    }

  }

  if (countTimeLowLight >= LONG_PRESS_CYCLES) {
    Serial.println(">> Evento: TOQUE LONGO (RESET) <<");
    isRunning = false;
    countTimeLowLight = 0;
    lastDegree = 0;
    servo.write(lastDegree);
  }

  bool isHighEdge = wasHighLight && !isLowLight;
  
  if (isHighEdge) {
    if (countTimeLowLight > 0 && countTimeLowLight < LONG_PRESS_CYCLES) {
      isRunning = !isRunning; // Alterna estado (Liga / Pausa)
      Serial.print(">> Evento: TOQUE CURTO -> Cronometro: ");
      Serial.println(isRunning ? "RODANDO" : "PAUSADO");
    }
    countTimeLowLight = 0;
  }

  if((currentTime - lastServoStepTime) >= SERVO_INTERVAL) {
    lastServoStepTime = currentTime;

    Serial.println("SERVO INTERVAL");
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
    } else {
      if(lastDegree == SERVO_LIMIT) {
          Serial.println("SERVO LIMIT");
        isRunning = false;
        countTimeLowLight = 0;
        lastDegree = 0;
        servo.write(lastDegree);
      }
    }
  }
  
  Serial.println("END");
  delay(1000);
}