# HIL-Traffic-Controller-EVP
# Hardware-in-the-Loop (HIL) Traffic Signal Controller & EVP Simulator

Scaled 2-way Hardware-in-the-Loop (HIL) traffic controller model built on Arduino UNO, simulating intersection signal management, priority-based input polling, and Emergency Vehicle Preemption (EVP) overrides.

---

## Key Technical Features

* **Active-LOW Relay Logic:** 4-channel active-LOW relay control with defined startup states to establish a safe default traffic configuration during system initialization.

* **Priority-Based Input Polling:** Side-street vehicle and emergency preemption inputs are monitored through digital polling. During an active side-street cycle, the EVP input is checked every 100 ms to maintain rapid response to emergency requests.

* **Emergency Vehicle Preemption (EVP):** High-priority override logic that detects an EVP request and restores the main-street green / side-street red configuration, overriding an active side-street phase.

* **Traffic State Control:** Vehicle detection triggers a temporary side-street green phase before the controller automatically returns to the default main-street green state.

* **UART Telemetry:** Real-time diagnostic messages report system initialization, vehicle detection, traffic signal state changes, and EVP activation over a 115200 Baud serial interface.

---

## Hardware Architecture & Pinout

| Peripheral | Pin / Line | Details |
|---|---|---|
| Main Street Green | Digital Pin 2 | Relay Channel 1 (Active-LOW) |
| Main Street Red | Digital Pin 3 | Relay Channel 2 (Active-LOW) |
| Side Street Green | Digital Pin 4 | Relay Channel 3 (Active-LOW) |
| Side Street Red | Digital Pin 5 | Relay Channel 4 (Active-LOW) |
| Side Street Vehicle Sensor | Digital Pin 7 | Pushbutton (`INPUT_PULLUP`) |
| Emergency Preemption (EVP) | Digital Pin 8 | Pushbutton (`INPUT_PULLUP`) |

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
  * **Demo Video:** [Watch Full System & Interlock Demo](https://drive.google.com/file/d/15BhMp_JoopJyY_lupTLX_ianT7n03PK-/view?usp=drivesdk)
