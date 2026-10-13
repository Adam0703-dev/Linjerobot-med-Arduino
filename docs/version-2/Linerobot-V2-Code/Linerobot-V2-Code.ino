#include "arduino_secrets.h"

// ================= STATES =================
enum RobotState {
  LINE_FOLLOW,
  OBSTACLE_DETECTED,
  WALL_FOLLOW,
  FREE_NAVIGATION
};

RobotState state;

// ================= MOTOR PINS =================
#define IN1 A5
#define IN2 A4
#define IN3 A3
#define IN4 A2
#define ENA 10
#define ENB 11

// ================= IR =================
#define IR_LEFT A0
#define IR_CENTER 2
#define IR_RIGHT A1

// ================= ULTRASONIC =================
#define TRIG_FRONT_LEFT 12
#define ECHO_FRONT_LEFT 9
#define TRIG_FRONT_RIGHT 5
#define ECHO_FRONT_RIGHT 6
#define TRIG_LEFT 4
#define ECHO_LEFT 3
#define TRIG_RIGHT 8
#define ECHO_RIGHT 7

// ================= PARAMETERS =================
int baseSpeed = 80;
int obstacleThreshold = 20;
int wallTarget = 25;
bool obstacleTurnedLeft = true;
// =================================================

void setup() {

  Serial.begin(9600);
  while(!Serial);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IR_LEFT, INPUT);
  pinMode(IR_CENTER, INPUT);
  pinMode(IR_RIGHT, INPUT);

  pinMode(TRIG_FRONT_LEFT, OUTPUT);
  pinMode(ECHO_FRONT_LEFT, INPUT);
  pinMode(TRIG_FRONT_RIGHT, OUTPUT);
  pinMode(ECHO_FRONT_RIGHT, INPUT);
  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);
  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);

  delay(800);

  state = LINE_FOLLOW;
}

// =================================================

void loop() {

  printDebug();

  switch(state) {

    case LINE_FOLLOW:
      lineFollow();
      break;

    case OBSTACLE_DETECTED:
      obstacleDetected();
      break;

    case WALL_FOLLOW:
      wallFollow();
      break;

    case FREE_NAVIGATION:
      freeNavigation();
      break;
  }

  delay(200);
}

// =================================================
// DEBUG
// =================================================

void printDebug() {

  Serial.println("====================================");

  Serial.print("STATE: ");
  if(state == LINE_FOLLOW) Serial.println("LINE_FOLLOW");
  if(state == OBSTACLE_DETECTED) Serial.println("OBSTACLE_DETECTED");
  if(state == FREE_NAVIGATION) Serial.println("FREE_NAVIGATION");

  Serial.print("IR L:");
  Serial.print(digitalRead(IR_LEFT));
  Serial.print(" C:");
  Serial.print(digitalRead(IR_CENTER));
  Serial.print(" R:");
  Serial.println(digitalRead(IR_RIGHT));

  int fl = readUltrasonic(TRIG_FRONT_LEFT, ECHO_FRONT_LEFT);
  int fr = readUltrasonic(TRIG_FRONT_RIGHT, ECHO_FRONT_RIGHT);
  int l  = readUltrasonic(TRIG_LEFT, ECHO_LEFT);
  int r  = readUltrasonic(TRIG_RIGHT, ECHO_RIGHT);

  Serial.print("ULTRA FL:");
  Serial.print(fl);
  Serial.print(" FR:");
  Serial.print(fr);
  Serial.print(" L:");
  Serial.print(l);
  Serial.print(" R:");
  Serial.println(r);

  Serial.print("Front(min): ");
  Serial.println(min(fl, fr));
}

// =================================================
// FRONT DISTANCE
// =================================================

int getFrontDistance() {
  int fl = readUltrasonic(TRIG_FRONT_LEFT, ECHO_FRONT_LEFT);
  delay(10);
  int fr = readUltrasonic(TRIG_FRONT_RIGHT, ECHO_FRONT_RIGHT);
  return min(fl, fr);
}

// =================================================
// LINE FOLLOW
// =================================================

void lineFollow() {

  int front = getFrontDistance();

  if(front < obstacleThreshold) {
    state = OBSTACLE_DETECTED;
    return;
  }

  int left   = digitalRead(IR_LEFT);
  int center = digitalRead(IR_CENTER);
  int right  = digitalRead(IR_RIGHT);

  // CENTER pÃ¥ linjen â kÃ¶r rakt
  if(center == LOW) {
    setMotorSpeed(baseSpeed, baseSpeed);
  }

  // Linjen Ã¤r till vÃ¤nster
  else if(left == LOW) {

    Serial.println("Adjusting LEFT");

    // Stanna nÃ¤stan och justera lÃ¥ngsamt
    setMotorSpeed(140, 0);

    // FortsÃ¤tt svÃ¤nga tills center hittar linjen
    while(digitalRead(IR_CENTER) == HIGH) {
      int front = getFrontDistance();
      if(front < obstacleThreshold) {
      state = OBSTACLE_DETECTED;
      return;
      }
      setMotorSpeed(140, 0);
    }
  }

  // Linjen Ã¤r till hÃ¶ger
  else if(right == LOW) {

    Serial.println("Adjusting RIGHT");

    setMotorSpeed(0, 140);

    while(digitalRead(IR_CENTER) == HIGH) {
      int front = getFrontDistance();
      if(front < obstacleThreshold) {
      state = OBSTACLE_DETECTED;
      return;
      }
      setMotorSpeed(0, 140);
    }
  }
 
}


