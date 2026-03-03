<h1>LED Random Selector</h1>
<img width="939" height="601" alt="image" src="https://github.com/user-attachments/assets/6c080aa6-bcbe-4ceb-97f4-9d865faa04f8" />


<p>
Projeto de firmware utilizando Arduino para controle de múltiplas saídas digitais
com geração pseudoaleatória.
</p>

<h3>📌 Descrição</h3>

<p>O sistema consiste em:</p>

<ul>
  <li>6 LEDs conectados a pinos digitais</li>
  <li>1 botão configurado com <code>INPUT_PULLUP</code></li>
  <li>Seleção aleatória de um LED ao pressionar o botão</li>
</ul>

<p>
Ao detectar o pressionamento, todos os LEDs são desligados e apenas um é acionado,
escolhido via função <code>random()</code>.
</p>

<p>
O foco do projeto é consolidar fundamentos de sistemas embarcados e organização de firmware.
</p>

<h3>🛠️ Conceitos Trabalhados</h3>

<ul>
  <li>Manipulação de múltiplos GPIOs via vetor</li>
  <li>Leitura de entrada digital com pull-up interno</li>
  <li>Estruturação de função dedicada</li>
  <li>Uso de <code>randomSeed()</code> para reduzir previsibilidade</li>
  <li>Separação clara entre <code>setup()</code> e <code>loop()</code></li>
</ul>

<h3>🔌 Hardware Utilizado</h3>

<ul>
  <li>Arduino Uno</li>
  <li>6 LEDs</li>
  <li>6 resistores</li>
  <li>1 botão</li>
  <li>Protoboard</li>
  <li>Jumpers</li>
</ul>

<h3>📂 Estrutura do Projeto</h3>

<pre>
/firmware
    main.ino
</pre>

<h3>🚀 Próximas Melhorias</h3>

<ul>
  <li>Implementação de debounce adequado</li>
  <li>Substituição de <code>delay()</code> por controle não bloqueante com <code>millis()</code></li>
  <li>Efeito visual de roleta antes do resultado final</li>
  <li>Modularização do código</li>
</ul>

<h3>🎯 Objetivo</h3>

<p>
Reforçar fundamentos de firmware e controle de hardware com organização, clareza de lógica
e boas práticas iniciais em sistemas embarcados.
</p>
