

# Serial IoT Gateway

Um gateway simples **Serial-para-Cloud** para telemetria de dispositivos embarcados.

🇺🇸 English | 🇧🇷 Versão em Português

Um gateway simples Serial-para-Cloud que encaminha dados de telemetria de um dispositivo embarcado para a nuvem.

Este projeto demonstra uma arquitetura básica de IoT onde um microcontrolador envia dados por **comunicação serial**, e um script em **Python** encaminha esses dados para a plataforma **ThingSpeak** utilizando uma **API REST**.

---

## Visão Geral

Em muitos protótipos de IoT, microcontroladores podem não possuir conectividade com a internet integrada.

Neste projeto, um **script em Python atua como gateway**, fazendo a ponte entre o dispositivo embarcado e a nuvem.

Fluxo de dados:

```
Sensor / Botão
      ↓
Arduino (Saída Serial)
      ↓
Script Python (Gateway)
      ↓
ThingSpeak Cloud
```

---

## Tecnologias Utilizadas

- Python 3  
- Comunicação Serial (pyserial)  
- REST API  
- Arduino  
- Plataforma IoT ThingSpeak  

---

## Requisitos

Instale as bibliotecas Python necessárias:

```bash
pip install pyserial requests
```

---

## Configuração

Edite as seguintes variáveis no script:

```python
API_KEY = "THINGSPEAK_API_KEY"
ARDUINO_PORT = "COMX"
BAUD_RATE = 9600
INTERVAL = 30
```

- **API_KEY** → Sua Write API Key do ThingSpeak  
- **ARDUINO_PORT** → Porta serial utilizada pelo microcontrolador  
- **BAUD_RATE** → Deve corresponder à configuração serial do Arduino  
- **INTERVAL** → Intervalo entre envios para a nuvem (segundos)

---

## Executando o Gateway

Execute o script:

```bash
python gateway.py
```

Se o dispositivo estiver enviando dados pela serial, o script encaminhará a telemetria para o ThingSpeak.

Exemplo de saída:

```
Connected to Arduino at COM5
Sent value: 1 | Response: 123456
```

---

## Exemplos de Uso

Este gateway pode ser utilizado em experimentos simples de IoT, como:

- Registro de eventos de botão  
- Monitoramento de sensores  
- Telemetria remota  
- Prototipagem de sistemas embarcados  

---

## Observações

Este projeto foi desenvolvido como parte de experimentos com **sistemas embarcados e comunicação IoT**.

Na ausência de um módulo Wi-Fi no microcontrolador, o computador atua como um **gateway IoT temporário**, encaminhando os dados da comunicação serial para a nuvem.

---

## Melhorias Futuras

- Suporte a MQTT  
- Telemetria com múltiplos sensores  
- Buffer de dados  
- Melhorias no tratamento de erros
---

## Status do Projeto

Protótipo

---

## 👨‍💻 Autor

Luan Henrique  
Estudante de Engenharia da Computação  
Entusiasta de Sistemas Embarcados  

Desenvolvido para aprendizado, experimentação e desenvolvimento em sistemas embarcados.
