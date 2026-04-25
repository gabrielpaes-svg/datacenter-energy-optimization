// ============================================================================
// 🔋 SIMULAÇÃO IoT - OTIMIZAÇÃO DE CONSUMO ENERGÉTICO EM DATA CENTERS
// ============================================================================
// Sistema de monitoramento de 4 servidores com sensores de temperatura
// e LEDs indicadores de consumo energético
// 
// Autor: Gabriel Paes SVG
// Data: 2026
// Versão: 1.0
// ============================================================================

// ============================================================================
// CONFIGURAÇÃO DE PINOS
// ============================================================================

// Pinos Analógicos para Sensores de Temperatura (TMP36)
const int SENSOR_SERVIDOR_PRINCIPAL = A0;  // Servidor #1
const int SENSOR_SERVIDOR_BACKUP    = A1;  // Servidor #2
const int SENSOR_STORAGE            = A2;  // Servidor #3
const int SENSOR_REDE               = A3;  // Servidor #4

// Pinos Digitais para LEDs de Indicação de Consumo
const int LED_SERVIDOR_PRINCIPAL = 8;      // Vermelho
const int LED_SERVIDOR_BACKUP    = 9;      // Amarelo
const int LED_STORAGE            = 10;     // Verde
const int LED_REDE               = 11;     // Azul

// ============================================================================
// VARIÁVEIS GLOBAIS
// ============================================================================

// Armazenar leituras de temperatura
float temperatura_servidor_principal = 0.0;
float temperatura_servidor_backup    = 0.0;
float temperatura_storage            = 0.0;
float temperatura_rede               = 0.0;

// Controle de tempo
unsigned long ultimo_envio = 0;
const unsigned long INTERVALO_ENVIO = 2000;  // 2 segundos

// Contadores para análise
int leituras_total = 0;
float temperatura_maxima = 0.0;
float temperatura_minima = 100.0;

// ============================================================================
// SETUP - EXECUTADO UMA VEZ NA INICIALIZAÇÃO
// ============================================================================

void setup() {
  // Configurar pinos dos LEDs como saída
  pinMode(LED_SERVIDOR_PRINCIPAL, OUTPUT);
  pinMode(LED_SERVIDOR_BACKUP, OUTPUT);
  pinMode(LED_STORAGE, OUTPUT);
  pinMode(LED_REDE, OUTPUT);
  
  // Desligar todos os LEDs inicialmente
  digitalWrite(LED_SERVIDOR_PRINCIPAL, LOW);
  digitalWrite(LED_SERVIDOR_BACKUP, LOW);
  digitalWrite(LED_STORAGE, LOW);
  digitalWrite(LED_REDE, LOW);
  
  // Inicializar comunicação Serial (9600 baud)
  Serial.begin(9600);
  
  // Mensagem de inicialização
  Serial.println("\n");
  Serial.println("============================================================");
  Serial.println("  🔋 IoT DATA CENTER ENERGY OPTIMIZATION SYSTEM 🔋");
  Serial.println("============================================================");
  Serial.println("Sistema de Monitoramento de Consumo Energético");
  Serial.println("Sensores: 4x TMP36 | Indicadores: 4x LEDs");
  Serial.println("Arduino: Arduino Uno | Baudrate: 9600");
  Serial.println("============================================================\n");
  
  Serial.println("INICIANDO SISTEMA...\n");
}

// ============================================================================
// LOOP - EXECUTADO CONTINUAMENTE
// ============================================================================

