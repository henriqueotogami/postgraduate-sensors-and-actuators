#include <SPI.h>
#include <MFRC522.h>

#define PIN_SS 10
#define PIN_RST 9
#define PIN_RELAY 5
#define PIN_LDR 6

const int RELAY_ON = 1;
const int MAX_TIME_RELAY_OFF = 5;

int countTimeRelayOff = 0;
int countTimeLowLight = 0;
int isCardRegistered = 0;

MFRC522 rfid(PIN_SS, PIN_RST);
byte nuidPICC[4];

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN_RELAY, OUTPUT);
  digitalWrite(PIN_RELAY, HIGH);
}

void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
  Serial.println();
}

void loop() {

  if ((countTimeRelayOff > 0) && (MAX_TIME_RELAY_OFF > countTimeRelayOff)) {
    countTimeRelayOff++;
    Serial.println(countTimeRelayOff);
    delay(500);
    return;
  }

  if (rfid.PICC_IsNewCardPresent()) {

    Serial.println(F("Cartao Inserido"));

    if (!rfid.PICC_ReadCardSerial()) {
      Serial.println(F("Leitura de Cartao - Falha"));
      return;
    }

    if (
      rfid.uid.uidByte[0] != nuidPICC[0] || 
      rfid.uid.uidByte[1] != nuidPICC[1] || 
      rfid.uid.uidByte[2] != nuidPICC[2] || 
      rfid.uid.uidByte[3] != nuidPICC[3]) {
      Serial.println(F("Leiura de Cartao - Sem Cadastro Anterior"));

      for (byte i = 0; i < 4; i++) {
        nuidPICC[i] = rfid.uid.uidByte[i];
      }

      Serial.println(F("Leitura de Cartao - TAG NUID:"));
      Serial.print(F("Leitura de artao - Hexadecimal: "));
      printHex(rfid.uid.uidByte, rfid.uid.size);

      Serial.println(F("Leitura de Cartao - Inicio do Cadastro"));
      
      for(int index = 0; index < 5; ++index){
        int readLight = analogRead(PIN_LDR);
        if (readLight < 1000) {
          countTimeLowLight++;
        }
        delay(1000);
      }

      Serial.println(F("Leitura de Cartao - Fim do Cadastro"));

      if (5 < countTimeLowLight) {
        for (int index = 0; index < 5; ++index) {
          digitalWrite(LED_BUILTIN, HIGH);
          delay(100);
          digitalWrite(LED_BUILTIN, HIGH);
        }
        countTimeLowLight = 0;
        isCardRegistered = 1;
        Serial.println(F("[Cartao cadastrado] - [SUCESSO]"));
      } else {
        Serial.println(F("[Cartao nao cadastrado] - [FALHA]"));
      }

      rfid.PICC_HaltA();
      rfid.PCD_StopCrypto1();

    } else {
      Serial.println(F("Leitura de Cartao - Lido Anteriormente"));

      if ((countTimeRelayOff == 0) && (isCardRegistered == 1)) {
        Serial.println(F("Leitura de Cartao - Porta Aberta"));
        digitalWrite(PIN_RELAY, LOW);
        countTimeRelayOff = RELAY_ON;
      } else {
        Serial.println(F("Leitura de Cartao - Falha na Abertura da Porta"));
      }
    }

  } else {

    if (MAX_TIME_RELAY_OFF == countTimeRelayOff) {
      Serial.println(F("Tempo Expirado - Porta Fechada"));
      digitalWrite(PIN_RELAY, HIGH);
      countTimeRelayOff = 0;
    } else {
      Serial.println(F("Leitura de Cartao - Aguardando"));
    }

  }
  delay(500);
}
