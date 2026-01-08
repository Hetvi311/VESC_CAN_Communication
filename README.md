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

---
## 🔧 Debugging Steps:

- Check baudrate is same or not from both transmitting and receiving side.
- To set baudrate, you have to configure prescaler, TIM_SEGMENT_1 and TIM_SEGMENT_2 according to desired baudrate.
- Check which FIFO0 and FIFO1 is used in receiving side code and which Rx0 or Rx1 interrupt is enabled in IOC, as Rx0 should  be for FIFO0 and Rx1 should be for FIFO1.
- Auto retransmission should be enabled from transmitting side as Enabling Auto Retransmission in CAN communication is crucial because it ensures that messages are reliably delivered even in the presence of errors or bus contention.
- Transmitting and receiving side StdId should be same and between 0x000 and 0x7FF.
- Check hardware for data is transmitting or not, check voltage on CANH and CANL there should be 2V difference.
- Check resistance between CANH and CANL that it is 120 ohm.
- Check how much voltage you are giving to module, according to the IC and module should be given 5V.

---
A detailed explanation of **CAN protocol and VESC CAN communication** is provided in the PDF below:

📄 **[CAN Communication Details](CAN_COMMUNICATION.pdf)**
