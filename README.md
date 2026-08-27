# HIL-Traffic-Controller-EVP
# Hardware-in-the-Loop (HIL) Traffic Signal Controller & EVP Simulator

Scaled 2-way Hardware-in-the-Loop (HIL) traffic controller model built on Arduino UNO, simulating real-time intersection safety management, non-blocking polling loops, and Emergency Vehicle Preemption (EVP) overrides.

---

## Key Technical Features
* **Active-LOW Relay Logic:** 4-channel relay actuation configured with internal pull-ups to prevent relay chatter and unsafe initialization states.
* **Non-Blocking Architecture:** Continuous 50 ms state polling avoiding blocking `delay()` functions, ensuring high-priority inputs are continuously sampled.
* **Emergency Vehicle Preemption (EVP):** Priority interlock logic that immediately drops active cross-traffic phases to restore main-thoroughfare green signals during an emergency call.
* **UART Telemetry:** Real-time diagnostics transmitted over 115200 Baud serial interface.

---

## Hardware Architecture & Pinout

| Peripheral | Pin / Line | Details |
| :--- | :--- | :--- |
| **Main Street Green** | Digital Pin 2 | Relay Channel 1 (Active-LOW) |
| **Main Street Red** | Digital Pin 3 | Relay Channel 2 (Active-LOW) |
| **Side Street Green** | Digital Pin 4 | Relay Channel 3 (Active-LOW) |
| **Side Street Red** | Digital Pin 5 | Relay Channel 4 (Active-LOW) |
| **Side Street Vehicle Sensor** | Digital Pin 7 | Pushbutton (`INPUT_PULLUP`) |
| **Emergency Preemption (EVP)** | Digital Pin 8 | Pushbutton (`INPUT_PULLUP`) |

---

## Diagnostic Output Sample

```text
================ SYSTEM INITIALIZATION ================
HIL Traffic Signal Controller online.
[STATE UPDATE] Main Street: GREEN | Side Street: RED
[INPUT] Vehicle detected on Side Street (Pin 7)
[STATE UPDATE] Main Street: RED | Side Street: GREEN
-------------------------------------------------------
[INTERRUPT] Emergency Vehicle Preemption (EVP) Detected!
[ACTION] Executing instant state priority restoration...
-------------------------------------------------------
[STATE UPDATE] Main Street: GREEN | Side Street: RED
  ```
  ---
  ## Media & Verification
  * **Demo Video:** [Watch Full System & Interlock Demo](https://drive.google.com/file/d/12j0f9mfA_pifQzWWQEPIqF2v0Z6EdmNC/view?usp=drivesdk)
