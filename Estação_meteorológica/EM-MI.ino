#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <ESP32Servo.h>

// =====================================================
// CONFIGURAÇÕES WI-FI E MQTT
// =====================================================
const char* ssid = "M14 do Logan";
const char* password = "capivara013";

const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;

const char* topic_subscribe = "ColMi/subscribe";

// =====================================================
// OBJETOS E PINOS
// =====================================================
WiFiClient espClient;
PubSubClient client(espClient);

const uint8_t LEDS[] = {4, 18, 19}; // LED 0 (GPIO 4) pode ser usado como Alerta de Chuva
const uint8_t NUM_LEDS = sizeof(LEDS) / sizeof(LEDS[0]);

#ifndef LED_BUILTIN
  #define LED_BUILTIN 2
#endif

#define DHT_PIN 14
#define DHT_TYPE DHT11

// Mudado para pino analógico ADC1 (GPIO 34)
#define SENSOR_CHUVA_AO 34 
const uint8_t SENSOR_MICROFONE = 27;

#define SERVO1_PIN 12
#define SERVO2_PIN 13

DHT dht(DHT_PIN, DHT_TYPE);
Servo servo1;
Servo servo2;

// =====================================================
// VARIÁVEIS DE CONTROLE
// =====================================================
unsigned long ultimoEnvio = 0;
unsigned long ultimaTentativaMQTT = 0;

const unsigned long INTERVALO_SENSORES = 5000; 
const unsigned long INTERVALO_RECONEXAO_MQTT = 5000;

#define MSG_BUFFER_SIZE 50
char msg[MSG_BUFFER_SIZE];

// Limiar de alarme (em %) para considerar chuva forte
const int LIMIAR_ALARME_CHUVA = 60; 

// =====================================================
// FUNÇÕES AUXILIARES
// =====================================================
void apagarLeds() {
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    digitalWrite(LEDS[i], LOW);
  }
  digitalWrite(LED_BUILTIN, LOW);
}

void processarPayload(String payloadStr) {
  payloadStr.trim();  
  if (payloadStr.length() == 0) return;

  // (Sua lógica de payload anterior permanece igual...)
  // ...
}

void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado!");
}

void callback(char* topic, byte* payload, unsigned int length) {
  String mensagemRecebida = "";
  for (unsigned int i = 0; i < length; i++) {
    mensagemRecebida += (char)payload[i];
  }
  processarPayload(mensagemRecebida);
}

void reconnect() {
  if (!client.connected()) {
    unsigned long agora = millis();
    if (agora - ultimaTentativaMQTT >= INTERVALO_RECONEXAO_MQTT) {
      ultimaTentativaMQTT = agora;
      String clientId = "ESP32-Client-" + String(ESP.getEfuseMac(), HEX);
      if (client.connect(clientId.c_str())) {
        client.subscribe(topic_subscribe);
      }
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    pinMode(LEDS[i], OUTPUT);
  }
  pinMode(LED_BUILTIN, OUTPUT);
  apagarLeds();

  servo1.setPeriodHertz(50);
  servo1.attach(SERVO1_PIN, 500, 2400);
  servo2.setPeriodHertz(50);
  servo2.attach(SERVO2_PIN, 500, 2400);

  // O pino analógico no ESP32 não precisa estritamente de pinMode, mas não atrapalha
  pinMode(SENSOR_MICROFONE, INPUT);

  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  } else {
    client.loop();
  }

  unsigned long agora = millis();
  if (agora - ultimoEnvio >= INTERVALO_SENSORES) {
    ultimoEnvio = agora;

    float humidity = dht.readHumidity();
    float tempC = dht.readTemperature();
    
    // =====================================================
    // LEITURA E TRATAMENTO DO SENSOR DE CHUVA (ANALÓGICO)
    // =====================================================
    int valorBrutoChuva = analogRead(SENSOR_CHUVA_AO); // Lê de 0 a 4095
    
    // Mapeia o valor invertido para porcentagem (0 a 100%)
    int intensidadeChuva = map(valorBrutoChuva, 4095, 0, 0, 100);
    intensidadeChuva = constrain(intensidadeChuva, 0, 100);

    // Sistema de Alarme Meteorológico Local
    if (intensidadeChuva >= LIMIAR_ALARME_CHUVA) {
      digitalWrite(LEDS[0], HIGH); // Acende o LED 1 como Alerta Visual de Chuva Forte
      Serial.println(">>> ALARME: Chuva Forte Detectada! <<<");
    } else {
      digitalWrite(LEDS[0], LOW);  // Desliga o alerta se o tempo estiver firme/leve
    }

    int som = digitalReal(SENSOR_MICROFONE); // correção do seu digitalRead

    // =====================================================
    // PUBLICAÇÃO DOS DADOS MQTT
    // =====================================================
    if (client.connected()) {
      Serial.println("--- Publicando dados meteorológicos ---");

      snprintf(msg, MSG_BUFFER_SIZE, "%.1f", tempC);
      client.publish("ColMi/tempC", msg);

      snprintf(msg, MSG_BUFFER_SIZE, "%d", intensidadeChuva);
      client.publish("ColMi/chuva_intensidade_pct", msg); // Publica a % da chuva

      // Classificação textual opcional baseada na intensidade
      if (intensidadeChuva == 0) {
        client.publish("ColMi/status_chuva", "Sem Chuva");
      } else if (intensidadeChuva < 30) {
        client.publish("ColMi/status_chuva", "Chuva Leve");
      } else if (intensidadeChuva < 70) {
        client.publish("ColMi/status_chuva", "Chuva Moderada");
      } else {
        client.publish("ColMi/status_chuva", "Chuva Forte (Alerta)");
      }
      
      Serial.println("Dados publicados com sucesso!");
    }
  }
}
