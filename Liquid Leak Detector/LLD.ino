#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// =====================
// LCD I2C (Frank de Brabander)
LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27 ou 0x3F dependendo do seu módulo

// =====================
// Hardware
const int ledAlert[] = {2,3,4};
const int sensorPetroleo = A0;
const int servoPin = 5;
const int buzzer = 6;

// =====================
// Servo
Servo valvula;
const int VALVULA_ABERTA = 160;
const int VALVULA_MEIA = 45;
const int VALVULA_FECHADA = 90;

// =====================
// Limites
const int LIMITE_SEGURO = 400;
const int LIMITE_CRITICO = 800;

// =====================
// Tempo
const unsigned long INTERVALO_LEITURA = 2000;
unsigned long tempoAnterior = 0;

// =====================
// Buffer
const int TAM_BUFFER = 5;
int buffer[TAM_BUFFER];
int indice = 0;

// =====================
// Estados
enum Nivel { SEGURO, MEDIO, CRITICO };
Nivel estadoAtual = SEGURO;
Nivel estadoAnterior = SEGURO;

// =====================
// Setup
void setup() {
  Serial.begin(9600);

  lcd.init();       // inicializa o LCD
  lcd.backlight();  // liga backlight
  lcd.setCursor(0,0);
  lcd.print("Sistema iniciado");

  for(int i=0;i<3;i++)
    pinMode(ledAlert[i],OUTPUT);
  pinMode(buzzer,OUTPUT);

  valvula.attach(servoPin);
  valvula.write(VALVULA_ABERTA);

  delay(1500);
  lcd.clear();

  Serial.println("Sistema inteligente iniciado");
}

// =====================
// Loop
void loop() {
  unsigned long tempoAtual = millis();

  if(tempoAtual - tempoAnterior >= INTERVALO_LEITURA) {
    tempoAnterior = tempoAtual;

    int leitura = analogRead(sensorPetroleo);

    atualizarBuffer(leitura);

    int leituraFiltrada = mediaMovel();
    int tendencia = calcularTendencia();

    Serial.print("Leitura filtrada: ");
    Serial.println(leituraFiltrada);
    Serial.print("Tendencia: ");
    Serial.println(tendencia);

    estadoAtual = classificarNivel(leituraFiltrada);

    // IA simples: tendência de vazamento
    if(tendencia > 40 && estadoAtual == SEGURO) {
      Serial.println("Possivel vazamento detectado (previsao)");
      estadoAtual = MEDIO;
    }

    atualizarLEDs(estadoAtual);

    if(estadoAtual != estadoAnterior) {
      controlarValvula(estadoAtual);
      estadoAnterior = estadoAtual;
    }

    controlarBuzzer(estadoAtual);
    atualizarDisplay(leituraFiltrada, estadoAtual);
  }
}

// =====================
// Buffer
void atualizarBuffer(int leitura) {
  buffer[indice] = leitura;
  indice++;
  if(indice >= TAM_BUFFER) indice = 0;
}

int mediaMovel() {
  long soma = 0;
  for(int i=0;i<TAM_BUFFER;i++) soma += buffer[i];
  return soma / TAM_BUFFER;
}

// =====================
// Tendência
int calcularTendencia() {
  int diferenca = buffer[(indice+TAM_BUFFER-1)%TAM_BUFFER] -
                  buffer[(indice+TAM_BUFFER-2)%TAM_BUFFER];
  return diferenca;
}

// =====================
// Classificação
Nivel classificarNivel(int leitura) {
  if(leitura < LIMITE_SEGURO) return SEGURO;
  if(leitura < LIMITE_CRITICO) return MEDIO;
  return CRITICO;
}

// =====================
// LEDs
void atualizarLEDs(Nivel nivel) {
  for(int i=0;i<3;i++) digitalWrite(ledAlert[i],LOW);
  switch(nivel) {
    case SEGURO: digitalWrite(ledAlert[0],HIGH); break;
    case MEDIO:  digitalWrite(ledAlert[1],HIGH); break;
    case CRITICO: digitalWrite(ledAlert[2],HIGH); break;
  }
}

// =====================
// Buzzer
void controlarBuzzer(Nivel nivel) {
  if(nivel == CRITICO) tone(buzzer,1000);
  else noTone(buzzer);
}

// =====================
// Válvula
void controlarValvula(Nivel nivel) {
  switch(nivel) {
    case SEGURO:
      Serial.println("Nivel seguro - valvula aberta");
      valvula.write(VALVULA_ABERTA);
      break;
    case MEDIO:
      Serial.println("Nivel medio - restricao parcial");
      valvula.write(VALVULA_MEIA);
      break;
    case CRITICO:
      Serial.println("Nivel critico - fechamento emergencia");
      valvula.write(VALVULA_FECHADA);
      break;
  }
}

// =====================
// DISPLAY
void atualizarDisplay(int leitura, Nivel nivel) {
  // Atualiza sem limpar a tela inteira
  lcd.setCursor(0,0);
  lcd.print("Leitura:       "); // apaga resto da linha
  lcd.setCursor(9,0);
  lcd.print(leitura);

  lcd.setCursor(0,1);
  lcd.print("Status:        "); // apaga resto da linha
  lcd.setCursor(8,1);
  switch(nivel) {
    case SEGURO: lcd.print("SEGURO "); break;
    case MEDIO:  lcd.print("MEDIO  "); break;
    case CRITICO: lcd.print("CRITICO"); break;
  }
}
