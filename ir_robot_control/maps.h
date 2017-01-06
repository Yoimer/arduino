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

