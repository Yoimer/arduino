/****************************************
 *                                      *
 * Constants                            *
 *                                      *
 * There were name clashes in Arduino   *
 * thus this code uses ROBOT_ prefix    *
 *                                      *
 ****************************************/

#define ROBOT_DIRECTIONS 8

// bit mask for directions
// 10000000
#define ROBOT_N 1 << 7
// 00010000
#define ROBOT_S 1 << 4
// 00001000
#define ROBOT_E 1 << 3
// 00000001
#define ROBOT_W 1
#define ROBOT_NE ROBOT_N | ROBOT_E
#define ROBOT_NW ROBOT_N | ROBOT_W
#define ROBOT_SE ROBOT_S | ROBOT_E
#define ROBOT_SW ROBOT_S | ROBOT_W
// special direction
#define ROBOT_NO_MOVE 0

/****************************************
 *                                      *
 * IR Remotes                           *
 *                                      *
 * Based on type different codes used   *
 *                                      *
 ****************************************/

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

// motor 1 pins
#define ROBOT_RIGHT_MOTOR_PIN1 10
#define ROBOT_RIGHT_MOTOR_PIN2 9
// motor 2 pins
#define ROBOT_LEFT_MOTOR_PIN1 5
#define ROBOT_LEFT_MOTOR_PIN2 3
// IR pin
#define ROBOT_IR_PIN 11

// move lenght in ms
#define ROBOT_MOVE_LENGHT 4000
// turn 90 degrees lenght in ms
#define ROBOT_TURN_LENGHT 650
// delay lenght in ms
#define ROBOT_DELAY_LENGHT 20
// delay in the loop function
#define ROBOT_DELAY_LOOP 1000


void move(unsigned char forward);

void stop();

void turn(short deg);

void execute(unsigned char direction);
