# VESC CAN Communication Library (STM32 + HAL)

A lightweight and reusable **C++ CAN library for controlling VESC motor controllers**
using **STM32 (HAL CAN driver)** and **Extended CAN frames (29-bit ID)**.

This library provides high-level APIs to:
- Control VESC speed, current, duty cycle, and position
- Decode VESC status frames
- Integrate easily with STM32CubeIDE projects

---

## 📌 Features

- Written in **modern C++**
- Uses **STM32 HAL CAN**
- Supports **Extended CAN ID (29-bit)**
- Suitable for **robotics, EV, and motor control projects**
- Tested with **STM32F4 series**

---

## 🧩 Supported VESC Commands

- Set RPM
- Set Duty Cycle
- Set Motor Current
- Set Brake Current
- Set Handbrake Current
- Set Position

---

## 🏗️ CAN Frame Format (VESC)

VESC uses **Extended CAN Frames (29-bit ID)**.

### Extended ID Structure
```c
Bits 0–7 : Controller ID (0–255)
Bits 8–15 : Command ID
Bits 16–28 : Reserved

ExtId = (command << 8) | controller_id;
```
---
## 🔧 Hardware Requirements

- STM32 with CAN peripheral (e.g. STM32F4 series)
- CAN Transceiver (any one):
- SN65HVD230 (3.3V)
- TJA1050 (5V)
- MCP2551 (5V)
- Proper 120Ω termination resistor

---
## ⚙️ STM32 Configuration (CubeMX)

- CAN Mode: Normal
- Frame Type: Extended ID
- Enable: RX FIFO interrupt i.e. Auto retransmission
- Ensure same baud rate on all CAN nodes

