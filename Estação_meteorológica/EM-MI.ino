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

// Tópico para receber comandos (Inscrição)
const char* topic_subscribe = "ColMi/subscribe";

// Tópico para passar dados
const char* topic_publisher_temp = "ColMi/temperatura";
const char* topic_publisher_umid = "ColMi/umidade";

// =====================================================
// OBJETOS E PINOS
// =====================================================

WiFiClient espClient;
PubSubClient client(espClient);

const uint8_t LEDS[] = {4, 18, 19};
const uint8_t NUM_LEDS = sizeof(LEDS) / sizeof(LEDS[0]);

#ifndef LED_BUILTIN
  #define LED_BUILTIN 2
#endif

// DHT movido para o pino 14 para liberar o GPIO 2 (LED Built-in)
#define DHT_PIN 14
#define DHT_TYPE DHT11

const uint8_t SENSOR_CHUVA = 26;
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
unsigned long contador = 0;

const unsigned long INTERVALO_SENSORES = 5000; 
const unsigned long INTERVALO_RECONEXAO_MQTT = 5000;

#define MSG_BUFFER_SIZE 50
char msg[MSG_BUFFER_SIZE];

// =====================================================
// FUNÇÕES AUXILIARES - CONTROLE DE DISPOSITIVOS
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

  Serial.print("Comando processado: [");
  Serial.print(payloadStr);
  Serial.println("]");

  if (payloadStr.indexOf(':') != -1) {
    int separador = payloadStr.indexOf(':');
    int payloadId = payloadStr.substring(0, separador).toInt();
    int valor = payloadStr.substring(separador + 1).toInt();

    switch (payloadId) {
      case 2: // Servo 1
        valor = constrain(valor, 0, 180);
        servo1.write(valor);
        Serial.print("-> Servo 1 movido para: ");
        Serial.println(valor);
        break;
      case 3: // Servo 2
        valor = constrain(valor, 0, 180);
        servo2.write(valor);
        Serial.print("-> Servo 2 movido para: ");
        Serial.println(valor);
        break;
      default:
        Serial.println("-> Payload ID de dois pontos desconhecido.");
        break;
    }
    return;
  }

  char comando = payloadStr.charAt(0);

  switch (comando) {
    case '1':
      digitalWrite(LEDS[0], HIGH);
      Serial.println("-> LED 1 (GPIO 4) LIGADO");
      break;
    case '2':
      digitalWrite(LEDS[1], HIGH);
      Serial.println("-> LED 2 (GPIO 18) LIGADO");
      break;
    case '3':
      digitalWrite(LEDS[2], HIGH);
      Serial.println("-> LED 3 (GPIO 19) LIGADO");
      break;
    case '4':
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("-> LED Built-in LIGADO");
      break;
    case '5':
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("-> LED Built-in DESLIGADO");
      break;
    case '0':
      apagarLeds();
      Serial.println("-> Todos os LEDs e Built-in desligados.");
      break;
    default:
      Serial.print("-> Comando inválido recebido: ");
      Serial.println(comando);
      break;
  }
}

// =====================================================
// CONEXÃO WI-FI E CALLBACK MQTT
// =====================================================

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando-se a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Wi-Fi conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida no tópico [");
  Serial.print(topic);
  Serial.print("]: ");
  
  String mensagemRecebida = "";
  for (unsigned int i = 0; i < length; i++) {
    mensagemRecebida += (char)payload[i];
  }
  
  Serial.println(mensagemRecebida);
  processarPayload(mensagemRecebida);
}

void reconnect() {
  if (!client.connected()) {
    unsigned long agora = millis();
    if (agora - ultimaTentativaMQTT >= INTERVALO_RECONEXAO_MQTT) {
      ultimaTentativaMQTT = agora;
      Serial.print("Tentando conexão MQTT...");
      
      String clientId = "ESP32-Client-";
      clientId += String(ESP.getEfuseMac(), HEX);
      
      if (client.connect(clientId.c_str())) {
        Serial.println("conectado!");
        client.subscribe(topic_subscribe);
      } else {
        Serial.print("falhou, rc=");
        Serial.print(client.state());
        Serial.println(" tentando novamente em 5 segundos.");
      }
    }
  }
}

// =====================================================
// SETUP E LOOP PRINCIPAIS
// =====================================================

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

  pinMode(SENSOR_CHUVA, INPUT);
  pinMode(SENSOR_MICROFONE, INPUT);

  dht.begin();
  Serial.println("DHT Sensor Inicializado com Sucesso.");

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
    contador++;

    float humidity = dht.readHumidity();
    float tempC = dht.readTemperature();
    float tempF = dht.readTemperature(true);

    int chuva = digitalRead(SENSOR_CHUVA);
    int som = digitalRead(SENSOR_MICROFONE);

    if (isnan(humidity) || isnan(tempC) || isnan(tempF)) {
      Serial.println("Warning: Failed to read from DHT sensor! Check your wiring.");
      return; 
    }

    float heatIndexC = dht.computeHeatIndex(tempC, humidity, false);
    float heatIndexF = dht.computeHeatIndex(tempF, humidity);

    // =====================================================
    // PUBLICAÇÃO EM TÓPICOS SEPARADOS
    // =====================================================
    if (client.connected()) {
      Serial.println("--- Publicando dados em tópicos separados ---");

      snprintf(msg, MSG_BUFFER_SIZE, "%.1f", tempC);
      client.publish("ColMi/tempC", msg);

      snprintf(msg, MSG_BUFFER_SIZE, "%.1f", tempF);
      client.publish("ColMi/tempF", msg);

      snprintf(msg, MSG_BUFFER_SIZE, "%.1f", humidity);
      client.publish("ColMi/umid", msg);

      snprintf(msg, MSG_BUFFER_SIZE, "%.1f", heatIndexC);
      client.publish("ColMi/hiC", msg);

      snprintf(msg, MSG_BUFFER_SIZE, "%.1f", heatIndexF);
      client.publish("ColMi/hiF", msg);

      snprintf(msg, MSG_BUFFER_SIZE, "%d", chuva);
      client.publish("ColMi/chuva", msg);

      snprintf(msg, MSG_BUFFER_SIZE, "%d", som);
      client.publish("ColMi/som", msg);
      
      Serial.println("Dados publicados com sucesso!");
    }
  }
}
