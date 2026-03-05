#include <Servo.h>

// =====================
// Monitor de Concentração de Hidrocarboneto
// =====================

// ---- Hardware ----
const int ledAlert[] = {2,3,4};
const int sensorPetroleo = A0;
const int servoPin = 5;

// ---- Servo ----
Servo valvula;

// posições mecânicas seguras
const int VALVULA_ABERTA = 160;
const int VALVULA_MEIA = 45;
const int VALVULA_FECHADA = 90;

// ---- Limites do sensor ----
const int LIMITE_SEGURO = 400;
const int LIMITE_CRITICO = 800;

// ---- Controle de tempo ----
const unsigned long INTERVALO_LEITURA = 2000;
unsigned long tempoAnterior = 0;

// ---- Estados ----
enum Nivel
{
  SEGURO,
  MEDIO,
  CRITICO
};

Nivel estadoAtual = SEGURO;
Nivel estadoAnterior = SEGURO;

// =====================
// Setup
// =====================

void setup()
{
  Serial.begin(9600);

  for(int i=0;i<sizeof(ledAlert)/sizeof(ledAlert[0]);i++)
  {
    pinMode(ledAlert[i],OUTPUT);
  }

  valvula.attach(servoPin);

  delay(500); // estabiliza servo

  valvula.write(VALVULA_ABERTA);

  Serial.println("Sistema iniciado");
}

// =====================
// Loop principal
// =====================

void loop()
{
  unsigned long tempoAtual = millis();

  if(tempoAtual - tempoAnterior >= INTERVALO_LEITURA)
  {
    tempoAnterior = tempoAtual;

    int leitura = analogRead(sensorPetroleo);

    Serial.print("Leitura sensor: ");
    Serial.println(leitura);

    estadoAtual = classificarNivel(leitura);

    atualizarLEDs(estadoAtual);

    if(estadoAtual != estadoAnterior)
    {
      controlarValvula(estadoAtual);
      estadoAnterior = estadoAtual;
    }
  }
}

// =====================
// Classificação
// =====================

Nivel classificarNivel(int leitura)
{
  if(leitura < LIMITE_SEGURO)
  return SEGURO;

  if(leitura < LIMITE_CRITICO)
  return MEDIO;

  return CRITICO;
}

// =====================
// LEDs
// =====================

void atualizarLEDs(Nivel nivel)
{
  for(int i=0;i<sizeof(ledAlert)/sizeof(ledAlert[0]);i++)
  digitalWrite(ledAlert[i],LOW);

  switch(nivel)
  {
    case SEGURO:
    digitalWrite(ledAlert[0],HIGH);
    break;

    case MEDIO:
    digitalWrite(ledAlert[1],HIGH);
    break;

    case CRITICO:
    digitalWrite(ledAlert[2],HIGH);
    break;
  }
}

// =====================
// Controle da válvula
// =====================

void controlarValvula(Nivel nivel)
{
  switch(nivel)
  {
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
