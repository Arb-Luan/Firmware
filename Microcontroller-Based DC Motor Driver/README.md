<h1>Low-Side DC Motor Driver</h1>

<hr>
<img width="1015" height="539" alt="image" src="https://github.com/user-attachments/assets/5ac15fff-d0b1-4058-b133-46b89d312562" />


<h2>🇧🇷 Português</h2>

<h3>📖 Visão Geral</h3>
<p>
Este projeto demonstra o controle de um motor DC utilizando uma porta GPIO de um microcontrolador
e um transistor NPN configurado como chave low-side. Um botão é responsável por acionar
simultaneamente o motor e um LED de status.
</p>

<h3>🛠 Arquitetura de Hardware</h3>
<ul>
  <li><b>Microcontrolador:</b> Arduino Uno</li>
  <li><b>Entrada:</b> Botão (INPUT_PULLUP)</li>
  <li><b>Saídas:</b>
    <ul>
      <li>LED de status</li>
      <li>Motor DC (via transistor NPN)</li>
    </ul>
  </li>
  <li><b>Topologia:</b> Chaveamento Low-Side</li>
</ul>

<h3>⚡ Considerações Elétricas</h3>
<ul>
  <li>Transistor utilizado como chave eletrônica para acionamento de carga indutiva.</li>
  <li>Separação entre estágio lógico (microcontrolador) e estágio de potência (motor).</li>
  <li>Recomendado: Diodo flyback em paralelo com o motor para proteção contra back-EMF.</li>
  <li>Uso de resistor de pull-up interno para evitar estado flutuante na entrada.</li>
</ul>

<h3>🧠 Lógica do Sistema</h3>
<p>
O sistema monitora continuamente o estado do botão.
Quando pressionado, o motor e o LED são acionados.
Quando liberado, ambos são desligados.
</p>

<hr>

<h2>🇺🇸 English</h2>

<h3>📖 Overview</h3>
<p>
This project demonstrates the control of a DC motor using a microcontroller GPIO pin
and an NPN transistor configured as a low-side switch. A push button activates
both the motor and a status LED.
</p>

<h3>🛠 Hardware Architecture</h3>
<ul>
  <li><b>Microcontroller:</b> Arduino Uno</li>
  <li><b>Input:</b> Push Button (INPUT_PULLUP)</li>
  <li><b>Outputs:</b>
    <ul>
      <li>Status LED</li>
      <li>DC Motor (via NPN transistor)</li>
    </ul>
  </li>
  <li><b>Topology:</b> Low-Side Switching</li>
</ul>

<h3>⚡ Electrical Design Notes</h3>
<ul>
  <li>Transistor used as an electronic switch to drive an inductive load.</li>
  <li>Logical control stage separated from power stage.</li>
  <li>Recommended: Flyback diode across motor terminals to suppress back-EMF.</li>
  <li>Internal pull-up resistor used to avoid floating input states.</li>
</ul>

<h3>🧠 System Logic</h3>
<p>
The system continuously monitors the button state.
When pressed, the motor and LED are activated.
When released, both outputs are turned off.
</p>

<hr>

<h3>📈 Possible Improvements | Possíveis Melhorias</h3>
<ul>
  <li>PWM speed control | Controle de velocidade via PWM</li>
  <li>Software debounce | Implementação de debounce por software</li>
  <li>Interrupt-based input handling | Uso de interrupções externas</li>
  <li>Finite State Machine architecture | Arquitetura com Máquina de Estados</li>
  <li>Current monitoring for diagnostics | Monitoramento de corrente do motor</li>
</ul>

<h3>🎯 Key Concepts | Conceitos Aplicados</h3>
<ul>
  <li>GPIO configuration</li>
  <li>Digital input handling</li>
  <li>Transistor-based load driving</li>
  <li>Inductive load control</li>
  <li>Embedded firmware structuring</li>
</ul>
