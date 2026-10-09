// Version 2 baseline imported from the original source document.
// Validate wiring and behavior on the physical robot before use.

enum RobotState {
  LINE_FOLLOW,
  OBSTACLE_DETECTED,
  WALL_FOLLOW,
  FREE_NAVIGATION,
  STOPPED
};

RobotState state = FREE_NAVIGATION;

// Motor pins
#define IN1 10
#define IN2 11
#define IN3 12
#define IN4 13
#define ENA 5
#define ENB 6

// IR sensors
#define IR_LEFT A0
#define IR_CENTER A1
#define IR_RIGHT A2

// Ultrasonic sensors
#define TRIG_FRONT 2
#define ECHO_FRONT 3
#define TRIG_LEFT 4
#define ECHO_LEFT 7
#define TRIG_RIGHT 8
#define ECHO_RIGHT 9

int baseSpeed = 140;
int obstacleThreshold = 15;
int emergencyDistance = 10;
int wallTarget = 10;
float Kp = 8.0;

bool followLeftWall = true;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IR_LEFT, INPUT);
  pinMode(IR_CENTER, INPUT);
  pinMode(IR_RIGHT, INPUT);

  pinMode(TRIG_FRONT, OUTPUT);
  pinMode(ECHO_FRONT, INPUT);
  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);
  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);

  Serial.begin(9600);
  delay(3000);

  if (digitalRead(IR_LEFT) == LOW || digitalRead(IR_CENTER) == LOW || digitalRead(IR_RIGHT) == LOW) {
    state = LINE_FOLLOW;
  } else {
    state = FREE_NAVIGATION;
  }
}

void loop() {
  switch (state) {
    case LINE_FOLLOW:
      lineFollow();
      break;
    case OBSTACLE_DETECTED:
      decideWallSide();
      break;
    case WALL_FOLLOW:
      wallFollow();
      break;
    case FREE_NAVIGATION:
      freeNavigation();
      break;
    case STOPPED:
      stopMotors();
      break;
  }
}

bool goalDetected() {
  return digitalRead(IR_LEFT) == LOW && digitalRead(IR_CENTER) == LOW && digitalRead(IR_RIGHT) == LOW;
}

void lineFollow() {
  if (goalDetected()) {
    state = STOPPED;
    return;
  }

  int frontDist = readUltrasonic(TRIG_FRONT, ECHO_FRONT);
  if (frontDist < obstacleThreshold) {
    stopMotors();
    delay(200);
    state = OBSTACLE_DETECTED;
    return;
  }

  int left = digitalRead(IR_LEFT);
  int center = digitalRead(IR_CENTER);
  int right = digitalRead(IR_RIGHT);

  if (left == HIGH && center == HIGH && right == HIGH) {
    delay(150);
    if (digitalRead(IR_LEFT) == HIGH && digitalRead(IR_CENTER) == HIGH && digitalRead(IR_RIGHT) == HIGH) {
      state = FREE_NAVIGATION;
      return;
    }
  }

  if (center == LOW) {
    setMotorSpeed(baseSpeed, baseSpeed);
  } else if (left == LOW) {
    setMotorSpeed(90, 170);
  } else if (right == LOW) {
    setMotorSpeed(170, 90);
  } else {
    setMotorSpeed(baseSpeed, baseSpeed);
  }
}

void decideWallSide() {
  int leftDist = readUltrasonic(TRIG_LEFT, ECHO_LEFT);
  int rightDist = readUltrasonic(TRIG_RIGHT, ECHO_RIGHT);
  followLeftWall = (leftDist > rightDist);
  state = WALL_FOLLOW;
}

void wallFollow() {
  if (goalDetected()) {
    state = STOPPED;
    return;
  }

  int sideDist = followLeftWall ? readUltrasonic(TRIG_LEFT, ECHO_LEFT) : readUltrasonic(TRIG_RIGHT, ECHO_RIGHT);
  int error = wallTarget - sideDist;
  int correction = Kp * error;
  int leftSpeed = constrain(baseSpeed - correction, 80, 200);
  int rightSpeed = constrain(baseSpeed + correction, 80, 200);

  if (!followLeftWall) {
    int temp = leftSpeed;
    leftSpeed = rightSpeed;
    rightSpeed = temp;
  }

  setMotorSpeed(leftSpeed, rightSpeed);

  if (digitalRead(IR_CENTER) == LOW) {
    state = LINE_FOLLOW;
  }
}

void freeNavigation() {
  if (digitalRead(IR_LEFT) == LOW || digitalRead(IR_CENTER) == LOW || digitalRead(IR_RIGHT) == LOW) {
    stopMotors();
    delay(200);
    state = LINE_FOLLOW;
    return;
  }

  int front = readUltrasonic(TRIG_FRONT, ECHO_FRONT);
  int left = readUltrasonic(TRIG_LEFT, ECHO_LEFT);
  int right = readUltrasonic(TRIG_RIGHT, ECHO_RIGHT);

  if (front < emergencyDistance) {
    backward();
    delay(400);
    rotate180();
    return;
  }

  if (front >= left && front >= right) {
    forward();
  } else if (left > right) {
    turnLeft();
  } else {
    turnRight();
  }
}

void forward() { setMotorSpeed(baseSpeed, baseSpeed); }

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, baseSpeed);
  analogWrite(ENB, baseSpeed);
}

void turnLeft() { setMotorSpeed(80, 180); }
void turnRight() { setMotorSpeed(180, 80); }

void rotate180() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, baseSpeed);
  analogWrite(ENB, baseSpeed);
  delay(800);
}

void setMotorSpeed(int leftSpeed, int rightSpeed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, leftSpeed);
  analogWrite(ENB, rightSpeed);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

int readUltrasonic(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  int distance = duration * 0.034 / 2;
  if (distance == 0) distance = 100;
  return distance;
}
