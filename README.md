# 📍 Checkpoint II - Monitor de Ambiente com Arduino

Este projeto foi desenvolvido para o checkpoint da disciplina de **Edge Computing em parceria à Vinheria Agnello**, utilizando o **Arduino Uno**. O objetivo é monitorar a intensidade de luz, temperatura e umidade, e exibir essas informações em um display LCD, com alertas visuais e sonoros.

## 🧰 Componentes Utilizados

- 1 Arduino Uno
- 1 Sensor LDR
- 1 Sensor de temperatura e umidade DHT22
- 3 LEDs (Verde, Amarelo, Vermelho)
- 1 Buzzer
- 1 Display LCD 16x2
- 1 Potenciômetro (para ajuste do contraste do LCD)
- 3 Resistores de 220Ω (para os LEDs)
- 1 Resistor de 10kΩ (para o LDR)
- Jumpers
- Protoboard

## ⚙️ Funcionamento

O sistema realiza a leitura da **luminosidade**, **temperatura** e **umidade** do ambiente. Com base na luminosidade, ele ativa diferentes LEDs e sons de alerta com o buzzer. As informações são exibidas em tempo real no **display LCD**.

## 🔄 Lógica de Decisão

### 💡 Luminosidade

```cpp
const unsigned int LIMITE_ALERTA = 700;
const unsigned int LIMITE_OK = 400;
```

- **valorLuz < 400**: Liga o LED **Verde**, buzzer desligado, ícone feliz
- **400 ≤ valorLuz < 700**: Liga o LED **Amarelo**, buzzer tocando brevemente, ícone sério
- **valorLuz ≥ 700**: Liga o LED **Vermelho**, buzzer desligado, ícone triste

### 🌡️ Temperatura e Umidade

- As leituras do sensor **DHT22** são exibidas no LCD.
- Em caso de falha na leitura, é exibida a mensagem: `Erro leitura DHT`.

## 🖥️ Código Fonte

O código foi escrito em **C/C++ para Arduino** e está disponível no arquivo `monitor-ambiente.ino`. Ele utiliza as bibliotecas:

- `Adafruit_Sensor`
- `DHT`
- `DHT_U`
- `LiquidCrystal`

Essas bibliotecas devem ser instaladas na IDE Arduino para o correto funcionamento do projeto.

## 🔌 Ligações do Circuito

### 📷 Sensor LDR
- Uma ponta → 5V  
- Outra ponta → A0 e resistor de 10kΩ → GND

### 🌡️ Sensor DHT22
- VCC → 5V  
- GND → GND  
- DATA → Pino 8

### 💡 LEDs
- Verde → Pino 6  
- Amarelo → Pino 7  
- Vermelho → Pino 9  
> (Com resistores de 220Ω)

### 🔊 Buzzer
- Positivo → Pino 10  
- Negativo → GND

### 🖥️ LCD 16x2
- rs → Pino 12  
- enable → Pino 11  
- d4 → Pino 5  
- d5 → Pino 4  
- d6 → Pino 3  
- d7 → Pino 2  
- VSS → GND  
- VDD → 5V  
- VO → Meio do potenciômetro  
- RW → GND  
- Anodo → 5V via resistor  
- Catodo → GND

### ⚙️ Potenciômetro
- Um lado → 5V  
- Outro lado → GND  
- Meio → VO (LCD)

## 🎬 Vídeo de Apresentação
Confira o vídeo de apresentação do projeto em funcionamento no link abaixo:

- [🔗 Ver vídeo no Google Drive](https://drive.google.com/file/d/1GhWGCmn7vufVgeovqUPlMMioTjpA7dhl/view)

## 📀 Como Testar

Monte o circuito conforme o **diagrama no Wokwi**:

- [🔗 Abrir projeto no Wokwi](https://wokwi.com/projects/431033596095781889)

## 📕 Aprendizados

Este projeto explora conceitos como:

- Leitura de sensores analógicos e digitais
- Condicionais e controle lógico (`if`, `else`)
- Controle de LEDs e buzzer
- Criação de caracteres personalizados no LCD
- Comunicação serial com o computador

## 📋 Observações

- Os valores de luminosidade variam conforme o sensor e o ambiente.
- A biblioteca do DHT22 pode ocasionalmente retornar leituras inválidas, que foram tratadas no código.
- O contraste do LCD deve ser ajustado pelo potenciômetro para melhor visualização.

---

Checkpoint de Edge Computing desenvolvido por:  
- **Guilherme Ruiz Costa (RM: 563236)**  
- **Guilherme Moura Gama (RM: 562162)**  
- **João Batista Lima Neto (RM: 563426)**  
- **Júlio César Augusto Vieira (RM: 563366)**
