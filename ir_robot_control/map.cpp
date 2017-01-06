/****************************************
 *                                      *
 * Simple linked maps                   *
 *                                      *
 ****************************************/

#include <stdio.h>
#include "map.h"

template<class K, class V> struct item<K, V>* create_item(K key, V value) {
  struct item<K, V>* item = new struct item<K, V>;
  item->key = key;
  item->value = value;
  item->next = NULL;
  return item;
}

template<class K, class V> struct item<K, V>* add_item(struct item<K, V>* items, K key, V value) {
  struct item<K, V>* last = items;
  while (last->next != NULL) {
    last = last->next;
  }
  struct item<K, V>* item = create_item(key, value);
  last->next = item;
  return item;
}

template<class K, class V> struct item<K, V>* find_item_by_key(struct item<K, V>* items, K key) {
  struct item<K, V>* last = items;
  while (last != NULL) {
    if (last->key == key) {
      return last;
    }
    last = last->next;
  }
  return NULL;
}

template<class K, class V> struct item<K, V>* find_item_by_value(struct item<K, V>* items, V value) {
  struct item<K, V>* last = items;
  while (last != NULL) {
    if (last->value == value) {
      return last;
    }
    last = last->next;
  }
  return NULL;
}

