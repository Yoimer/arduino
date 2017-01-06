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

template<class T> struct node<T>* create_node(T value);

template<class T> struct node<T>* add_node(struct node<T>* nodes, T value);

template<class T> void free_node(struct node<T>* node);

#endif
