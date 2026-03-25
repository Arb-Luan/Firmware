<!DOCTYPE html>
<html lang="pt-BR">

<head>
<meta charset="UTF-8">
<title>PetroGuardian</title>
</head>

<body>

<h1 align="center">🛢 PetroGuardian</h1>

<p align="center">
Sistema Inteligente de Monitoramento de Hidrocarbonetos para Segurança Industrial
</p>

<p align="center">
🇧🇷 Português | 🇺🇸 <a href="README_EN.md">English Version</a>
</p>

<hr>

<h2>📌 Visão Geral</h2>

<p>
O <strong>PetroGuardian</strong> é um protótipo de sistema embarcado desenvolvido para monitorar níveis de concentração de hidrocarbonetos e reagir automaticamente a possíveis vazamentos.
</p>

<p>
O sistema combina <strong>aquisição de dados de sensores, filtragem de sinal, lógica preditiva e atuação automática</strong> para criar uma solução básica de monitoramento de segurança industrial.
</p>

<p>
Desenvolvido como projeto prático durante um programa de formação técnica, o protótipo demonstra conceitos fundamentais utilizados em <strong>sistemas de monitoramento industrial, firmware embarcado e automação de segurança</strong>.
</p>

<hr>

<h2>⚙ Arquitetura do Sistema</h2>

<ul>
<li>Sensor de hidrocarbonetos para leitura analógica de concentração</li>
<li>Filtragem de sinal utilizando média móvel</li>
<li>Detecção de tendência para previsão antecipada de vazamentos</li>
<li>Resposta automática de segurança</li>
<li>Interface homem-máquina utilizando display LCD</li>
<li>Sistema de alerta visual e sonoro</li>
<li>Controle de válvula de segurança através de servo motor</li>
</ul>

<hr>

<h2>🧠 Inteligência Embarcada</h2>

<p>
O sistema implementa um mecanismo simples de detecção preditiva para identificar possíveis vazamentos antes que os níveis se tornem críticos, pronpondo assim evitar acidentes.
</p>

<p><strong>Técnicas utilizadas:</strong></p>

<ul>
<li>Filtragem por média móvel (redução de ruído)</li>
<li>Armazenamento de dados em buffer circular</li>
<li>Detecção de tendência entre leituras consecutivas</li>
<li>Máquina de estados finita para controle do sistema</li>
</ul>

<p>
Isso permite ao sistema identificar padrões anormais de crescimento na concentração de hidrocarbonetos.
</p>

<hr>

<h2>🚨 Lógica de Segurança</h2>

<table border="1" cellpadding="8">

<tr>
<th>Status</th>
<th>Condição</th>
<th>Resposta do Sistema</th>
</tr>

<tr>
<td>SEGURO</td>
<td>Baixa concentração</td>
<td>Válvula aberta / LED verde</td>
</tr>

<tr>
<td>ALERTA</td>
<td>Aumento de concentração ou detecção preditiva</td>
<td>Restrição parcial / LED amarelo</td>
</tr>

<tr>
<td>CRÍTICO</td>
<td>Alta concentração</td>
<td>Fechamento de emergência / LED vermelho + buzzer</td>
</tr>

</table>

<hr>

<h2>🖥 Componentes de Hardware</h2>

<ul>
<li>Arduino Uno</li>
<li>Sensor de hidrocarbonetos (entrada analógica)</li>
<li>Servo motor (controle da válvula)</li>
<li>Display LCD I2C (16x2)</li>
<li>Buzzer</li>
<li>3 LEDs de status</li>
</ul>

<hr>

<h2>📊 Funcionalidades do Sistema</h2>

<ul>
<li>Monitoramento em tempo real da concentração de hidrocarbonetos</li>
<li>Filtragem de ruído utilizando média móvel</li>
<li>Previsão de vazamento através de detecção de tendência</li>
<li>Controle automático de válvula de segurança</li>
<li>Sistema de alerta visual com LEDs</li>
<li>Alarme sonoro para condições críticas</li>
<li>Interface LCD exibindo dados e status do sistema</li>
</ul>

<hr>

<h2>🧩 Conceitos de Firmware Demonstrados</h2>

<ul>
<li>Aquisição de sensores analógicos</li>
<li>Processamento e filtragem de sinais</li>
<li>Implementação de buffer circular</li>
<li>Lógica de máquina de estados</li>
<li>Abstração de hardware</li>
<li>Controle de segurança em sistemas embarcados</li>
</ul>

<hr>

<h2>📈 Melhorias Futuras</h2>

<ul>
<li>Integração com ESP32 para monitoramento remoto</li>
<li>Registro de dados em nuvem</li>
<li>Dashboard gráfico para análise do sistema</li>
<li>Modelo de machine learning para previsão avançada de vazamentos</li>
<li>Calibração com sensores industriais reais</li>
</ul>

<hr>

<h2>📷 Protótipo</h2>

<p align="center">
<img width="771" src="https://github.com/user-attachments/assets/6bbfc0fc-c34b-4c0c-920e-152f623d0c91">
</p>

<p align="center">
<img width="478" src="https://github.com/user-attachments/assets/ee0aa6d4-f51e-42f1-82a6-e1c99d348dda">
</p>

<p align="center">
<em>Protótipo embarcado do sistema PetroGuardian</em>
</p>

<hr>

<h2>👨‍💻 Autor</h2>

<p>
<strong>Luan Henrique</strong><br>
Estudante de Engenharia da Computação<br>
Foco em Sistemas Embarcados
</p>

<hr>

<p align="center">
Projeto desenvolvido para aprendizado, experimentação e desenvolvimento em sistemas embarcados.
</p>

</body>
</html>
