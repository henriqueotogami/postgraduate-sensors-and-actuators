# [FEATURE] Sistema de Controle de Acesso de Porta por RFID (Arduino UNO / ESP32)

## 📌 Descrição
Desenvolvimento de uma solução de automação comercial para controle de acesso físico. O sistema deve utilizar a tecnologia RFID para validar cartões/tags e gerenciar o destravamento de uma fechadura do tipo eletroímã acionada via módulo relé.

---

## 🎯 Requisitos Funcionais

- [ ] **Validação de Cartão Cadastrado:**
  - Ao identificar um cartão válido/cadastrado, a fechadura (eletroímã) deve ser **desligada por 3 segundos** (liberando a porta) e religada automaticamente após esse período.
- [ ] **Tratamento de Cartão Não Cadastrado:**
  - Ao identificar um cartão inválido/não cadastrado, o LED integrado (`LED_BUILTIN` no Arduino UNO ou pino `D2` no ESP32) deve **piscar 3 vezes** em sinal de alerta/recusa.
- [ ] **Gestão de Cartões (Cadastro/Descadastro):**
  - Implementar um mecanismo para adicionar (cadastrar) e remover (descadastrar) UIDs de cartões na memória em tempo de execução.
  - *Nota: Não é necessário persistir os dados em memória não volátil (EEPROM/SPIFFS).*

---

## 🛠️ Requisitos Técnicos & Hardware

- **Placa Principal:** Arduino UNO (ou ESP32)
- **Módulo Leitor:** RC522 (RFID 13.56 MHz)
- **Atuador:** Módulo Relé (Controlando a Fechadura Eletroímã)
- **Sinalização Visual:** `LED_BUILTIN` (Pino 13 no Arduino UNO / Pino D2 no ESP32)

---

## 📐 Es esquema de Ligações Sugerido (Arduino UNO + RC522 + Relé)

| Componente RC522 | Pino Arduino UNO |
| :--- | :--- |
| **SDA (SS)** | D10 |
| **SCK** | D13 |
| **MOSI** | D11 |
| **MISO** | D12 |
| **IRQ** | *Não conectado* |
| **GND** | GND |
| **RST** | D9 |
| **3.3V** | 3.3V |

| Componente Relé | Pino Arduino UNO |
| :--- | :--- |
| **IN** | D8 *(exemplo)* |
| **VCC** | 5V |
| **GND** | GND |

---

## ✅ Critérios de Aceite

1. O firmware compila sem erros para Arduino UNO / ESP32.
2. A leitura de um cartão previamente liberado desativa o relé por exatamente 3 segundos.
3. A leitura de um cartão não cadastrado faz o LED piscar 3 vezes sem acionar o relé.
4. O sistema possui lógica clara via serial ou botão/cartão mestre para cadastrar/descadastrar novas tags.