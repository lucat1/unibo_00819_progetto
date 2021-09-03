/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  04/01/2021

  unordered_map.cpp: Implementation of Nostd::UnorderedMap, built using a
  Nostd::Vector<Nostd::Pair<K,V>>.
  Please refer to Nostd::Map for method's documentation.

  WARNING: It does not allow duplicate
*/

#ifndef NOSTD_UNORDEREDMAP_HPP
#define NOSTD_UNORDEREDMAP_HPP

#include "map.hpp"
#include "pair.hpp"
#include "vector.hpp"
#include <exception>
#include <iterator>

namespace Nostd {

template <typename K, typename V> class UnorderedMap : public Map<K, V> {
private:
  Nostd::Vector<Nostd::Pair<const K, V> *> data;

public:
  using iterator = typename Nostd::Vector<Nostd::Pair<const K, V> *>::iterator;
  using reverse_iterator =
      typename Nostd::Vector<Nostd::Pair<const K, V> *>::reverse_iterator;
  using const_iterator =
      const typename Nostd::Vector<Nostd::Pair<const K, V> *>::const_iterator;
  using const_reverse_iterator = const typename Nostd::Vector<
      Nostd::Pair<const K, V> *>::const_reverse_iterator;

  UnorderedMap() {}

  /*
    Add new key and value to the map
   */
  void put(K key, V value) noexcept override {
    for (size_t i = 0; i < data.size(); i++) {
      Nostd::Pair<const K, V> *x = data[i];
      if (x->first == key) {
        x->second = value;
        return;
      }
    }
    data.push_back(new Nostd::Pair<const K, V>(key, value));
  }

  /*
    Removes a key and its value form the map
   */
  void remove(K key) noexcept override {
    for (size_t i = 0; i < this->data.size(); i++)
      if (data[i]->first == key) {
        delete data[i];
        data.erase(i);
        return;
      }
  }

  /*
    Checks wheter the map is empty or not
   */
  bool empty(void) const noexcept override { return this->data.empty(); }

  /*
    Checks wheter the map contains the key given in input
   */
  bool contains(const K &key) const noexcept override {
    for (size_t i = 0; i < this->data.size(); i++)
      if (key == data[i]->first)
        return true;
    return false;
  }

  /*
    Returns the number of keys inside the map
   */
  size_t size(void) const noexcept override { return this->data.size(); }

  /*
    Returns a Nostd::Vector with all the values stored into the map
   */
  Nostd::Vector<V> get_values(void) const noexcept override {
    Nostd::Vector<V> res(this->data.size());
    for (size_t i = 0; i < this->data.size(); i++)
      res[i] = data[i]->second;
    return res;
  }

  /*
    Returns a Vector representation of the map
   */
  Nostd::Vector<Nostd::Pair<const K, V> *>
  as_vector(void) const noexcept override {
    return this->data;
  }

  /*
    Removes all the keys and values from the map
   */
  void clear(void) noexcept override { data.clear(); }

  /*
    Access the value of the key given in input
   */
  V &operator[](const K &key) override {
    for (size_t i = 0; i < this->data.size(); i++)
      if (data[i]->first == key)
        return data[i]->second;
    throw std::invalid_argument("UnorderedMap: No value found for that key");
  }

  /*
    Access the value of the key given in input
   */
  const V &operator[](const K &key) const override {
    for (size_t i = 0; i < this->data.size(); i++)
      if (data[i]->first == key)
        return data[i]->second;
    throw std::invalid_argument("UnorderedMap: No value found for that key");
  }

  /*
    Iterator methods
   */
  iterator begin(void) noexcept { return this->data.begin(); }
  iterator end(void) noexcept { return this->data.end(); }

  const_iterator cbegin(void) const noexcept { return this->data.cbegin(); }
  const_iterator cend(void) const noexcept { return this->data.cend(); }

  reverse_iterator rbegin(void) const noexcept { return this->data.rbegin(); }
  reverse_iterator rend(void) const noexcept { return this->data.rend(); }
};

} // namespace Nostd
#endif
