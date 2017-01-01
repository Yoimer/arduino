#include <IRremote.h>
#include <SoftwareSerial.h>

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
// note: my Philips Mini Towe - may differ for other models
#define ROBOT_REMOTE_PHILIPS 3

/****************************************
 *                                      *
 * Select the remote type               *
 *                                      *
 ****************************************/

#define ROBOT_REMOTE_SELECTED ROBOT_REMOTE_SONY

#if defined ROBOT_REMOTE_SELECTED == ROBOT_REMOTE_SONY

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

#if defined ROBOT_REMOTE_SELECTED == ROBOT_REMOTE_PHILIPS

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

#if defined ROBOT_REMOTE_SELECTED == ROBOT_REMOTE_CIRCUITS_IO

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


/****************************************
 *                                      *
 *  Lists                               *
 *                                      *
 ****************************************/

struct node {
  unsigned char direction;
  struct node *next;
};

struct node* create_node(unsigned char direction) {
  struct node* node = (struct node*) malloc(sizeof(struct node));
  node->direction = direction;
  node->next = NULL;
  return node;
}

struct node* add_node(struct node* nodes, unsigned char direction) {
  struct node* last = nodes;
  while (last->next != NULL) {
    last = last->next;
  }
  struct node* node = create_node(direction);
  last->next = node;
  return node;
}

void free_list(struct node* list) {
  struct node* tmp;

  while (list != NULL) {
    tmp = list;
    list = list->next;
    free(tmp);
  }

  list = NULL;
}

/****************************************
 *                                      *
 * Maps                                 *
 *                                      *
 ****************************************/

struct map {
  unsigned char direction;
  unsigned long code;
  struct map *next;
};


struct map* create_map(unsigned char direction, unsigned long code) {
  struct map* map = (struct map*) malloc(sizeof(struct map));
  map->direction = direction;
  map->code = code;
  map->next = NULL;
  return map;
}

struct map* add_item(struct map* map, unsigned char direction, unsigned long code) {
  struct map* last = map;
  while (last->next != NULL) {
    last = last->next;
  }
  struct map* item = create_map(direction, code);
  last->next = item;
  return item;
}

struct map* find_item_by_direction(struct map* map, unsigned char direction) {
  struct map* last = map;
  while (last != NULL) {
    if (last->direction == direction) {
      return last;
    }
    last = last->next;
  }
  return NULL;
}

struct map* find_item_by_code(struct map* map, unsigned long code) {
  struct map* last = map;
  while (last != NULL) {
    if (last->code == code) {
      return last;
    }
    last = last->next;
  }
  return NULL;
}

/****************************************
 *                                      *
 * Moving Robot                         *
 *                                      *
 ****************************************/

void move(unsigned char forward, unsigned int delayMs) {
  digitalWrite(ROBOT_RIGHT_MOTOR_PIN1, forward);
  digitalWrite(ROBOT_RIGHT_MOTOR_PIN2, !forward);

  digitalWrite(ROBOT_LEFT_MOTOR_PIN1, forward);
  digitalWrite(ROBOT_LEFT_MOTOR_PIN2, !forward);

  delay(delayMs);  
}

void forward(unsigned int delayMs) {
  Serial.println("Forward");

  move(HIGH, delayMs);
}

void reverse(unsigned int delayMs) {
  Serial.println("Reverse");

  move(LOW, delayMs);
}

void stop() {
  digitalWrite(ROBOT_RIGHT_MOTOR_PIN1, LOW);
  digitalWrite(ROBOT_RIGHT_MOTOR_PIN2, LOW);

  digitalWrite(ROBOT_LEFT_MOTOR_PIN1, LOW);
  digitalWrite(ROBOT_LEFT_MOTOR_PIN2, LOW);

  delay(ROBOT_DELAY_LENGHT);
}


void turn(float delayMs, unsigned char left, unsigned char right) {
  digitalWrite(ROBOT_LEFT_MOTOR_PIN1, left);
  digitalWrite(ROBOT_LEFT_MOTOR_PIN2, !left);

  digitalWrite(ROBOT_RIGHT_MOTOR_PIN1, right);
  digitalWrite(ROBOT_RIGHT_MOTOR_PIN2, !right);

  delay(delayMs);
}

void left(float delayMs) {
  Serial.print("Left ");
  Serial.print(delayMs / ROBOT_TURN_LENGHT * 90);
  Serial.println(" degrees");

  turn(delayMs, LOW, HIGH);
}

void right(float delayMs) {
  Serial.print("Right ");
  Serial.print(delayMs / ROBOT_TURN_LENGHT * 90);
  Serial.println(" degrees");

  turn(delayMs, HIGH, LOW);

}

void execute(unsigned long direction) {
  switch (direction) {
    case ROBOT_N:
      forward(ROBOT_MOVE_LENGHT);
      break;
    case ROBOT_S:
      reverse(ROBOT_MOVE_LENGHT);
      break;
    case ROBOT_W:
      left(ROBOT_TURN_LENGHT);
      break;
    case ROBOT_NW:
      left(ROBOT_TURN_LENGHT / 2);
      break;
    case ROBOT_SW:
      left(ROBOT_TURN_LENGHT + ROBOT_TURN_LENGHT / 2);
      break;
    case ROBOT_E:
      right(ROBOT_TURN_LENGHT);
      break;
    case ROBOT_NE:
      right(ROBOT_TURN_LENGHT / 2);
      break;
    case ROBOT_SE:
      right(ROBOT_TURN_LENGHT + ROBOT_TURN_LENGHT / 2);
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

