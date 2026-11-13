# 🎡 [Atividade Prática] Projeto "Roletrando" — Roleta com Motor de Passo

**Disciplina:** Sensores e Atuadores (SEAT) — Pós-Graduação em Sistemas Embarcados  
**Referência:** Aula 8 — Motor de Passo (*Stepper Motor*)  
**Labels:** `enhancement`, `hardware`, `arduino`, `atividade-casa`

---

## 📋 Descrição da Tarefa

Em homenagem ao programa clássico *"Roletrando"* apresentado por Silvio Santos, esta atividade consiste em projetar e implementar uma réplica funcional da roleta utilizando um microcontrolador e um motor de passo.

O sistema deve permanecer em repouso aguardando o acionamento de um botão físico. Ao ser pressionado, o motor deve girar a roleta por um **intervalo de tempo aleatório** (simulando o impulso manual e a desaceleração natural) até parar completamente em uma posição sorteada.

---

## 🛠️ Requisitos de Hardware

* **Microcontrolador:** Arduino Uno (ou NodeMCU ESP8266/ESP32)
* **Atuador:** Motor de passo unipolar `28BYJ-48` ($5\text{ VDC}$, redução $1/64$)
* **Driver:** Módulo driver `ULN2003A`
* **Entrada Digital:** 1x *Push-button* (botão táctil) + resistor de *pull-down* (ou uso de `INPUT_PULLUP` interno)
* **Alimentação:** Fonte externa de $5\text{ V}$ dedicada para o motor/driver (com `GND` compartilhado com o microcontrolador)
* **Estrutura Mecânica:** Disco da roleta impresso/montado e acoplado ao eixo do motor

---

## ⚙️ Requisitos Funcionais

1. **Estado Inicial (Ocioso):** O motor deve iniciar desligado (bobinas desenergizadas para evitar aquecimento e consumo desnecessário) enquanto aguarda o acionamento do botão.
2. **Disparo por Botão:** Ao detectar o clique no botão (com tratamento de *debounce*), o sistema inicia o ciclo de giro. Novas pressões durante o giro devem ser ignoradas.
3. **Aleatoriedade:** Utilizar uma semente aleatória (ex.: `randomSeed(analogRead(A0))`) para sortear a duração do giro ou a quantidade total de passos a serem executados.
4. **Perfil de Movimento (Opcional/Recomendado):** Implementar rampa de desaceleração progressiva (aumentando o intervalo entre passos ao final do ciclo) para simular a perda de inércia da roleta real.
5. **Parada e Economia:** Ao finalizar o movimento, desenergizar as bobinas do driver (`LOW` nas saídas `IN1`–`IN4`) e aguardar um novo acionamento.

---

## ✅ Checklist de Implementação

- [ ] **Montagem Elétrica:** Conectar os pinos `IN1`, `IN2`, `IN3` e `IN4` do driver `ULN2003A` às portas digitais do microcontrolador e alimentar o módulo com $5\text{ V}$.
- [ ] **Leitura do Botão:** Implementar leitura digital com *debounce* via software.
- [ ] **Lógica de Sorteio:** Configurar gerador de números pseudoaleatórios (`random()`) para definir o tempo/passos de parada.
- [ ] **Controle do Motor:** Implementar o acionamento via biblioteca (`Stepper.h` / `AccelStepper.h`) ou sequência direta (*Full-Step* / *Half-Step*).
- [ ] **Prototipagem Física:** Fixar o disco numerado/colorido no eixo do `28BYJ-48` e posicionar um ponteiro indicador fixo.
- [ ] **Testes e Validação:** Verificar se o motor não perde passos durante o arranque e se a parada ocorre de forma imprevisível.

---

## 💡 Dicas Técnicas

* **Ordem dos pinos na `Stepper.h`:** Para o motor `28BYJ-48`, lembre-se de declarar os pinos na sequência cruzada `(8, 10, 9, 11)` e configurar `2048` passos por revolução para o giro correto nos dois sentidos.
* **Desenergização após parada:** Como o motor `28BYJ-48` possui caixa de redução interna ($1/64$), o atrito mecânico das engrenagens já é suficiente para segurar o disco parado sem precisar manter corrente nas bobinas após o sorteio.