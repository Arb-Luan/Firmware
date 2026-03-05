#include <Servo.h>

// =====================
// Hardware
// =====================

const int ledAlert[] = {2,3,4};
const int sensorPetroleo = A0;
const int servoPin = 5;
const int buzzer = 6;

// =====================
// Servo
// =====================

Servo valvula;

const int VALVULA_ABERTA = 160;
const int VALVULA_MEIA = 45;
const int VALVULA_FECHADA = 90;

// =====================
// Limites
// =====================

const int LIMITE_SEGURO = 400;
const int LIMITE_CRITICO = 800;

// =====================
// Controle de tempo
// =====================

const unsigned long INTERVALO_LEITURA = 2000;
unsigned long tempoAnterior = 0;

// =====================
// Buffer de leituras
// =====================

const int TAM_BUFFER = 5;
int buffer[TAM_BUFFER];
int indice = 0;

// =====================
// Estados
// =====================

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

  for(int i=0;i<3;i++)
  pinMode(ledAlert[i],OUTPUT);

  pinMode(buzzer,OUTPUT);

  valvula.attach(servoPin);

  delay(500);

  valvula.write(VALVULA_ABERTA);

  Serial.println("Sistema inteligente iniciado");
}

// =====================
// Loop
// =====================

void loop()
{
  unsigned long tempoAtual = millis();

  if(tempoAtual - tempoAnterior >= INTERVALO_LEITURA)
  {
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

    // IA simples: se tendencia subir rápido → alerta preventivo
    if(tendencia > 40 && estadoAtual == SEGURO)
    {
      Serial.println("Possivel vazamento detectado (previsao)");
      estadoAtual = MEDIO;
    }

    atualizarLEDs(estadoAtual);

    if(estadoAtual != estadoAnterior)
    {
      controlarValvula(estadoAtual);
      estadoAnterior = estadoAtual;
    }

    controlarBuzzer(estadoAtual);
  }
}

// =====================
// Buffer
// =====================

void atualizarBuffer(int leitura)
{
  buffer[indice] = leitura;
  indice++;

  if(indice >= TAM_BUFFER)
  indice = 0;
}

int mediaMovel()
{
  long soma = 0;

  for(int i=0;i<TAM_BUFFER;i++)
  soma += buffer[i];

  return soma / TAM_BUFFER;
}

// =====================
// Tendência (IA simples)
// =====================

int calcularTendencia()
{
  int diferenca = buffer[(indice+TAM_BUFFER-1)%TAM_BUFFER] -
                  buffer[(indice+TAM_BUFFER-2)%TAM_BUFFER];

  return diferenca;
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
  for(int i=0;i<3;i++)
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
// Buzzer
// =====================

void controlarBuzzer(Nivel nivel)
{
  if(nivel == CRITICO)
  {
    tone(buzzer,1000);
  }
  else
  {
    noTone(buzzer);
  }
}

// =====================
// Válvula
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
