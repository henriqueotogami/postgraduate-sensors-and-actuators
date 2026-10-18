# 🔌 Pós-Graduação em Sistemas Embarcados — Sensores e Atuadores (SEAT)

Este repositório é destinado ao armazenamento de notas de aula, rotinas de código, relatórios de práticas e projetos desenvolvidos na disciplina de **Sensores e Atuadores**, integrante da **Pós-Graduação em Sistemas Embarcados** da **Faculdade de Tecnologia SENAI Anchieta**.

---

## 📌 Contexto e Objetivos

A disciplina aborda o estudo conceitual e prático do condicionamento de sinais, técnicas de calibração, integração de sensores (analógicos e digitais) e acionamento de atuadores, com foco em aplicações para **Internet das Coisas (IoT)** e **Sistemas Embarcados**.

* **Instituição:** Faculdade de Tecnologia SENAI Anchieta
* **Curso:** Pós-Graduação *Lato Sensu* em Sistemas Embarcados
* **Disciplina:** Sensores e Atuadores
* **Carga Horária:** 30 horas
* **Ambiente de Desenvolvimento Principal:** MicroPython (IDE Thonny) / Arduino C/C++
* **Plataforma de Hardware:** ESP32 / NodeMCU (ESP8266) / Arduino Uno

---

## 🛠️ Tecnologias e Infraestrutura Utilizadas

### Hardware
* **Placas de Desenvolvimento:** ESP32 DevKit, ESP8266 (NodeMCU), Arduino
* **Sensores:**
  * LDR (Light Dependent Resistor)
  * Sensores de luz digital (BH1750, TSL2561)
  * Sensores Ultrassônicos
  * Encoders
* **Atuadores:** LEDs, Relés, Motores/Servos
* **Acessórios:** Kit de componentes, protoboards, jumpers e resistores

### Software & Ferramentas
* **Linguagens:** Python (MicroPython), C/C++
* **IDE:** [Thonny IDE](https://thonny.org/)
* **Ferramentas de Flash/Upload:** `esptool`, `ampy` (Adafruit MicroPython Tool)
* **Outros:** Python 3.10+

---

## 📚 Ementa da Disciplina

1. **Introdução a Sensores e Transdutores:**
   * Conceito de sensores vs. transdutores.
   * Classificação das formas de energia envolvidas.
   * Tipos de saída (analógica e digital: PWM, I2C, SPI, 1-Wire).

2. **Características Estáticas e Dinâmicas:**
   * Sensibilidade, Resolução/Passo, Erro de Sensibilidade.
   * Exatidão (Acurácia) vs. Precisão (Repetibilidade).
   * Alcance (*Range*), Linearidade, Estabilidade e Tempo de Resposta.

3. **Práticas e Calibração:**
   * Sensores de Iluminância (LDR e cálculo em Lux).
   * Relações logarítmicas e linearização de curvas.
   * Projetos com Encoders e Sensores Ultrassônicos.
   * Acionamento e controle de atuadores.

---

## 📂 Estrutura do Repositório

```text
.
├── docs/                 # Documentos, PDFs das aulas e referências teóricas
├── praticas/             # Códigos das práticas de aula divididas por tema
│   ├── aula-01-02-infra/ # Configuração de ambiente, firmware e Hello World (MicroPython)
│   ├── aula-03-ldr/      # Leitura analógica, calibração e conversão de LDR/Lux
│   └── ...
├── atividades/           # Atividades de avaliação (AT1 a AT8)
└── README.md             # Documentação principal do repositório
```
---

## 🚀 Como Executar os Códigos
### Pré-requisitos
- Instalar o Python 3.10+.
- Instalar a Thonny IDE.
- Gravar o firmware do MicroPython na placa ESP32/ESP8266 via esptool:

```shell
pip install esptool ampy
esptool.py --port <PORTA_COM> erase_flash
esptool.py --port <PORTA_COM> --chip esp32 write_flash -z 0x1000 <firmware_micropython>.bin
```

### Execução via Thonny
- Abra a IDE Thonny.
- Acesse Ferramentas -> Opções -> Interpretador.
- Selecione MicroPython (ESP32) ou MicroPython (ESP8266) e escolha a porta COM correspondente à sua placa.
- Abra o script .py desejado localizado na pasta praticas/ e clique em Run (F5).

## 📝 Avaliação e Atividades
A composição final da nota é dada pela média aritmética das atividades práticas desenvolvidas ao longo do curso:

$$\text{Média} = \frac{\sum_{i=1}^{8} \text{Atividade}_i}{8}$$

## 📖 Referências Bibliográficas

- WILSON, Jon S. Sensor Technology Handbook. Elsevier/Newnes.
- KARVINEN, Tero; KARVINEN, Kimmo. Make: Sensors - Projects and Experiments to Measure the World with Arduino and Raspberry Pi. O'Reilly.
- Documentação oficial do MicroPython: docs.micropython.org
