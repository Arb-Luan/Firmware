#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// =====================================================
// CONFIGURAÇÕES WI-FI E MQTT
// =====================================================

const char* ssid = "M14 do Logan";
const char* password = "capivara013";

const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;

const char* topic_publish = "ColMi/publisher";
const char* topic_subscribe = "ColMi/subscribe";

// =====================================================
// OBJETOS E PINOS
// =====================================================

WiFiClient espClient;
PubSubClient client(espClient);

const uint8_t LEDS[] = {4, 18, 19};
const uint8_t NUM_LEDS = sizeof(LEDS) / sizeof(LEDS[0]);

// Configurado conforme o seu segundo código: GPIO 2 e DHT11
#define DHT_PIN 2
#define DHT_TYPE DHT11

const uint8_t SENSOR_CHUVA = 26;
const uint8_t SENSOR_MICROFONE = 27;

DHT dht(DHT_PIN, DHT_TYPE);

// =====================================================
// VARIÁVEIS DE CONTROLE
// =====================================================

unsigned long ultimoEnvio = 0;
unsigned long ultimaTentativaMQTT = 0;
unsigned long contador = 0;

// O DHT11 precisa de pelo menos 2 segundos entre leituras. 5 segundos é ideal.
const unsigned long INTERVALO_SENSORES = 5000; 
const unsigned long INTERVALO_RECONEXAO_MQTT = 5000;

// Aumentado o buffer para suportar a string JSON maior com Fahrenheit e Heat Index
#define MSG_BUFFER_SIZE 350
char msg[MSG_BUFFER_SIZE];

// =====================================================
// FUNÇÕES AUXILIARES - Mudar o código do Payload
// =====================================================

void apagarLeds() {
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    digitalWrite(LEDS[i], LOW);
  }
}

void controlarLed(char comando) {
  apagarLeds();

  switch (comando) {
    case '1':
      digitalWrite(4, HIGH);
      Serial.println("LED 1 -> GPIO 4 LIGADO");
      break;
    case '2':
      digitalWrite(18, HIGH);
      Serial.println("LED 2 -> GPIO 18 LIGADO");
      break;
    case '3':
      digitalWrite(19, HIGH);
      Serial.println("LED 3 -> GPIO 19 LIGADO");
      break;
    case '0':
      Serial.println("Todos os LEDs DESLIGADOS");
      break;
    default:
      Serial.println("Comando inválido. Use 0, 1, 2 ou 3.");
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
  
  if (length > 0) {
    char comando = (char)payload[0];
    Serial.println(comando);
    controlarLed(comando);
  } else {
    Serial.println("Payload vazio.");
  }
}

void reconnect() {
  if (!client.connected()) {
    unsigned long agora = millis();
    if (agora - ultimaTentativaMQTT >= INTERVALO_RECONEXAO_MQTT) {
      ultimaTentativaMQTT = agora;
      Serial.print("Tentando conexão MQTT...");
      
      String clientId = "ESP32Client-";
      clientId += String(random(0xffff), HEX);
      
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
  
  // Configuração dos Pinos dos LEDs
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    pinMode(LEDS[i], OUTPUT);
  }
  apagarLeds();

  // Configuração dos Pinos dos Sensores extras
  pinMode(SENSOR_CHUVA, INPUT);
  pinMode(SENSOR_MICROFONE, INPUT);

  // Inicializa o sensor DHT
  dht.begin();
  Serial.println("DHT Sensor Inicializado com Sucesso.");

  // Inicializa Wi-Fi e MQTT
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  // Mantém a conexão com o Broker ativa de forma não-bloqueante
  if (!client.connected()) {
    reconnect();
  } else {
    client.loop();
  }

  // Rotina periódica de leitura e envio (substitui o delay(2000) do loop original)
  unsigned long agora = millis();
  if (agora - ultimoEnvio >= INTERVALO_SENSORES) {
    ultimoEnvio = agora;
    contador++;

    // Leitura do sensor DHT
    float humidity = dht.readHumidity();
    float tempC = dht.readTemperature();
    float tempF = dht.readTemperature(true);

    // Leitura dos demais sensores do circuito
    int chuva = digitalRead(SENSOR_CHUVA);
    int som = digitalRead(SENSOR_MICROFONE);

    // Validação de dados do DHT
    if (isnan(humidity) || isnan(tempC) || isnan(tempF)) {
      Serial.println("Warning: Failed to read from DHT sensor! Check your wiring.");
      return; // Sai mais cedo se a leitura falhar para não enviar lixo
    }

    // Cálculo do Índice de Calor
    float heatIndexC = dht.computeHeatIndex(tempC, humidity, false);
    float heatIndexF = dht.computeHeatIndex(tempF, humidity);

    // Exibição local no Monitor Serial (Mantendo o padrão limpo do seu código)
    Serial.print("Contador: ");
    Serial.print(contador);
    Serial.print(" | Humidity: ");
    Serial.print(humidity, 1);
    Serial.print("% | Temp: ");
    Serial.print(tempC, 1);
    Serial.print("°C / ");
    Serial.print(tempF, 1);
    Serial.print("°F | Heat Index: ");
    Serial.print(heatIndexC, 1);
    Serial.print("°C / ");
    Serial.print(heatIndexF, 1);
    Serial.println("°F");

    // Formatação de string JSON completa para envio via MQTT
   snprintf(msg, MSG_BUFFER_SIZE, 
  "{\n"
  "  \"id\": %lu,\n"
  "  \"tempC\": %.1f,\n"
  "  \"tempF\": %.1f,\n"
  "  \"umid\": %.1f,\n"
  "  \"hiC\": %.1f,\n"
  "  \"hiF\": %.1f,\n"
  "  \"chuva\": %d,\n"
  "  \"som\": %d\n"
  "}", 
  contador, tempC, tempF, humidity, heatIndexC, heatIndexF, chuva, som
);


    // Envio dos dados estruturados para o Broker
    if (client.connected()) {
      Serial.print("Publicando no MQTT: ");
      Serial.println(msg);
      client.publish(topic_publish, msg);
    }
  }
}
