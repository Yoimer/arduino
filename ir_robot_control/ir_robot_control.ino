#include <IRremote.h>
#include <SoftwareSerial.h>

#include "robot_api.h"
#include "lists.h"
#include "maps.h"

/****************************************
 *                                      *
 * Moving Robot                         *
 *                                      *
 ****************************************/

void move(unsigned char forward) {
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

void stop() {
  digitalWrite(ROBOT_RIGHT_MOTOR_PIN1, LOW);
  digitalWrite(ROBOT_RIGHT_MOTOR_PIN2, LOW);

  digitalWrite(ROBOT_LEFT_MOTOR_PIN1, LOW);
  digitalWrite(ROBOT_LEFT_MOTOR_PIN2, LOW);

  delay(ROBOT_DELAY_LENGHT);
}


void turn(short deg) {
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

void execute(unsigned char direction) {
  switch (direction) {
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
  }
  stop();
}

void replay_moves(struct node* list) {
  struct node* tmp = list;
  while (tmp != NULL) {
    execute(tmp->direction);
    tmp = tmp->next;
  }
}

/****************************************
 *                                      *
 * Global variables                     *
 *                                      *
 ****************************************/

IRrecv irrecv(ROBOT_IR_PIN);
struct map* codes;
struct node* directions;
bool programming = 0;

/****************************************
 *                                      *
 *  Arduino functions                   *
 *                                      *
 ****************************************/

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();

  Serial.println("=======================");
  Serial.print("Using remote with programming button ");
  Serial.print(ROBOT_IR_REMOTE_FUNC, HEX);
  Serial.println();

  pinMode(ROBOT_RIGHT_MOTOR_PIN1, OUTPUT);
  pinMode(ROBOT_RIGHT_MOTOR_PIN2, OUTPUT);

  pinMode(ROBOT_LEFT_MOTOR_PIN1, OUTPUT);
  pinMode(ROBOT_LEFT_MOTOR_PIN2, OUTPUT);

  pinMode(ROBOT_IR_PIN, INPUT);

  pinMode(LED_BUILTIN, OUTPUT);

  codes = create_map(ROBOT_N, ROBOT_IR_REMOTE_2);
  add_item(codes, ROBOT_NE, ROBOT_IR_REMOTE_3);
  add_item(codes, ROBOT_E, ROBOT_IR_REMOTE_6);
  add_item(codes, ROBOT_SE, ROBOT_IR_REMOTE_9);
  add_item(codes, ROBOT_S, ROBOT_IR_REMOTE_8);
  add_item(codes, ROBOT_SW, ROBOT_IR_REMOTE_7);
  add_item(codes, ROBOT_W, ROBOT_IR_REMOTE_4);
  add_item(codes, ROBOT_NW, ROBOT_IR_REMOTE_1);
}

void loop() {
  decode_results results;
  if (irrecv.decode(&results)) {
    irrecv.resume();
    if (results.value == ROBOT_IR_REMOTE_FUNC) {
      programming = !programming;
      if (programming) {
        digitalWrite(LED_BUILTIN, HIGH);
      } else {
        digitalWrite(LED_BUILTIN, LOW);
        replay_moves(directions);
        free_list(directions);
      }
    } else {
      struct map* item = find_item_by_code(codes, results.value);

      if (item != NULL) {
        if (programming) {
          if (directions == NULL) {
            directions = create_node(item->direction);
          } else {
            add_node(directions, item->direction);
          }
        } else {
          execute(item->direction);
        }
      }
    }
  }
  delay(ROBOT_DELAY_LOOP);
}

