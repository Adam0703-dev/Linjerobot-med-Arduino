# Test plan and results

Use this folder for repeatable checks of the active Version 2 firmware. Do not treat a code upload as a successful test; record the observed behavior and any hardware changes.

## Baseline checks

| ID | Scenario | Expected behavior | Result |
| --- | --- | --- | --- |
| T01 | Start on a line | Robot enters line-following mode | Not run |
| T02 | Start off the line | Robot enters free-navigation mode | Not run |
| T03 | Left or right IR sensor detects line | Robot corrects toward the line | Not run |
| T04 | Obstacle in front while on a line | Robot stops, selects a wall side, and bypasses the obstacle | Not run |
| T05 | Center IR sensor redetects line during wall following | Robot returns to line following | Not run |
| T06 | Line disappears | Robot switches to free navigation | Not run |
| T07 | Object is too close in free navigation | Robot backs up and rotates | Not run |
| T08 | All IR sensors detect the goal marker | Robot stops and remains stopped | Not run |

## Test-log template

Create one Markdown file per test session, for example `2026-10-09-baseline.md`.

```markdown
# Baseline test - YYYY-MM-DD

## Setup
- Firmware commit:
- Battery / power setup:
- Surface and line material:
- Sensor placement or calibration notes:

## Results
| Test ID | Pass / fail | Observation | Follow-up |
| --- | --- | --- | --- |
| T01 | | | |
```

