# Arduino Line-Following Robot

This project follows the robot from its first obstacle-avoiding prototype to a line-following robot developed for Unga Forskare. Version 2 uses an Arduino Uno, three infrared sensors, and three ultrasonic sensors to follow a line, avoid obstacles, and navigate when the line is no longer detected.

The repository keeps the original Version 1 sketch and project documents alongside the Version 2 firmware, so the design can be studied and improved over time.

## What it does

The Version 2 sketch is organized as a state machine. It can:

- follow a black line using three IR sensors;
- detect an obstacle ahead and choose a side to pass it;
- follow a nearby wall while moving around an obstacle;
- switch to free navigation when the line disappears; and
- stop when all three IR sensors detect the goal marker.

These behaviors are described in the competition poster and implemented in the supplied sketch. The test plan lists expected behavior; it does not claim that every scenario has been re-tested on the current robot.

## Hardware

The Version 2 materials identify:

- Arduino Uno
- two DC motors and a motor driver
- three IR sensors
- three ultrasonic sensors

Pin assignments and control values are in the [Version 2 sketch](firmware/LinjerobotV2/LinjerobotV2.ino). Check the wiring and motor directions on the robot before uploading changes.

## Versions

- **Version 1** is preserved with its original sketch and high-school thesis in [`docs/version-1/`](docs/version-1/).
- **Version 2** is the line-following and obstacle-avoiding design. Its active firmware is in [`firmware/LinjerobotV2/`](firmware/LinjerobotV2/), and its poster is in [`docs/version-2/`](docs/version-2/).

Version 1's sketch is kept as historical source. New improvements belong in the active firmware.

## Getting started

1. Install the Arduino IDE.
2. Open `firmware/LinjerobotV2/LinjerobotV2.ino`.
3. Select Arduino Uno as the board and check that the pin definitions match the robot.
4. Upload and test in a clear area, with the robot raised or otherwise secured for initial motor checks.
5. Record results using the test plan in [`tests/README.md`](tests/README.md).

The firmware was imported from the supplied Version 2 code. A fresh hardware test should be recorded before treating the current behavior as a verified baseline.

## Project layout

```text
firmware/LinjerobotV2/   Active Arduino sketch
docs/version-1/          Version 1 sketch and thesis
docs/version-2/          Version 2 poster and notes
docs/development/        Development and branch workflow
docs/source-material/    Original Version 2 code document
hardware/                Hardware notes and wiring information
tests/                   Test plan and test-session records
```

## Contributing

Small, focused changes make it easier to understand how each adjustment affects the robot. For a change, create a branch such as `feature/ir-calibration`, test it on the robot, record what happened, and open a pull request with the change and test result. See [the development workflow](docs/development/WORKFLOW.md).