void loop() {
  // ========== ETAPA 1: LER SENSORES ==========
  
  // Ler valores analógicos dos 4 sensores TMP36
  int valor_bruto_s1 = analogRead(SENSOR_SERVIDOR_PRINCIPAL);
  int valor_bruto_s2 = analogRead(SENSOR_SERVIDOR_BACKUP);
  int valor_bruto_s3 = analogRead(SENSOR_STORAGE);
  int valor_bruto_s4 = analogRead(SENSOR_REDE);
  
  // Converter valores analógicos para temperatura em Celsius
  // Fórmula para TMP36: T(°C) = (V - 0.5) × 100
  // onde V = (ADC/1023) × 5V
  temperatura_servidor_principal = converter_para_celsius(valor_bruto_s1);
  temperatura_servidor_backup = converter_para_celsius(valor_bruto_s2);
  temperatura_storage = converter_para_celsius(valor_bruto_s3);
  temperatura_rede = converter_para_celsius(valor_bruto_s4);
  
  // ========== ETAPA 2: ATUALIZAR LEDs ==========
  
  // Controlar LEDs baseado em limiares de temperatura
  // Cada LED representa um nível de consumo energético
  
  // LED #1 (Vermelho - Servidor Principal) acende se T > 30°C
  if (temperatura_servidor_principal > 30.0) {
    digitalWrite(LED_SERVIDOR_PRINCIPAL, HIGH);  // ACESO
  } else {
    digitalWrite(LED_SERVIDOR_PRINCIPAL, LOW);   // APAGADO
  }
  
  // LED #2 (Amarelo - Servidor Backup) acende se T > 28°C
  if (temperatura_servidor_backup > 28.0) {
    digitalWrite(LED_SERVIDOR_BACKUP, HIGH);
  } else {
    digitalWrite(LED_SERVIDOR_BACKUP, LOW);
  }
  
  // LED #3 (Verde - Storage) acende se T > 32°C
  if (temperatura_storage > 32.0) {
    digitalWrite(LED_STORAGE, HIGH);
  } else {
    digitalWrite(LED_STORAGE, LOW);
  }
  
  // LED #4 (Azul - Rede) acende se T > 26°C
  if (temperatura_rede > 26.0) {
    digitalWrite(LED_REDE, HIGH);
  } else {
    digitalWrite(LED_REDE, LOW);
  }
  
  // ========== ETAPA 3: ENVIAR DADOS VIA SERIAL ==========
  
  // Enviar dados a cada INTERVALO_ENVIO ms
  if (millis() - ultimo_envio >= INTERVALO_ENVIO) {
    
    // Calcular consumo total estimado
    float consumo_total = calcular_consumo_total(
      temperatura_servidor_principal,
      temperatura_servidor_backup,
      temperatura_storage,
      temperatura_rede
    );
    
    // Calcular temperatura média
    float temp_media = (temperatura_servidor_principal + 
                        temperatura_servidor_backup + 
                        temperatura_storage + 
                        temperatura_rede) / 4.0;
    
    // Atualizar estatísticas
    if (temp_media > temperatura_maxima) {
      temperatura_maxima = temp_media;
    }
    if (temp_media < temperatura_minima) {
      temperatura_minima = temp_media;
    }
    leituras_total++;
    
    // ===== IMPRIMIR HEADER =====
    Serial.println("----------------------------------------------------");
    Serial.print("LEITURA #");
    Serial.println(leituras_total);
    Serial.println("----------------------------------------------------");
    
    // ===== IMPRIMIR TEMPERATURAS =====
    Serial.print("T1 (Servidor Principal): ");
    Serial.print(temperatura_servidor_principal, 1);
    Serial.println("°C");
    
    Serial.print("T2 (Servidor Backup):    ");
    Serial.print(temperatura_servidor_backup, 1);
    Serial.println("°C");
    
    Serial.print("T3 (Storage):            ");
    Serial.print(temperatura_storage, 1);
    Serial.println("°C");
    
    Serial.print("T4 (Rede):               ");
    Serial.print(temperatura_rede, 1);
    Serial.println("°C");
    
    // ===== IMPRIMIR CONSUMO =====
    Serial.println("");
    Serial.print("Consumo Total Estimado: ");
    Serial.print(consumo_total, 2);
    Serial.println(" kW");
    
    Serial.print("Temperatura Média:      ");
    Serial.print(temp_media, 1);
    Serial.println("°C");
    
    // ===== IMPRIMIR STATUS DOS LEDs =====
    Serial.println("");
    Serial.print("LED Servidor Principal: ");
    Serial.println(digitalRead(LED_SERVIDOR_PRINCIPAL) ? "🔴 ACESO" : "⚫ APAGADO");
    
    Serial.print("LED Servidor Backup:    ");
    Serial.println(digitalRead(LED_SERVIDOR_BACKUP) ? "🟡 ACESO" : "⚫ APAGADO");
    
    Serial.print("LED Storage:            ");
    Serial.println(digitalRead(LED_STORAGE) ? "🟢 ACESO" : "⚫ APAGADO");
    
    Serial.print("LED Rede:               ");
    Serial.println(digitalRead(LED_REDE) ? "🔵 ACESO" : "⚫ APAGADO");
    
    // ===== IMPRIMIR RECOMENDAÇÕES =====
    Serial.println("");
    Serial.println("RECOMENDAÇÕES:");
    gerar_recomendacoes(temperatura_servidor_principal,
                       temperatura_servidor_backup,
                       temperatura_storage,
                       temperatura_rede,
                       consumo_total);
    
    Serial.println("");
    
    // Atualizar tempo do último envio
    ultimo_envio = millis();
  }
  
  // Pequeno delay para não sobrecarregar o processador
  delay(100);
}

