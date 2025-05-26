# 🏠 Smart Home System Based on STM32 and FreeRTOS

> A real-time embedded smart home system developed using STM32, FreeRTOS, and MQTT over ESP8266, enabling cloud-connected LED and button control with deterministic task scheduling.

## 📌 Project Overview

This project implements a real-time smart home control system on an **STM32** microcontroller running **FreeRTOS**, featuring:

- LED control
- Button press monitoring
- MQTT-based cloud communication (via **ESP8266**)
- Reliable cloud-to-device data transmission over **TCP/IP**

## 🛠 Tech Stack

- **Platform**: STM32 (ARM Cortex-M)
- **RTOS**: FreeRTOS
- **Communication**: MQTT over TCP/IP via ESP8266 Wi-Fi module
- **Cloud Provider**: Aliyun IoT Platform
- **Languages**: C / C++

---

## ✨ Key Features

- **Real-Time Task Scheduling**  
  Utilized FreeRTOS to implement isolated tasks for:
  - LED blinking based on cloud input
  - Button press detection with debouncing and duration tracking
  - Periodic MQTT data upload

- **Cloud Integration with MQTT**  
  - Connected to Aliyun IoT core using MQTT
  - Real-time remote LED control
  - Button press duration reports sent to cloud clients

- **Reliable Serial Communication**  
  - Identified and resolved data loss due to improper timeout handling
  - Enhanced cloud-to-device message reliability

---

## 🧪 System Architecture

