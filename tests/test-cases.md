
# Test Cases

## 1. Sensor Tests

### SEN-01 — Line Sensor Response

**Objective:** Verify that the three TCRT5000 sensor modules respond to the line and surrounding surface.

**Procedure:**

1. Place the robot over the test line.
2. Observe the readings from all three sensors.
3. Move the sensors over the line and the surrounding surface.
4. Compare the readings.

**Expected Result:** The sensor readings change in a way that allows the firmware to distinguish the line from the surrounding surface.

**Acceptance Criteria:** All three sensors produce readings that the firmware can use for line detection.

**Status:** Not tested

### SEN-02 — Ultrasonic Sensor Response

**Objective:** Verify that all four HC-SR04 sensors detect nearby obstacles.

**Procedure:**

1. Test each sensor individually.
2. Place an obstacle in front of the sensor at a measured distance.
3. Compare the measured distance with the actual distance.
4. Repeat at several distances within the intended operating range.

**Expected Result:** Each sensor returns usable distance measurements.

**Acceptance Criteria:** Each sensor detects obstacles within the robot's intended operating range with an error below a tolerance defined before testing.

**Status:** Not tested

## 2. Motor Tests

### MOT-01 — Motor Direction

**Objective:** Verify that both DC motors respond correctly to the firmware's motor commands.

**Procedure:**

1. Secure the robot so that its wheels can rotate without driving away.
2. Command forward movement.
3. Observe both motors.
4. Repeat for reverse movement and turning commands, where implemented.

**Expected Result:** The motors respond in the intended directions.

**Acceptance Criteria:** Each tested command produces the expected motor response.

**Status:** Not tested

## 3. Navigation Tests

### NAV-01 — Straight Line Following

**Objective:** Evaluate the robot's ability to follow a straight line.

**Procedure:**

1. Place the robot at a defined starting position.
2. Run the firmware on a straight test track.
3. Observe whether the robot follows the line.
4. Repeat the test under the same conditions.

**Expected Result:** The robot follows the line without losing track of it.

**Acceptance Criteria:** The robot completes the defined track without losing the line in the required number of trials.

**Status:** Not tested

### NAV-02 — Curve Following

**Objective:** Evaluate line tracking on a curved section.

**Procedure:**

1. Place the robot at the start of a defined curved track.
2. Run the firmware.
3. Record whether the robot follows the curve or loses the line.

**Expected Result:** The robot follows the curve within the defined track boundaries.

**Acceptance Criteria:** The robot completes the curve in the required number of trials.

**Status:** Not tested

## 4. Obstacle Avoidance Tests

### OBS-01 — Front Obstacle Detection

**Objective:** Verify that the front ultrasonic sensors detect an obstacle.

**Procedure:**

1. Place an obstacle in front of the robot.
2. Run the firmware.
3. Observe the sensor readings and the robot's response.
4. Repeat with the obstacle at different distances.

**Expected Result:** The robot detects an obstacle according to the programmed detection threshold.

**Acceptance Criteria:** The obstacle is detected at the intended threshold under the test conditions.

**Status:** Not tested

### OBS-02 — Obstacle Avoidance and Line Recovery

**Objective:** Evaluate the complete obstacle-avoidance sequence.

**Procedure:**

1. Place the robot on a track with a line and a defined obstacle.
2. Start the robot at a repeatable position.
3. Observe detection, maneuvering, and line recovery.
4. Record whether the robot completes the sequence.

**Expected Result:** The robot detects the obstacle, executes its programmed avoidance maneuver, and attempts to reacquire the line.

**Acceptance Criteria:** The robot completes the entire sequence successfully in the required number of trials.

**Status:** Not tested

## 5. Regression Tests

### REG-01 — Core Functionality After Firmware Changes

**Objective:** Verify that changes to the firmware do not break previously working behavior.

**Procedure:**

1. Run the relevant sensor tests.
2. Run the straight-line test.
3. Run the obstacle-detection test.
4. Run the obstacle-avoidance test where applicable.
5. Compare the results with previous test records.

**Expected Result:** Previously working behavior remains functional.

**Acceptance Criteria:** All tests relevant to the firmware change pass.

**Status:** Not tested
