<h1 align="center">🛢 PetroGuardian</h1>

<p align="center">
Intelligent Hydrocarbon Monitoring System for Industrial Safety
</p>

<p align="center">
🇺🇸 English | 🇧🇷 <a href="README_PT.md">Versão em Português</a>
</p>

<hr>

<h2>📌 Overview</h2>

<p>
<strong>PetroGuardian</strong> is an embedded system prototype designed to monitor hydrocarbon concentration levels and automatically react to potential leaks.
</p>

<p>
The system combines <strong>sensor data acquisition, signal filtering, predictive logic, and automated actuation</strong> to create a basic industrial safety monitoring solution.
</p>

<p>
Developed as a practical project during a technical training program, the prototype demonstrates fundamental concepts used in <strong>industrial monitoring systems, embedded firmware, and safety automation</strong>.
</p>

<hr>

<h2>⚙ System Architecture</h2>

<ul>
<li>Hydrocarbon sensor for analog concentration readings</li>
<li>Signal filtering using moving average</li>
<li>Trend detection for early leak prediction</li>
<li>Automated safety response</li>
<li>Human-machine interface using LCD display</li>
<li>Visual and audible alert system</li>
<li>Servo-controlled safety valve</li>
</ul>

<hr>

<h2>🧠 Embedded Intelligence</h2>

<p>
The system implements a simple predictive mechanism to detect potential leaks before reaching critical levels.
</p>

<p>
Key techniques used:
</p>

<ul>
<li>Moving average filtering (noise reduction)</li>
<li>Circular buffer data storage</li>
<li>Trend detection between sensor readings</li>
<li>Finite state machine for safety states</li>
</ul>

<p>
This allows the system to identify abnormal growth patterns in hydrocarbon concentration.
</p>

<hr>

<h2>🚨 Safety Logic</h2>

<table>
<tr>
<th>Status</th>
<th>Condition</th>
<th>System Response</th>
</tr>

<tr>
<td>SAFE</td>
<td>Low concentration</td>
<td>Valve open / Green LED</td>
</tr>

<tr>
<td>WARNING</td>
<td>Rising concentration or predictive detection</td>
<td>Partial restriction / Yellow LED</td>
</tr>

<tr>
<td>CRITICAL</td>
<td>High concentration</td>
<td>Emergency shutdown / Red LED + Buzzer</td>
</tr>

</table>

<hr>

<h2>🖥 Hardware Components</h2>

<ul>
<li>Arduino Uno</li>
<li>Hydrocarbon sensor (analog input)</li>
<li>Servo motor (valve control)</li>
<li>LCD Display I2C (16x2)</li>
<li>Buzzer</li>
<li>3 Status LEDs</li>
</ul>

<hr>

<h2>📊 System Features</h2>

<ul>
<li>Real-time hydrocarbon concentration monitoring</li>
<li>Noise filtering using moving average</li>
<li>Leak prediction through trend detection</li>
<li>Automated valve control</li>
<li>Visual alert system (LED indicators)</li>
<li>Audible alarm for critical conditions</li>
<li>LCD interface displaying system status</li>
</ul>

<hr>

<h2>🧩 Firmware Concepts Demonstrated</h2>

<ul>
<li>Analog sensor acquisition</li>
<li>Signal processing</li>
<li>Circular buffer implementation</li>
<li>State machine logic</li>
<li>Hardware abstraction</li>
<li>Embedded safety control</li>
</ul>

<hr>

<h2>📈 Future Improvements</h2>

<ul>
<li>ESP32 integration for remote monitoring</li>
<li>Cloud data logging</li>
<li>Graphical dashboard for system analytics</li>
<li>Machine learning model for advanced leak prediction</li>
<li>Industrial-grade sensor calibration</li>
</ul>

<hr>

<h2>📷 Prototype</h2>

<img width="771" height="480" alt="image" src="https://github.com/user-attachments/assets/6bbfc0fc-c34b-4c0c-920e-152f623d0c91" />
<img width="478" height="514" alt="image" src="https://github.com/user-attachments/assets/ee0aa6d4-f51e-42f1-82a6-e1c99d348dda" />

<p align="center">
<em>PetroGuardian embedded monitoring prototype</em>
</p>

<hr>

<h2>👨‍💻 Author</h2>

<p>
<strong>Luan Henrique</strong><br>
Computer Engineering Student<br>
Embedded Systems Enthusiast
</p>

<hr>

<p align="center">
Built for learning, experimentation and embedded systems development.
</p>
