# Hardware Notes

## Overview

This document describes the hardware used in the Arduino-based line-following robot, including the main components, their functions, and the sensor configuration.

For the detailed electrical connections, refer to the schematic included in this directory.

## Bill of Materials (BOM)

| Component                   | Model / Specification |    Quantity | Function                                           |
| --------------------------- | --------------------- | ----------: | -------------------------------------------------- |
| Microcontroller             | Arduino Uno R3        |           1 | Processes sensor readings and controls the robot.  |
| Infrared sensor modules     | TCRT5000              |           3 | Detect the line using reflected infrared light.    |
| Ultrasonic distance sensors | HC-SR04               |           4 | Measure distances to nearby obstacles.             |
| Motor driver                | L298N                 |           1 | Controls the direction and speed of the DC motors. |
| DC motors                   | Model unspecified     |           2 | Drive the robot.                                   |
| Jumper wires                | Male-to-male          | As required | Connect electronic modules and components.         |
| Jumper wires                | Female-to-female      | As required | Connect electronic modules and components.         |
| Batteries                   | 9 V                   |           2 | Supply power to the robot's electrical system.     |
| Chassis                     | Model unspecified     |           1 | Provides the mechanical structure for the robot.   |

## Sensor Configuration

### Infrared Line Sensors

The robot uses three TCRT5000 sensor modules to detect the line. The modules provide electrical output signals that the Arduino can read.

The sensor readings are used by the control logic to determine the robot's position relative to the line and adjust motor movement accordingly.

### Ultrasonic Distance Sensors

The robot uses four HC-SR04 ultrasonic sensors for obstacle detection.

- **Front:** Two sensors
- **Left:** One sensor
- **Right:** One sensor

This arrangement allows the robot to detect obstacles in front of it and on either side.

## Motor Control

The L298N motor driver controls the two DC motors based on signals from the Arduino Uno R3. The driver handles the motor-side electrical load, while the Arduino provides the control signals.

## Power Supply

The robot uses two 9 V batteries. The exact battery connections and the distribution of power between the Arduino, sensors, and motor driver should be verified against the schematic.

The power supply must be able to provide sufficient current for the motors and electronics. Standard rectangular 9 V batteries can struggle to supply the current required by DC motors, so reliable operation depends on the actual wiring and load.

## Wiring and Schematic

The schematic is included in this directory and should be used as the primary reference for electrical connections.

It documents how the Arduino, sensors, motor driver, motors, and power supply are connected.


[View the schematics here:](./Linerobot-V2-Schematics.Ink)