// =================================================
// OBSTACLE OVER LINE
// =================================================

void obstacleDetected() {

  Serial.println("Obstacle detected over line");

  backward();
  delay(900);

  setMotorSpeed(0, 0);
  delay(200); 

  int leftDist  = readUltrasonic(TRIG_LEFT, ECHO_LEFT);
  int rightDist = readUltrasonic(TRIG_RIGHT, ECHO_RIGHT);

  if(leftDist > rightDist) {
    obstacleTurnedLeft = true;
    turnLeft();
  } else {
    obstacleTurnedLeft = false;
    turnRight();
  }

  delay(500);
  state = WALL_FOLLOW;
}

void wallFollow() {
    // Om linjen hittas igen
  if(digitalRead(IR_LEFT) == LOW ||
     digitalRead(IR_CENTER) == LOW ||
     digitalRead(IR_RIGHT) == LOW) {

    // SvÃ¤ng tillbaka Ã¥t RÃTT hÃ¥ll
    if (obstacleTurnedLeft) {
      while (digitalRead(IR_LEFT) == LOW && digitalRead(IR_CENTER) == LOW)
      turnLeftWall();
    } 
    
    else {
      while (digitalRead(IR_RIGHT) == LOW && digitalRead(IR_CENTER) == LOW)
      turnRightWall();
    }

    state = LINE_FOLLOW;
    return;
  }

  // LÃ¤s avstÃ¥nd till vÃ¤ggen
  int wallDist;

  if (obstacleTurnedLeft) {
    wallDist = readUltrasonic(TRIG_RIGHT, ECHO_RIGHT);
  } else {
    wallDist = readUltrasonic(TRIG_LEFT, ECHO_LEFT);
  }
  if (obstacleTurnedLeft) {
    while (wallDist > wallTarget) {
    setMotorSpeed(140, 0);
    wallDist = readUltrasonic(TRIG_RIGHT, ECHO_RIGHT);
    }
    while (wallDist < wallTarget) {
    setMotorSpeed(0, 140);
    wallDist = readUltrasonic(TRIG_RIGHT, ECHO_RIGHT);
    }
  }
  else {
    while (wallDist > wallTarget) {
    setMotorSpeed(0, 140);
    wallDist = readUltrasonic(TRIG_LEFT, ECHO_LEFT);
    }
    while (wallDist < wallTarget) {
    setMotorSpeed(140, 0);
    wallDist = readUltrasonic(TRIG_LEFT, ECHO_LEFT);
    }
  }
}

// =================================================
// FREE NAVIGATION (FlÃ¶deschema-logik)
// =================================================

void freeNavigation() {

  int front = getFrontDistance();

  // Om linje hittas igen
  if(digitalRead(IR_LEFT) == LOW ||
     digitalRead(IR_CENTER) == LOW ||
     digitalRead(IR_RIGHT) == LOW) {

     state = LINE_FOLLOW;
     return;
  }

  // KÃ¶r fritt fram
  if(front >= obstacleThreshold) {
    forward();
    return;
  }

  // Hinder framfÃ¶r
  Serial.println("Free mode obstacle!");

  backward();
  delay(1800);

  int leftDist = readUltrasonic(TRIG_LEFT, ECHO_LEFT);
  int rightDist = readUltrasonic(TRIG_RIGHT, ECHO_RIGHT);

  Serial.print("Choosing side -> L:");
  Serial.print(leftDist);
  Serial.print(" R:");
  Serial.println(rightDist);

  if(leftDist > rightDist) {
   turnLeft();
  } else {
   turnRight();
  }

  delay(1200);

  forward();
}

// =================================================
// MOTOR FUNCTIONS
// =================================================

void forward() {
  setMotorSpeed(baseSpeed, baseSpeed);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
  Serial.println("Motor: BACKWARD");
}

void turnLeft() {
   digitalWrite(IN1, HIGH);
   digitalWrite(IN2, LOW);
   analogWrite(ENA, 120);
   digitalWrite(IN3, LOW);
   digitalWrite(IN4, HIGH);
   analogWrite(ENB, 120);
  Serial.println("Motor: TURN LEFT");
  delay(1200);
}

void turnRight() {
   digitalWrite(IN1, LOW);
   digitalWrite(IN2, HIGH);
   analogWrite(ENA, 160);
   digitalWrite(IN3, HIGH);
   digitalWrite(IN4, LOW);
   analogWrite(ENB, 160);
  Serial.println("Motor: TURN RIGHT");
  delay(1200);
}

void turnLeftWall() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 100);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENB, 100);
    Serial.println("Motor: TURN LEFT");
}

void turnRightWall() {
   digitalWrite(IN1, LOW);
   digitalWrite(IN2, HIGH);
   analogWrite(ENA, 100);
   digitalWrite(IN3, HIGH);
   digitalWrite(IN4, LOW);
   analogWrite(ENB, 100);
  Serial.println("Motor: TURN RIGHT");
}

void setMotorSpeed(int leftSpeed, int rightSpeed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, leftSpeed);
  analogWrite(ENB, rightSpeed);

  Serial.print("Motor L:");
  Serial.print(leftSpeed);
  Serial.print(" R:");
  Serial.println(rightSpeed);
}

// =================================================
// ULTRASONIC
// =================================================

int readUltrasonic(int trigPin, int echoPin) {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  int distance = duration * 0.034 / 2;

  if(distance == 0) distance = 100;

  return distance;
}