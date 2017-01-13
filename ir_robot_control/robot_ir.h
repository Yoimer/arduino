/****************************************
 *                                      *
 * IR Remotes                           *
 *                                      *
 * Based on type different codes used   *
 *                                      *
 ****************************************/

#ifndef robot_ir_h
#define robot_ir_h

#include <robot.h>
#include <map.cpp>

// IR pin
#define ROBOT_IR_PIN 11

// Sony Bravia TV
// note: my Sony Bravia - may differ for other models
#define ROBOT_REMOTE_SONY 1
// circuits.io simulator
#define ROBOT_REMOTE_CIRCUITS_IO 2
// Philips Mini Tower
// note: my Philips Mini Tower - may differ for other models
#define ROBOT_REMOTE_PHILIPS 3

/****************************************
 *                                      *
 * Select the remote type               *
 *                                      *
 ****************************************/

#define ROBOT_REMOTE_SELECTED ROBOT_REMOTE_SONY

#if defined ROBOT_REMOTE_SELECTED && ROBOT_REMOTE_SELECTED == ROBOT_REMOTE_SONY

#define ROBOT_IR_REMOTE_1 0x207BEF0F
#define ROBOT_IR_REMOTE_2 0xE8455D8E
#define ROBOT_IR_REMOTE_3 0xCBB7E949
#define ROBOT_IR_REMOTE_4 0x2C1F3172
#define ROBOT_IR_REMOTE_6 0x8CE1E3FC
#define ROBOT_IR_REMOTE_7 0x315B1905
#define ROBOT_IR_REMOTE_8 0xC67C01B6
#define ROBOT_IR_REMOTE_9 0xB418D969
#define ROBOT_IR_REMOTE_FUNC 0x2B4DA162

#endif

#if defined ROBOT_REMOTE_SELECTED && ROBOT_REMOTE_SELECTED == ROBOT_REMOTE_PHILIPS

#define ROBOT_IR_REMOTE_1 0xC54DA1E5
#define ROBOT_IR_REMOTE_2 0xDD54FA64
#define ROBOT_IR_REMOTE_3 0x52394D26
#define ROBOT_IR_REMOTE_4 0x90A84C9A
#define ROBOT_IR_REMOTE_6 0xBBB5D0DB
#define ROBOT_IR_REMOTE_7 0x898E1742
#define ROBOT_IR_REMOTE_8 0xAFBC74A
#define ROBOT_IR_REMOTE_9 0xBAEBCA37
#define ROBOT_IR_REMOTE_FUNC 0xA26697EF

#endif

#if defined ROBOT_REMOTE_SELECTED && ROBOT_REMOTE_SELECTED == ROBOT_REMOTE_CIRCUITS_IO

#define ROBOT_IR_REMOTE_1 0xFD08F7
#define ROBOT_IR_REMOTE_2 0xFD8877
#define ROBOT_IR_REMOTE_3 0xFD48B7
#define ROBOT_IR_REMOTE_4 0xFD28D7
#define ROBOT_IR_REMOTE_6 0xFD6897
#define ROBOT_IR_REMOTE_7 0xFD18E7
#define ROBOT_IR_REMOTE_8 0xFD9867
#define ROBOT_IR_REMOTE_9 0xFD58A7
#define ROBOT_IR_REMOTE_FUNC 0XFD40BF

#endif

struct item<unsigned char, unsigned long>* getCodes() {
  struct item<unsigned char, unsigned long>* codes;
  codes = createItem((unsigned char)(ROBOT_N), (unsigned long)(ROBOT_IR_REMOTE_2));
  addItem(codes, (unsigned char)(ROBOT_NE), (unsigned long)(ROBOT_IR_REMOTE_3));
  addItem(codes, (unsigned char)(ROBOT_E), (unsigned long)(ROBOT_IR_REMOTE_6));
  addItem(codes, (unsigned char)(ROBOT_SE), (unsigned long)(ROBOT_IR_REMOTE_9));
  addItem(codes, (unsigned char)(ROBOT_S), (unsigned long)(ROBOT_IR_REMOTE_8));
  addItem(codes, (unsigned char)(ROBOT_SW), (unsigned long)(ROBOT_IR_REMOTE_7));
  addItem(codes, (unsigned char)(ROBOT_W), (unsigned long)(ROBOT_IR_REMOTE_4));
  addItem(codes, (unsigned char)(ROBOT_NW), (unsigned long)(ROBOT_IR_REMOTE_1));
  addItem(codes, (unsigned char)(ROBOT_PROGRAMMING), (unsigned long)(ROBOT_IR_REMOTE_FUNC));
  return codes;
}

#endif
