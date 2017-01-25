#include <SoftwareSerial.h>

#include <robot.h>
#include <map.h>
#include <env.h>

#include "robot_bluetooth.h"

/****************************************
 *                                      *
 * Global variables                     *
 *                                      *
 ****************************************/

SoftwareSerial bluetooth(ROBOT_BT_RX_PIN, ROBOT_BT_TX_PIN);
Robot robot = new Robot(true);
struct item<unsigned char, int>* codes = getCodes();

/****************************************
 *                                      *
 *  Arduino functions                   *
 *                                      *
 ****************************************/

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  Serial.println("=======================");
}

void loop() {
//  unsigned short darkness = analogRead(A0);
//  if (Env::isDark(darkness)) {
//    robot.turnLightsOn();
//  } else {
//    robot.turnLightsOff();
//  }

  if (bluetooth.available()) {
    int code = bluetooth.read();
    if (code == 3) {
      return;
    }
    struct item<unsigned char, int>* item = findItemByValue(codes, code);
    if (item != NULL) {
      robot.execute(item->key);
    }
  }

  delay(ROBOT_DELAY_LOOP);
}
