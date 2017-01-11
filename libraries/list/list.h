/****************************************
 *                                      *
 *  Simple linked lists                 *
 *                                      *
 ****************************************/

#ifndef list_h
#define list_h

template<class T> struct node {
  T value;
  struct node<T>* next;
};

template<class T> struct node<T>* createNode(T value);

template<class T> struct node<T>* addNode(struct node<T>* head, T value);

template<class T> void freeNode(struct node<T>* head);

#endif
