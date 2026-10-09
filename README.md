# Arduino Line-Following Robot

An Arduino Uno robot-car project that combines line following, obstacle avoidance, wall following, and free navigation. The active development baseline is Version 2, originally prepared for Unga Forskare.

## Project status

This repository is private and intended as an engineering portfolio project. Version 1 is retained as historical documentation. The firmware in `firmware/` is the current Version 2 development baseline.

## Demonstrated Version 2 behavior

- Follows a black line using three infrared sensors.
- Detects obstacles with three ultrasonic sensors.
- Chooses a side and follows a wall while bypassing an obstacle.
- Falls back to free navigation when the line is lost.
- Stops permanently when all three IR sensors detect the goal marker.

The original project poster and firmware are retained in this repository as source material. The code has not yet been revalidated on the current hardware after import.

## Repository map

```text
firmware/             Current Arduino firmware (Version 2 baseline)
docs/
  version-1/          Version 1 thesis and original prototype sketch
  version-2/          Version 2 poster and historical context
  development/        Workflow and future-development notes
  source-material/    Original source document for the Version 2 sketch
hardware/             Hardware notes and wiring documentation
tests/                Repeatable test plans and result logs
```

## Hardware represented by Version 2

- Arduino Uno
- Two DC motors
- L298N motor driver
- Three IR sensors
- Three ultrasonic sensors

Pin assignments and control parameters are documented directly in the Version 2 sketch. Confirm the wiring against the physical robot before powering it.

## Getting started

1. Open `firmware/LinjerobotV2/LinjerobotV2.ino` in the Arduino IDE.
2. Inspect the pin assignments and motor direction before uploading.
3. Start with the checks in `tests/README.md`.
4. Record outcomes before changing constants or behavior.
5. Use a branch for each improvement and merge only after the relevant tests pass.

## Portfolio note

Before making this repository public, review the archived report and poster for personal information such as names, email addresses, school branding, and photographs. Keep a private source archive and publish a redacted portfolio version if needed.

## How versions work here

Folders preserve the supplied historical material; Git preserves the development story from now on.

- `main` contains the latest working version of the robot.
- A **commit** is one small, named change, such as a sensor-calibration adjustment.
- A **branch** is a safe workspace for a change before it reaches `main`.
- A **tag** marks a stable milestone, for example `v2.1.0` after testing or `v3.0.0` for a substantial redesign.

The repository's Git history begins with this import. The original Version 1 sketch is preserved in `docs/version-1/firmware/`; the active Version 2 code is in `firmware/`. The historical source files are kept unchanged, while improvements happen only in the active firmware.
