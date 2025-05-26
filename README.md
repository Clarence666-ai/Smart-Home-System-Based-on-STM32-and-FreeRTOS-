# 🏠 Smart Home Embedded Firmware (STM32 + FreeRTOS)

This repository contains a modular embedded firmware for a smart home automation system based on STM32 microcontrollers and FreeRTOS. It enables real-time control of LEDs and button inputs, as well as cloud interaction via MQTT over ESP8266 Wi-Fi.

## 📂 Directory Structure

| Folder       | Description                                             |
|--------------|---------------------------------------------------------|
| `app/`       | Application logic (LED control, button monitoring)      |
| `device/`    | Device abstraction and peripheral interfaces            |
| `protocol/`  | MQTT protocol and message handling                      |
| `middleware/`| Middleware integrations, e.g., Aliyun IoT SDK           |
| `platform/`  | Platform-specific macros and configurations             |
| `modules/`   | Drivers for external components (e.g., Wi-Fi modules)   |
| `hal/`       | Hardware Abstraction Layer (based on STM32 HAL)        |
| `core/`      | FreeRTOS tasks, scheduler setup, and system init        |
| `project/`   | STM32CubeMX, Keil uVision, or IAR project files         |
| `docs/`      | Design documents, architecture diagrams, etc.           |

## 🚀 Features

- Real-time LED and button handling using FreeRTOS tasks
- Cloud communication via MQTT protocol (Aliyun IoT Core)
- Remote LED control and button state reporting
- Reliable serial communication via ESP8266 (UART + AT commands)
- Bug fixes for timeout issues and data loss handling

## 🧰 Development Environment

- **MCU**: STM32F1/F4 (Cortex-M series)
- **RTOS**: FreeRTOS 10.x
- **Network**: ESP8266 Wi-Fi module (AT firmware)
- **IDE**: STM32CubeMX / Keil uVision / IAR / VSCode + GCC
- **Language**: C / C++

## 📡 MQTT Topics

- **Subscribe**: `/device/led/control`
- **Publish**: `/device/button/status`

## 📝 License

This project is licensed under the MIT License.
