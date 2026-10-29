# kongar-UGV-Ground-Reflection-Mitigation

Switched antenna diversity sketch for Teensy 4.1 to mitigate two-ray ground reflection nulls on a low-height UGV link (2.4 GHz transceiver + PE4259 RF switch with half-wavelength antenna spacing).

## Overview

At ~40 cm antenna height, ground reflections cause destructive interference dips. `main.cpp` polls RSSI and packet error rate at 50 Hz (or 10 Hz when the link margin is high) and toggles the PE4259 SPDT switch (`Pin 14`) when the link score drops below `-85 dBm` with a `3 dB` hysteresis margin.

## Pinout

- `Pin 14`: PE4259 RF switch control output
- `Pin 13`: active antenna status LED
- `Pin A0`: analog RSSI input
