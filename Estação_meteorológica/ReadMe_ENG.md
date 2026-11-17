# ColMi — Sistema IoT de Monitoramento e Alerta Preventivo de Tempestades

**Sistema baseado em ESP32 para monitoramento de condições ambientais e identificação de possíveis atividades de tempestade.**

\<p align="center">   \<strong>IoT · Sistemas Embarcados · ESP32 · MQTT · Monitoramento Meteorológico\</strong> \</p>

---

## Sobre o Projeto

O ColMi é um projeto de sistemas embarcados e Internet das Coisas (IoT), desenvolvido para monitorar condições ambientais e identificar indicadores associados à aproximação ou ocorrência de tempestades.

Construído em torno do microcontrolador ESP32, o sistema integra diferentes sensores para coletar dados meteorológicos, processar sinais ambientais e transmitir informações por meio do protocolo MQTT.

O projeto possui três funções principais de monitoramento:

- **Detecção de chuva:** identifica a ocorrência de precipitação e estima sua intensidade utilizando um sensor analógico de chuva.
- **Monitoramento de umidade:** mede a umidade relativa do ar por meio de um sensor DHT11.
- **Detecção de trovões:** utiliza um módulo de microfone para detectar e contabilizar eventos acústicos associados a trovões.

A combinação dessas medições busca fornecer informações sobre as condições ambientais e contribuir para a identificação preventiva de situações meteorológicas potencialmente perigosas.

## Objetivos Principais

- Monitorar a temperatura e a umidade relativa do ar.
- Detectar a ocorrência de chuva e estimar sua intensidade.
- Identificar e contabilizar eventos acústicos associados a trovões.
- Transmitir as medições dos sensores utilizando MQTT.
- Fornecer alertas visuais locais quando determinadas condições forem atingidas.
- Desenvolver uma base para monitoramento remoto e sistemas de alerta de tempestades.

## Arquitetura do Sistema

```text
          SENSORES AMBIENTAIS
                    |
       +------------+------------+
       |            |            |
     DHT11      Sensor de      Microfone
                 Chuva
       |            |            |
       +------------+------------+
                    |
                  ESP32
                    |
            Processamento
                de Dados
                    |
                  Wi-Fi
                    |
             Broker MQTT
                    |
           Monitoramento Remoto
                    |
          Painel / Sistema de Alertas
```

## Componentes de Hardware

| Componente                | Função                                          |
| ------------------------- | ----------------------------------------------- |
| ESP32 DevKit              | Microcontrolador principal                      |
| DHT11                     | Medição de temperatura e umidade                |
| Sensor Analógico de Chuva | Detecção de chuva e estimativa de intensidade   |
| Módulo de Microfone       | Detecção acústica de trovões                    |
| LEDs                      | Indicadores visuais e alertas locais            |
| Servomotores (2x)         | Reservados para futuras aplicações de automação |

## Configuração dos Pinos

| Componente                  | GPIO do ESP32 |
| --------------------------- | ------------- |
| DHT11                       | GPIO 14       |
| Sensor de Chuva (Analógico) | GPIO 34       |
| Microfone                   | GPIO 27       |
| LED 1                       | GPIO 4        |
| LED 2                       | GPIO 18       |
| LED 3                       | GPIO 19       |
| Servo 1                     | GPIO 12       |
| Servo 2                     | GPIO 13       |
| LED Integrado               | GPIO 2        |

## Monitoramento de Chuva

O sensor analógico de chuva está conectado ao GPIO 34, permitindo que o ESP32 realize leituras das variações do sinal analógico.

O firmware converte essas leituras em uma escala estimada de intensidade entre 0 e 100%.

As condições de chuva são classificadas nas seguintes categorias:

| Intensidade Estimada | Classificação  |
| -------------------- | -------------- |
| 0%                   | Sem Chuva      |
| 1–29%                | Chuva Leve     |
| 30–69%               | Chuva Moderada |
| 70–100%              | Chuva Forte    |

Um alerta visual é ativado quando a intensidade estimada atinge ou ultrapassa o limite configurado de 60%.

*Observação: a porcentagem representa uma escala estimada do sensor, não uma medição meteorológica calibrada de precipitação em mm/h.*

## Monitoramento de Umidade e Temperatura

