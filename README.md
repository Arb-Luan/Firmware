<h1 align="center">🌱 Estufa Inteligente com Arduino</h1>
📌 Descrição do Projeto:

Este projeto simula o controle de uma estufa de hortaliças, utilizando um Arduino Uno no simulador Tinkercad.
O sistema monitora a temperatura do ambiente e atua automaticamente para ventilação e alerta de emergência, garantindo condições adequadas para o cultivo.

O controle é feito por meio de sensor de temperatura, motor (ventilador), LED e buzzer, todos integrados em um circuito eletrônico simples e funcional.


Componentes Utilizados

Arduino Uno

Sensor de temperatura TMP36

Motor DC (simulando ventilador)

Transistor NPN (acionamento do motor)

LED vermelho + resistor

Buzzer

Capacitor de desacoplamento (100 nF)

Protoboard e jumpers

<h3 align="center">🔧 Funcionalidades Implementadas</h3>

O sistema executa automaticamente as seguintes ações:

(a) Leitura de Temperatura

A temperatura ambiente é lida continuamente através do sensor TMP36, utilizando o conversor analógico-digital (ADC) do Arduino.

(b) Controle de Ventilação

Quando a temperatura atinge ou ultrapassa 30 °C, o motor é acionado, simulando um ventilador para resfriamento da estufa.

(c) Alerta de Emergência

Caso a temperatura ultrapasse 50 °C:

Um LED vermelho é acionado;

Uma buzina (buzzer) emite um sinal sonoro de alerta, indicando situação crítica.
<h3 align="center">🧠 Lógica de Controle</h3>

O sistema possui dois níveis de atuação térmica:

Nível de controle: ventilação automática a partir de 30 °C;

Nível de emergência: alerta visual e sonoro acima de 50 °C.

O motor é acionado via transistor NPN, evitando sobrecarga nos pinos do Arduino.

O código foi desenvolvido em linguagem C, conforme o padrão da plataforma Arduino.

<h3 align="center">🖥️ Ambiente de Desenvolvimento</h3>

Simulação realizada no Tinkercad
👉 https://www.tinkercad.com/things/lywodr7Kr1l-sirene-dio?sharecode=NUsGYMeGXiEaEond23amMLXYplEiKYPxHOb20I2Mt3Y

Programação em Arduino C/C++

⚠️ Observação: algumas adaptações foram feitas para compatibilidade com o simulador. Em uma implementação real, recomenda-se o uso de fonte externa para o motor e diodo de flyback.

🎯 Objetivo Educacional

Este projeto tem como objetivo consolidar conceitos de:

Sistemas embarcados com Arduino

Leitura de sensores analógicos

Controle de atuadores

Interface entre lógica digital e potência

Depuração de hardware e software em conjunto
