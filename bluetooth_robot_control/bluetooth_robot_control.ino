#include <SoftwareSerial.h>

#include <robot.h>
#include <map.h>

#include "robot_bluetooth.h"

/****************************************
 *                                      *
 * Global variables                     *
 *                                      *
 ****************************************/

SoftwareSerial bluetooth(ROBOT_BT_RX_PIN, ROBOT_BT_TX_PIN);
Robot robot;
struct item<unsigned char, int>* codes = getCodes();

/****************************************
 *                                      *
 *  Arduino functions                   *
 *                                      *
 ****************************************/

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);

  pinMode(ROBOT_RIGHT_MOTOR_PIN1, OUTPUT);
  pinMode(ROBOT_RIGHT_MOTOR_PIN2, OUTPUT);

  pinMode(ROBOT_LEFT_MOTOR_PIN1, OUTPUT);
  pinMode(ROBOT_LEFT_MOTOR_PIN2, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (bluetooth.available()) {
    int code = bluetooth.read();
    if (code == 3) {
      return;
    }

    struct item<unsigned char, int>* item = findItemByValue(codes, code);
    if (item != NULL) {
      robot.execute(item->key);
    }

    if (robot.isProgramming()) {
      digitalWrite(LED_BUILTIN, HIGH);
    } else {
      digitalWrite(LED_BUILTIN, LOW);
    }

  }
  delay(ROBOT_DELAY_LOOP);
}

