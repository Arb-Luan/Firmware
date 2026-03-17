# Serial IoT Gateway

A simple Serial-to-Cloud gateway for embedded device telemetry.

🇺🇸 English | 🇧🇷 [Versão em Português](README-PTBR.md)

A simple **Serial-to-Cloud gateway** that forwards telemetry data from an embedded device to the cloud.

This project demonstrates a basic IoT architecture where a microcontroller sends data via **serial communication**, and a Python script forwards that data to the **ThingSpeak IoT platform** using a REST API.

---

## Overview

In many IoT prototypes, microcontrollers may not have built-in internet connectivity.  
In this project, a **Python script acts as a gateway**, bridging the embedded device and the cloud.

Data flow:

```
Sensor / Button
      ↓
Arduino (Serial Output)
      ↓
Python Gateway Script
      ↓
ThingSpeak Cloud
```

---

## Technologies Used

- Python 3
- Serial Communication (pyserial)
- REST API
- Arduino
- ThingSpeak IoT Platform

---

## Requirements

Install the required Python libraries:

```bash
pip install pyserial requests
```

---

## Configuration

Edit the following variables in the script:

```python
API_KEY = "THINGSPEAK_API_KEY"
ARDUINO_PORT = "COMX"
BAUD_RATE = 9600
INTERVAL = 30
```

- `API_KEY` → Your ThingSpeak Write API Key  
- `ARDUINO_PORT` → Serial port used by the microcontroller  
- `BAUD_RATE` → Must match the Arduino serial configuration  
- `INTERVAL` → Time between cloud updates (seconds)

---

## Running the Gateway

Run the script:

```bash
python gateway.py
```

If the device sends serial data, the script will forward the telemetry to ThingSpeak.

Example output:

```
Connected to Arduino at COM5
Sent value: 1 | Response: 123456
```

---

## Example Use Case

This gateway can be used for simple IoT experiments such as:

- Button event logging
- Sensor monitoring
- Remote telemetry
- Embedded system prototyping

---

## Notes

This project was developed as part of experiments with **embedded systems and IoT communication**.

In the absence of a Wi-Fi module on the microcontroller, the computer acts as a **temporary IoT gateway**, forwarding serial data to the cloud.

---

## Future Improvements

- MQTT support
- Multi-sensor telemetry
- Data buffering
- Error handling improvements
---

## Project Status

Prototype

---

## 👨‍💻 Author

Luan Henrique  
Computer Engineering Student  
Embedded Systems Enthusiast  

Built for learning, experimentation, and embedded systems development.
