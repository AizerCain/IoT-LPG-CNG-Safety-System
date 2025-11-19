# 🔌 Circuit Schematics

This folder contains the circuit diagrams and wiring layouts for the Gas Leakage Detection System.

## Files Included
* `wiring_diagram.png`: A Visual Schematic diagram of connections.
* `circuit_diagram.png`: (To be added) Snapshot of the Fritzing/Tinkercad design.

## Logic Diagram

The following chart illustrates the high-level connection logic:

```mermaid
graph LR
    subgraph Power_System
    Ext_Power[External 5V 2A Source]
    end

    subgraph Sensors
    MQ6[MQ-6 Gas Sensor]
    end

    subgraph Output
    Buzz[Piezo Buzzer]
    end

    subgraph Communication
    GSM[GSM Module SIM900A]
    SIM[SIM Card]
    GSM --- SIM
    end

    subgraph Controller
    Ard[Arduino Uno]
    end

    %% Connections
    Ext_Power -- Power --> GSM
    Ext_Power -- GND (Common) --> Ard
    
    MQ6 -- Analog Signal (A0) --> Ard
    Ard -- Digital Signal (D8) --> Buzz
    Ard -- SoftwareSerial TX (D10) --> GSM
    GSM -- SoftwareSerial RX (D9) --> Ard
  ```

## Wiring Notes

1.  **Common Ground:** It is mandatory to connect the Ground (GND) of the external power supply to the Ground (GND) of the Arduino. Without this, the GSM module will not communicate.

2.  **GSM Power:** Do not power the GSM module directly from the Arduino's 5V pin; it cannot supply enough current during network registration.
