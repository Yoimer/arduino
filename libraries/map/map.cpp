/****************************************
 *                                      *
 * Simple linked maps                   *
 *                                      *
 ****************************************/

#include <stdio.h>
#include "map.h"

template<class K, class V> struct item<K, V>* createItem(K key, V value) {
  struct item<K, V>* item = new struct item<K, V>;
  item->key = key;
  item->value = value;
  item->next = NULL;
  return item;
}

template<class K, class V> struct item<K, V>* addItem(struct item<K, V>* items, K key, V value) {
  struct item<K, V>* last = items;
  while (last->next != NULL) {
    last = last->next;
  }
  struct item<K, V>* item = createItem(key, value);
  last->next = item;
  return item;
}

template<class K, class V> struct item<K, V>* findItemByKey(struct item<K, V>* items, K key) {
  struct item<K, V>* last = items;
  while (last != NULL) {
    if (last->key == key) {
      return last;
    }
    last = last->next;
  }
  return NULL;
}

template<class K, class V> struct item<K, V>* findItemByValue(struct item<K, V>* items, V value) {
  struct item<K, V>* last = items;
  while (last != NULL) {
    if (last->value == value) {
      return last;
    }
    last = last->next;
  }
  return NULL;
}
