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

