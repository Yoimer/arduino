#include <IRremote.h>

#include <robot.h>
#include <map.h>
#include <env.h>
#include "robot_ir.h"

/****************************************
 *                                      *
 * Global variables                     *
 *                                      *
 ****************************************/

IRrecv irrecv(ROBOT_IR_PIN);
Robot robot = new Robot(false);
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

  pinMode(ROBOT_IR_PIN, INPUT);
}

void loop() {
  unsigned short darkness = analogRead(A0);
  if (Env::isDark(darkness)) {
    robot.turnLightsOn();
  } else {
    robot.turnLightsOff();
  }

  decode_results results;
  if (irrecv.decode(&results)) {
    irrecv.resume();
    struct item<unsigned char, unsigned long>* item = findItemByValue(codes, results.value);
    if (item != NULL) {
      robot.execute(item->key);
    }
  }

  delay(ROBOT_DELAY_LOOP);
}
