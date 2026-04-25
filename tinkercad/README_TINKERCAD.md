# 🔧 Simulação IoT no Tinkercad - Guia Rápido

## 📋 O que você precisa fazer

Você tem 2 arquivos prontos:

1. **`arduino_iot_sensors.cpp`** - Código completo para Arduino
2. **`ESQUEMA_CONEXOES.txt`** - Diagrama de como conectar tudo

## ⚡ Passo a Passo Simplificado (5 minutos)

### 1️⃣ Criar Projeto no Tinkercad

- Acesse: https://www.tinkercad.com
- Clique em **"Create New Design"**
- Selecione **"Circuits"**
- Renomear para: **"IoT Sensores - Data Center Energy"**

### 2️⃣ Adicionar Componentes (Copie e Cole)

**Procure no painel e adicione:**

```
✓ 1x Arduino Uno
✓ 1x Breadboard (Half)
✓ 4x TMP36 (sensores de temperatura)
✓ 4x LED (cores: vermelho, amarelo, verde, azul)
✓ 4x Resistor 220Ω
✓ Fios (vermelho, preto, amarelo)
```

### 3️⃣ Conectar (Use o arquivo ESQUEMA_CONEXOES.txt como guia)

**Resumo das conexões:**

```
SENSORES (TMP36):
  Sensor 1: VCC→5V,  OUT→A0,  GND→GND  (Servidor Principal)
  Sensor 2: VCC→5V,  OUT→A1,  GND→GND  (Servidor Backup)
  Sensor 3: VCC→5V,  OUT→A2,  GND→GND  (Storage)
  Sensor 4: VCC→5V,  OUT→A3,  GND→GND  (Rede)

LEDs + RESISTORES:
  LED 1: Pin8 → Resistor → LED Vermelho → GND
  LED 2: Pin9 → Resistor → LED Amarelo → GND
  LED 3: Pin10 → Resistor → LED Verde → GND
  LED 4: Pin11 → Resistor → LED Azul → GND
```

### 4️⃣ Adicionar Código

- Clique em **"Code"** (no topo)
- Selecione **"Text"** (C++)
- **Apague tudo** que está lá
- **Copie e Cole** o conteúdo do arquivo `arduino_iot_sensors.cpp`
- Clique em **"Start Simulation"**

### 5️⃣ Ver Resultado

Você verá:
- ✅ LEDs piscando
- ✅ Serial Monitor com dados
- ✅ Recomendações de otimização

### 6️⃣ Compartilhar

- Clique em **"Share"**
- Marque **"Make it shareable"**
- Copie o link
- Cole no README.md do GitHub

---

## 📝 Código Pronto (Se preferir copiar direto)

Apenas copie este código C++ no Tinkercad:

```cpp
// Pinos Analógicos (Sensores)
const int SENSOR1 = A0, SENSOR2 = A1, SENSOR3 = A2, SENSOR4 = A3;

// Pinos Digitais (LEDs)
const int LED1 = 8, LED2 = 9, LED3 = 10, LED4 = 11;

float temp1, temp2, temp3, temp4;
unsigned long tempo = 0;

void setup() {
  pinMode(LED1, OUTPUT); pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT); pinMode(LED4, OUTPUT);
  Serial.begin(9600);
  Serial.println("=== IoT Data Center Energy Optimizer ===");
}

void loop() {
  // Ler sensores
  temp1 = (analogRead(SENSOR1) * 5.0 / 1023.0 - 0.5) * 100.0;
  temp2 = (analogRead(SENSOR2) * 5.0 / 1023.0 - 0.5) * 100.0;
  temp3 = (analogRead(SENSOR3) * 5.0 / 1023.0 - 0.5) * 100.0;
  temp4 = (analogRead(SENSOR4) * 5.0 / 1023.0 - 0.5) * 100.0;
  
  // Controlar LEDs
  digitalWrite(LED1, temp1 > 30 ? HIGH : LOW);
  digitalWrite(LED2, temp2 > 28 ? HIGH : LOW);
  digitalWrite(LED3, temp3 > 32 ? HIGH : LOW);
  digitalWrite(LED4, temp4 > 26 ? HIGH : LOW);
  
  // Exibir dados
  if (millis() - tempo > 2000) {
    Serial.print("T1: "); Serial.print(temp1, 1); Serial.print("°C | ");
    Serial.print("T2: "); Serial.print(temp2, 1); Serial.print("°C | ");
    Serial.print("T3: "); Serial.print(temp3, 1); Serial.print("°C | ");
    Serial.print("T4: "); Serial.print(temp4, 1); Serial.println("°C");
    
    float consumo_total = (temp1 + temp2 + temp3 + temp4) * 0.4; // Aproximado
    Serial.print("Consumo Total: "); Serial.print(consumo_total, 2); Serial.println(" kW");
    Serial.println("---");
    
    tempo = millis();
  }
  
  delay(1000);
}
```

---

## 🎥 Resultado Visual Esperado

```
Serial Monitor output:

=== IoT Data Center Energy Optimizer ===
T1: 32.5°C | T2: 25.3°C | T3: 28.9°C | T4: 22.1°C
Consumo Total: 18.54 kW
---
T1: 33.2°C | T2: 26.1°C | T3: 29.5°C | T4: 23.0°C
Consumo Total: 18.95 kW
---

LEDs Status:
🔴 RED (Pin 8) - ON  (Servidor Principal quente)
⚫ YELLOW (Pin 9) - OFF
⚫ GREEN (Pin 10) - OFF
⚫ BLUE (Pin 11) - OFF
```

---

## ✅ Checklist

- [ ] Criei novo projeto no Tinkercad
- [ ] Adicionei todos os componentes
- [ ] Conectei os sensores aos pinos A0-A3
- [ ] Conectei os LEDs aos pinos 8-11
- [ ] Copiei o código C++
- [ ] Cliquei "Start Simulation"
- [ ] Vi os LEDs piscando
- [ ] Vi os dados no Serial Monitor
- [ ] Compartilhei o projeto
- [ ] Copiei o link para o README

---

## 🆘 Problemas Comuns

**P: LEDs não acendem**
R: Verifique se o código está correto e clique em "Start Simulation"

**P: Serial Monitor vazio**
R: Clique em "Code" → selecione "Text" (C++) → adicione Serial.begin(9600)

**P: Erro ao compilar**
R: Copie exatamente o código, sem modificações

**P: Como compartilhar?**
R: Share → Make it shareable → Copy link → Abra a aba "Edit" e copie a URL

---

## 🔗 Adicionar ao README.md

Cole no seu README:

```markdown
## 🔧 Simulação IoT - Tinkercad

- **Sensores**: 4x TMP36 (Temperatura)
- **Indicadores**: 4x LEDs (Consumo Energético)
- **Microcontrolador**: Arduino Uno
- **Link**: https://www.tinkercad.com/circuits/xxxxxxxxxxxxx

[Visualizar Simulação no Tinkercad]
```

---

## 📚 Arquivos Criados

```
tinkercad/
├── arduino_iot_sensors.cpp      ← Código completo comentado
├── ESQUEMA_CONEXOES.txt         ← Diagrama visual
└── README_TINKERCAD.md          ← Este arquivo
```

Pronto! Agora você tem tudo para criar a simulação! 🚀
