# Testing

## Overview

This directory contains the test cases and test records used to evaluate the Arduino-based line-following robot.

Testing is primarily performed on the physical robot. The purpose is to verify that the firmware behaves as expected and to identify problems before introducing further changes.

## Testing Approach

Tests are performed incrementally, starting with individual components and progressing to complete robot behavior.

The testing process includes:

1. **Sensor testing:** Verify that the infrared and ultrasonic sensors produce usable readings.
2. **Motor testing:** Verify motor direction and response to control signals.
3. **Line-following tests:** Evaluate the robot's ability to follow straight lines and curves.
4. **Obstacle-detection tests:** Check obstacle detection from the front and sides.
5. **Obstacle-avoidance tests:** Evaluate the robot's ability to maneuver around obstacles and return to the line.
6. **Regression testing:** Repeat previously successful tests after firmware changes to check that existing functionality still works.

## Test Documentation

Test cases and their acceptance criteria are documented in [`test-cases.md`](./test-cases.md).

Actual test runs, observations, and results are recorded in [`test-log`](./test-log/)

A test is marked as passed only when its acceptance criteria have been met. Tests that have not been performed are marked as not tested.

## Test Environment

The robot is built around an Arduino Uno R3 and uses:

- 3 × TCRT5000 infrared sensor modules
- 4 × HC-SR04 ultrasonic distance sensors
- 1 × L298N motor driver
- 2 × DC motors

For the complete hardware configuration, see [Hardware Notes](../hardware/).

## Development Workflow

When making changes to the firmware:

1. Identify the behavior being changed.
2. Define or select a relevant test case.
3. Run the test and record the result.
4. Investigate failures and make corrections.
5. Repeat relevant tests to check for regressions.

Testing results should reflect observed behavior rather than assumed functionality.
