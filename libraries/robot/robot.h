#ifndef robot_h
#define robot_h

#include <list.h>

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
#define ROBOT_NW (ROBOT_N | ROBOT_W)
#define ROBOT_SE ROBOT_S | ROBOT_E
#define ROBOT_SW ROBOT_S | ROBOT_W
// special direction
#define ROBOT_NO_MOVE 0
// marking start/stop of programming
#define ROBOT_PROGRAMMING 100
// turning the lights on/off
#define ROBOT_LIGHTS 101

// motor 1 pins
#define ROBOT_RIGHT_MOTOR_PIN1 10
#define ROBOT_RIGHT_MOTOR_PIN2 9
// motor 2 pins
#define ROBOT_LEFT_MOTOR_PIN1 5
#define ROBOT_LEFT_MOTOR_PIN2 3

// lights
#define ROBOT_LIGHTS_PIN 2

// move lenght in ms
// was 4000
#define ROBOT_MOVE_LENGHT 2000
// turn 90 degrees lenght in ms
// was 650
#define ROBOT_TURN_LENGHT 350
// delay lenght in ms
#define ROBOT_DELAY_LENGHT 20
// delay in the loop function
#define ROBOT_DELAY_LOOP 1000

class Robot {
  public:
    Robot(bool frontOmniWheel);
    bool isProgramming();
    void startProgramming();
    void endProgramming();
    void execute(unsigned char direction);
    bool areLightsOn();
    void turnLightsOn();
    void turnLightsOff();

  private:
    bool frontOmniWheel;
    bool programming;
    bool lightsOn;
    struct node<unsigned char>* moves;
    void move(unsigned char forward);
    void stop();
    void turn(short deg);
    void replayMoves();
};

#endif
