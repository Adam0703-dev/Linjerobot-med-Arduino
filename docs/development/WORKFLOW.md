# Development workflow

## Scope

Version 1 is an archive. Version 2 is the current development baseline. A future Version 3 should be created only when its goal requires a deliberate architectural break rather than an incremental Version 2 improvement.

## Day-to-day workflow

1. Create an issue describing the behavior to improve and how success will be measured.
2. Create a branch named after the change, for example `feature/sensor-calibration` or `fix/wall-following-turn`.
3. Make the smallest focused firmware or hardware-documentation change.
4. Run the relevant tests from `tests/README.md` and write a session log.
5. Open a pull request that states the test result, hardware configuration, and any known limitation.
6. Merge only after the behavior is repeatable.

## Suggested next milestones

1. Establish a documented Version 2 baseline on the current physical robot.
2. Calibrate IR thresholds and ultrasonic distance behavior for the current track and environment.
3. Separate sensor reading, movement control, and state transitions into smaller modules if the sketch becomes difficult to change safely.
4. Add a wiring diagram, parts list, photographs, and a short demonstration video for the portfolio version.

## Version policy

- Keep compatible improvements in `versions/v2`.
- Tag a stable, tested state as `v2.x`.
- Start `versions/v3` only for a redesign with its own documented goal and migration notes.

