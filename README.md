# Ground Reflection Mitigation System for Kongar UGV

This repository contains the embedded software implementation for mitigating Two-Ray Ground Reflection issues in Unmanned Ground Vehicles (UGVs). The project uses a **Space Diversity** approach with a single-receiver architecture to maintain link quality without increasing transmit power.

## Project Description
In low-height UGV operations (antenna height ~40 cm), ground reflections cause destructive interference, leading to signal nulls. This project implements a **Blind Switching Algorithm** on a Teensy 4.1 microcontroller to dynamically select the best antenna based on signal quality metrics.

## Hardware Configuration
* **Microcontroller:** Teensy 4.1
* **RF Switch:** PE4259 (SPDT, Low-power)
* **Telemetry:** 2.4 GHz Transceiver
* **Antenna Spacing:** $\lambda/2$ (approx. 6.25 cm)

## Algorithm Logic
The system operates on a "Single-Receiver Switched Diversity" principle:
1.  **Monitoring:** The system continuously monitors the Link Quality (RSSI combined with Packet Error Rate) of the active antenna.
2.  **Trigger:** If the quality drops below the threshold (-85 dBm), the system switches to the secondary antenna.
3.  **Validation:** It measures the signal on the new antenna. If the new signal is not significantly better (Hysteresis check), it reverts to the primary antenna to prevent instability.

## Sustainability & Performance Results
Field tests and log analysis demonstrated the following improvements:

* **Battery Efficiency:** +25% battery life extension by reducing retransmissions.
* **Data Throughput:** +23% effective throughput increase in live trials.
* **Power Consumption:** Switching logic is optimized to minimize CPU wake cycles (-40%).

## Pinout
* **Pin 14:** RF Switch Control (Output)
* **Pin 13:** Active Antenna Indicator (LED)
* **Pin A0:** RSSI Input (Analog)

---
**Student:** Cihan Erdem Gündoğdu
**Course:** Electromagnetic Waves
**Team:** Kongar Tank Team
