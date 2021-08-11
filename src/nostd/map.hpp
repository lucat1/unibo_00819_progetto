/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  04/01/2021

  map.cpp: Nostd::Map definition.
*/

#ifndef NOSTD_MAP_HPP
#define NOSTD_MAP_HPP

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
  virtual bool empty() const = 0;

  /// Check wheter the map contains the key
  virtual bool contains(K key) const = 0;

  /// Remove all elements
  virtual void clear() = 0;

  /// Returns all the values inside the map as Nostd::Vector<V>
  virtual Nostd::Vector<V> get_values() const = 0;

  /// Returns all the Key-Values pairs as Nostd::Vector<Nostd::Pair<K,V>>
  virtual Nostd::Vector<Nostd::Pair<const K, V> *> as_vector() const = 0;

  virtual size_t size() const = 0;

  virtual V &operator[](K key) = 0;

  virtual const V &operator[](K key) const = 0;
};

} // namespace Nostd

#endif
