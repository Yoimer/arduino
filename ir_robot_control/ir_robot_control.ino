#include <IRremote.h>

#include <robot.h>
#include <map.h>
#include "robot_ir.h"

/****************************************
 *                                      *
 * Global variables                     *
 *                                      *
 ****************************************/

IRrecv irrecv(ROBOT_IR_PIN);
Robot robot;
struct item<unsigned char, unsigned long>* codes = getCodes();

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
}

void loop() {
  decode_results results;
  if (irrecv.decode(&results)) {
    irrecv.resume();
    if (results.value == ROBOT_IR_REMOTE_FUNC) {
      if (!robot.isProgramming()) {
        robot.startProgramming();
        digitalWrite(LED_BUILTIN, HIGH);
      } else {
        digitalWrite(LED_BUILTIN, LOW);
        robot.endProgramming();
      }
    } else {
      struct item<unsigned char, unsigned long>* item = findItemByValue(codes, results.value);
      if (item != NULL) {
        robot.execute(item->key);
      }
    }
  }
  delay(ROBOT_DELAY_LOOP);
}
