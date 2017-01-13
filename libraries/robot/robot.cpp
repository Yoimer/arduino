#include <Arduino.h>

#include "robot.h"
#include <list.cpp>

/****************************************
 *                                      *
 * Robot logic                          *
 *                                      *
 ****************************************/

bool Robot::isProgramming() {
  return programming;
}

void Robot::startProgramming() {
  programming = 1;
}

void Robot::endProgramming() {
  programming = 0;
  replayMoves();
}

void Robot::move(unsigned char forward) {
  if (forward) {
    Serial.println("Moving forward");
  } else {
    Serial.println("Moving reverse");
  }
  digitalWrite(ROBOT_RIGHT_MOTOR_PIN1, forward);
  digitalWrite(ROBOT_RIGHT_MOTOR_PIN2, !forward);

  digitalWrite(ROBOT_LEFT_MOTOR_PIN1, forward);
  digitalWrite(ROBOT_LEFT_MOTOR_PIN2, !forward);

  delay(ROBOT_MOVE_LENGHT);
}

void Robot::stop() {
  digitalWrite(ROBOT_RIGHT_MOTOR_PIN1, LOW);
  digitalWrite(ROBOT_RIGHT_MOTOR_PIN2, LOW);

  digitalWrite(ROBOT_LEFT_MOTOR_PIN1, LOW);
  digitalWrite(ROBOT_LEFT_MOTOR_PIN2, LOW);

  delay(ROBOT_DELAY_LENGHT);
}

void Robot::turn(short deg) {
  Serial.print("Turning by ");
  Serial.println(deg);

  unsigned char left = LOW;
  unsigned char right = LOW;

  // turning left:
  // left motor reverses while right one moves forward
  if (deg < 0) {
    right = HIGH;
    deg = -deg;
  } else {
    left = HIGH;
  }

  unsigned short delayMs = (deg / 90.0) * ROBOT_TURN_LENGHT;

  Serial.print("Move will take ");
  Serial.print(delayMs);
  Serial.println(" ms");

  digitalWrite(ROBOT_LEFT_MOTOR_PIN1, left);
  digitalWrite(ROBOT_LEFT_MOTOR_PIN2, !left);

  digitalWrite(ROBOT_RIGHT_MOTOR_PIN1, right);
  digitalWrite(ROBOT_RIGHT_MOTOR_PIN2, !right);

  delay(delayMs);
}


void Robot::execute(unsigned char code) {

  if (isProgramming() && code != ROBOT_PROGRAMMING) {
    if (moves == NULL) {
        moves = createNode(code);
    } else {
        addNode(moves, code);
    }
    return;
  }

  switch (code) {
    case ROBOT_N:
      move(HIGH);
      break;
    case ROBOT_S:
      move(LOW);
      break;
    case ROBOT_W:
      turn(-90);
      break;
    case ROBOT_NW:
      turn(-45);
      break;
    case ROBOT_SW:
      turn(-135);
      break;
    case ROBOT_E:
      turn(90);
      break;
    case ROBOT_NE:
      turn(45);
      break;
    case ROBOT_SE:
      turn(135);
      break;
    case ROBOT_PROGRAMMING:
      if (!isProgramming()) {
        startProgramming();
      } else {
        endProgramming();
      }
      break;
  }
  stop();
}

void Robot::replayMoves() {
  struct node<unsigned char>* tmp = moves;
  while (tmp != NULL) {
    execute(tmp->value);
    tmp = tmp->next;
  }
  freeNode(moves);
}