O sensor DHT11 realiza a coleta de dados de temperatura e umidade relativa do ar.

Esses parâmetros fornecem informações complementares sobre as condições ambientais e auxiliam na observação de mudanças meteorológicas.

As medições podem ser transmitidas para um broker MQTT, permitindo sua visualização remota e posterior análise histórica.

## Detecção de Trovões

O ColMi incorpora um módulo de microfone para monitorar a atividade acústica associada a tempestades.

As funcionalidades previstas para esse módulo incluem:

- Detectar eventos acústicos associados a trovões.
- Contabilizar os eventos detectados.
- Monitorar alterações na atividade acústica ao longo do tempo.
- Utilizar essas informações como indicadores complementares de atividade de tempestades.

A abordagem baseada em microfone exige processamento de sinais, filtragem de eventos e calibração para diferenciar trovões de ruídos ambientais comuns.

*Importante: a detecção acústica não mede diretamente os raios nem determina sua distância. Trata-se de um método indireto de monitoramento, não de um sistema certificado de detecção de descargas elétricas ou alerta meteorológico.*

## Comunicação MQTT

O ColMi utiliza o protocolo MQTT para transmissão sem fio de dados, por meio da biblioteca PubSubClient.

**Configuração do broker:**

- Broker: `test.mosquitto.org`
- Porta: `1883`
- Protocolo: MQTT
- Comunicação: Publicação / Assinatura (Publish / Subscribe)

### Tópicos Publicados

| Tópico MQTT                   | Descrição                          |
| ----------------------------- | ---------------------------------- |
| `ColMi/tempC`                 | Temperatura em graus Celsius       |
| `ColMi/chuva_intensidade_pct` | Intensidade estimada da chuva      |
| `ColMi/status_chuva`          | Classificação da condição de chuva |

### Assinatura

O ESP32 realiza a assinatura do seguinte tópico:

`ColMi/subscribe`

Esse tópico estabelece a base para futuras implementações de comandos remotos e controle de atuadores.

Tópicos adicionais para transmissão da umidade e dos eventos de trovão poderão ser incorporados conforme a evolução do firmware.

## Software e Tecnologias

O firmware é desenvolvido em C++ utilizando o framework Arduino.

**Principais tecnologias e bibliotecas:**

- **ESP32:** processamento embarcado e conectividade.
- **Arduino Framework:** desenvolvimento do firmware.
- **WiFi.h:** conexão com redes sem fio.
- **PubSubClient.h:** comunicação MQTT.
- **DHT.h:** aquisição de temperatura e umidade.
- **ESP32Servo.h:** controle de servomotores.

## Desenvolvimentos Futuros

As próximas etapas de desenvolvimento incluem:

- Implementação do processamento de sinais do microfone e contagem de trovões.
- Filtragem de ruídos ambientais.
- Transmissão dos dados de umidade via MQTT.
- Desenvolvimento de um painel para monitoramento em tempo real.
- Armazenamento histórico dos dados meteorológicos.
- Análise conjunta de chuva, umidade e atividade acústica.
- Configuração de limites para emissão de alertas.
- Controle remoto de atuadores por MQTT.
- Aprimoramento da calibração dos sensores.
- Operação autônoma utilizando energia solar.

## Aplicações do Projeto

O ColMi explora a utilização de sistemas embarcados e tecnologias IoT acessíveis para monitoramento ambiental e identificação de condições associadas a riscos meteorológicos.

Entre suas possíveis aplicações estão:

- Monitoramento meteorológico local.
- Observação de precipitação.
- Monitoramento de atividade de tempestades.
- Coleta de dados ambientais.
- Aplicações educacionais em sistemas embarcados e meteorologia.

## Informações Técnicas

| Atributo                    | Descrição                                                      |
| --------------------------- | -------------------------------------------------------------- |
| Projeto                     | ColMi                                                          |
| Plataforma                  | ESP32                                                          |
| Linguagem de Programação    | C++                                                            |
| Protocolo de Comunicação    | MQTT                                                           |
| Ambiente de Desenvolvimento | Arduino IDE                                                    |
| Aplicação                   | Monitoramento Meteorológico e Alerta Preventivo de Tempestades |

---

*ColMi — Conectando sistemas embarcados à inteligência ambiental.*
