# Development workflow

The robot combines hardware and software changes, so each change should include a short note about what was tested on the physical robot.

## Branches

- `main` holds the current project baseline.
- `develop` is where completed changes are combined and checked together.
- Short-lived branches are created from `develop` for one change and merged back through a pull request.

Use a short name that describes the work:

- `feature/ir-calibration` for a new capability or improvement;
- `fix/wall-following` for a correction; and
- `docs/wiring-guide` for documentation.

Branches represent work in progress, not permanent robot versions. Version 1 and Version 2 are recorded in the project files and Git history. When a tested state is ready to mark as a release, create a tag such as `v2.0.0`.

## A typical change

1. Describe the goal and a way to tell whether it worked. Use a GitHub issue for work that needs tracking or discussion.
2. Create a short-lived branch from `develop`.
3. Make one focused change.
4. Test the relevant behavior on the robot and add the result to `tests/`.
5. Open a pull request into `develop`. Include the reason for the change, what was tested, and what happened.
6. After related changes work together, open a pull request from `develop` to `main` to update the project baseline.

## Development milestones

1. Run and document the Version 2 baseline test plan.
2. Calibrate IR sensors and ultrasonic distance readings for the actual robot and course.
3. Add a checked wiring diagram and a parts list.
4. Consider a Version 3 redesign only when a specific goal calls for a larger architectural change.
