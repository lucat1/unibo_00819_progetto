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
  Map: pure virtual class extended by Nostd::UnorderedMap and Nostd::TreeMap
 */

template <typename K, typename V> class Map {
public:
  /*
   Insert a new pair Key Value
  */
  virtual void put(K key, V value) = 0;

  /*
    Remove a key and its value
   */
  virtual void remove(K key) = 0;

  /*
    Check wheter the map has no keys
   */
  virtual bool empty(void) const = 0;

  /*
    Check wheter the map contains the key
   */
  virtual bool contains(const K &key) const = 0;

  /*
    Remove all elements
   */
  virtual void clear(void) = 0;

  /*
    Returns all the values inside the map as Nostd::Vector<V>
   */
  virtual Nostd::Vector<V> get_values(void) const = 0;

  /*
    Returns all the Key-Values pairs as Nostd::Vector<Nostd::Pair<K,V>>
   */
  virtual Nostd::Vector<Nostd::Pair<const K, V> *> as_vector(void) const = 0;

  /*
    Returns the number of elements inside the map
   */
  virtual size_t size(void) const = 0;

  /*
    Access a value from its key
   */
  virtual V &operator[](const K &key) = 0;

  /*
    Access a value from its key
   */
  virtual const V &operator[](const K &key) const = 0;
};

} // namespace Nostd

#endif
