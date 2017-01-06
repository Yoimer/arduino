/****************************************
 *                                      *
 * Simple linked maps                   *
 *                                      *
 ****************************************/

#ifndef map_h
#define map_h

template<class K, class V> struct item {
  K key;
  V value;
  struct item<K, V>* next;
};


template<class K, class V> struct item<K, V>* create_item(K key, V value);

template<class K, class V> struct item<K, V>* add_item(struct item<K, V>* items, K key, V value);

template<class K, class V> struct item<K, V>* find_item_by_key(struct item<K, V>* items, K key);

template<class K, class V> struct item<K, V>* find_item_by_value(struct item<K, V>* items, V value);

#endif