// ============================================================================
// FUNÇÕES AUXILIARES
// ============================================================================

// Função: Converter valor analógico para temperatura (TMP36)
// Entrada: valor_bruto (0-1023 de analogRead)
// Saída: temperatura em Celsius
float converter_para_celsius(int valor_bruto) {
  // Converter ADC para voltagem: V = (ADC/1023) × 5V
  float voltagem = (valor_bruto / 1023.0) * 5.0;
  
  // Converter voltagem para temperatura: T = (V - 0.5) × 100
  // TMP36: 10mV por grau Celsius, offset 0.5V para 0°C
  float celsius = (voltagem - 0.5) * 100.0;
  
  return celsius;
}

// Função: Calcular consumo total estimado
// Entrada: 4 temperaturas dos servidores
// Saída: consumo total em kW
float calcular_consumo_total(float t1, float t2, float t3, float t4) {
  // Fórmula simplificada: consumo ≈ (soma temperaturas) × fator
  // Em um sistema real, seria mais complexo
  float soma_temperaturas = t1 + t2 + t3 + t4;
  
  // Fator de conversão (ajustado experimentalmente)
  const float FATOR_CONSUMO = 0.4;
  
  // Consumo mínimo: 5 kW (refrigeração, rede, etc)
  const float CONSUMO_BASE = 5.0;
  
  float consumo = CONSUMO_BASE + (soma_temperaturas * FATOR_CONSUMO);
  
  return consumo;
}

// Função: Gerar recomendações de otimização
void gerar_recomendacoes(float t1, float t2, float t3, float t4, float consumo) {
  int recomendacoes_count = 0;
  
  // Verificação 1: Temperatura elevada
  float temp_media = (t1 + t2 + t3 + t4) / 4.0;
  if (temp_media > 30.0) {
    recomendacoes_count++;
    Serial.print("  ");
    Serial.print(recomendacoes_count);
    Serial.println(". Aumentar refrigeração (T média > 30°C)");
    Serial.println("     💡 Economia potencial: ~2.5 kW");
  }
  
  // Verificação 2: Temperatura baixa (desperdício)
  if (temp_media < 20.0) {
    recomendacoes_count++;
    Serial.print("  ");
    Serial.print(recomendacoes_count);
    Serial.println(". Aquecimento insuficiente (T média < 20°C)");
    Serial.println("     💡 Verificar funcionamento dos servidores");
  }
  
  // Verificação 3: Consumo muito alto
  if (consumo > 40.0) {
    recomendacoes_count++;
    Serial.print("  ");
    Serial.print(recomendacoes_count);
    Serial.println(". Consumo elevado detectado");
    Serial.println("     💡 Balancear carga entre servidores");
  }
  
  // Verificação 4: Servidor Principal com temperatura muito alta
  if (t1 > 35.0) {
    recomendacoes_count++;
    Serial.print("  ");
    Serial.print(recomendacoes_count);
    Serial.println(". Servidor Principal está superaquecido (T > 35°C)");
    Serial.println("     💡 Reduzir carga ou aumentar ventilação");
  }
  
  // Verificação 5: Oportunidade de economia
  if (temp_media > 25.0 && temp_media < 28.0) {
    recomendacoes_count++;
    Serial.print("  ");
    Serial.print(recomendacoes_count);
    Serial.println(". Sistema em operação ótima!");
    Serial.println("     ✅ Sem recomendações urgentes");
  }
  
  // Se nenhuma recomendação
  if (recomendacoes_count == 0) {
    Serial.println("  ✅ Sistema operando normalmente");
  }
}

// ============================================================================
// FIM DO CÓDIGO
// ============================================================================
