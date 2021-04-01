#ifndef __NOSTD_MAP_HPP__
#define __NOSTD_MAP_HPP__

#include "pair.hpp"
#include "vector.hpp"

namespace Nostd {

/*
 * Map
 *
 * Pure virtual class extended by Nostd::UnorderedMap and Nostd::TreeMap
 *
 * */

template <typename K, typename V> class Map {
public:
  /// Insert a new pair Key Value
  virtual void put(K key, V value) = 0;

  /// Remove a key and its value
  virtual void remove(K key) = 0;

  /// Check wheter the map has no keys
  virtual bool empty() = 0;

  /// Check wheter the map contains the key
  virtual bool contains(K key) = 0;

  /// Returns all the values inside the map as Nostd::Vector<V>
  virtual Nostd::Vector<V> get_values() = 0;

  /// Returns all the Key-Values pairs as Nostd::Vector<Nostd::Pair<K,V>>
  virtual Nostd::Vector<Nostd::Pair<K, V>> as_vector() = 0;

  virtual V &operator[](K key) = 0;
};

} // namespace Nostd

#endif
