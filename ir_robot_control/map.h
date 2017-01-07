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


template<class K, class V> struct item<K, V>* createItem(K key, V value);

template<class K, class V> struct item<K, V>* addItem(struct item<K, V>* items, K key, V value);

template<class K, class V> struct item<K, V>* findItemByKey(struct item<K, V>* items, K key);

template<class K, class V> struct item<K, V>* findItemByValue(struct item<K, V>* items, V value);

#endif
