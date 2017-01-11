/****************************************
 *                                      *
 *  Simple lists                        *
 *                                      *
 ****************************************/

#include <stdio.h>
#include "list.h"

template<class T> struct node<T>* createNode(T value) {
  struct node<T>* node = new struct node<T>;
  node->value = value;
  node->next = NULL;
  return node;
}

template<class T> struct node<T>* addNode(struct node<T>* head, T value) {
  struct node<T>* last = head;
  while (last->next != NULL) {
    last = last->next;
  }
  struct node<T>* node = createNode(value);
  last->next = node;
  return node;
}

template<class T> void freeNode(struct node<T>* head) {
  struct node<T>* tmp;
  struct node<T>* it = head;
  while (it != NULL) {
    tmp = it;
    it = it->next;
    delete tmp;
    tmp = NULL;
  }
}

