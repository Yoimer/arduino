/****************************************
 *                                      *
 * Bluetooth Codes                      *
 *                                      *
 ****************************************/

#ifndef robot_bt_h
#define robot_bt_h

#include <robot.h>
#include <map.cpp>

#define ROBOT_BT_RX_PIN 11
#define ROBOT_BT_TX_PIN 6

struct item<unsigned char, int>* getCodes() {
  struct item<unsigned char, int>* codes;
  codes = createItem((unsigned char)(ROBOT_N), 48);
  addItem(codes, (unsigned char)(ROBOT_NE), 49);
  addItem(codes, (unsigned char)(ROBOT_E), 50);
  addItem(codes, (unsigned char)(ROBOT_SE), 51);
  addItem(codes, (unsigned char)(ROBOT_S), 52);
  addItem(codes, (unsigned char)(ROBOT_SW), 53);
  addItem(codes, (unsigned char)(ROBOT_W), 54);
  addItem(codes, (unsigned char)(ROBOT_NW), 55);
  addItem(codes, (unsigned char)(ROBOT_PROGRAMMING), 56);
  addItem(codes, (unsigned char)(ROBOT_LIGHTS), 57);
  return codes;
}

#endif
