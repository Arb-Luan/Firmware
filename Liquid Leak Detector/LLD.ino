// =====================
// Monitor de Concentração de Hidrocarboneto
// =====================

// ---- Configuração de Hardware ----
const int ledAlert[] = {2, 3, 4};
const int cPetroleo = A0;

// ---- Limites ----
const int LIMITE_SEGURO  = 400;
const int LIMITE_CRITICO = 800;

// ---- Controle de Tempo ----
const unsigned long INTERVALO_LEITURA = 2000;
unsigned long tempoAnterior = 0;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < sizeof(ledAlert)/sizeof(ledAlert[0]); i++) {
    pinMode(ledAlert[i], OUTPUT);
  }
}

void loop() {

  unsigned long tempoAtual = millis();

  if (tempoAtual - tempoAnterior >= INTERVALO_LEITURA) {
    tempoAnterior = tempoAtual;

    int leitura = analogRead(cPetroleo);
    processarConcentracao(leitura);
  }
}

void processarConcentracao(int leitura) {
  Serial.println("\nConcentracao de petroleo:");
  Serial.println(leitura);
  atualizarSinalizacao(leitura);
}

void atualizarSinalizacao(int nivel) {

  // Desliga todos
  for (int i = 0; i < sizeof(ledAlert)/sizeof(ledAlert[0]); i++) {
    digitalWrite(ledAlert[i], LOW);
  }

  if (nivel < LIMITE_SEGURO) {
    digitalWrite(ledAlert[0], HIGH);

  } else if (nivel < LIMITE_CRITICO) {
    digitalWrite(ledAlert[1], HIGH);

  } else {
    digitalWrite(ledAlert[2], HIGH);
  }
}
