/****************************************
 *                                      *
 *  Simple lists                        *
 *                                      *
 ****************************************/

#include <stdio.h>
#include "list.h"

template<class T> struct node<T>* create_node(T value) {
  struct node<T>* node = new struct node<T>;
  node->value = value;
  node->next = NULL;
  return node;
}

template<class T> struct node<T>* add_node(struct node<T>* list, T value) {
  struct node<T>* last = list;
  while (last->next != NULL) {
    last = last->next;
  }
  struct node<T>* n = create_node(value);
  last->next = n;
  return n;
}

template<class T> void free_node(struct node<T>* node) {
  struct node<T>* tmp;
  while (node != NULL) {
    tmp = node;
    node = node->next;
    delete tmp;
    tmp = NULL;
  }
}

