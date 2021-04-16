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
#include <cstddef>
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

  ~UnorderedMap() {
    for (size_t i{0}; i < data.size(); i++)
      delete data[i];
  }
  // Add new key and value to the map
  void put(K key, V value) override {
    for (size_t i = 0; i < data.size(); i++) {
      Nostd::Pair<const K, V> *x = data[i];
      if (x->first == key) {
        x->second = value;
        return;
      }
    }
    data.push_back(new Nostd::Pair<const K, V>(key, value));
  }

  void remove(K key) override {
    for (size_t i = 0; i < this->data.size(); i++)
      if (data[i]->first == key) {
        delete data[i];
        data.erase(i);
        return;
      }
  }

  bool empty() const override { return this->data.empty(); }

  bool contains(K key) const override {
    for (size_t i = 0; i < this->data.size(); i++)
      if (key == data[i]->first)
        return true;
    return false;
  }

  size_t size() const override { return this->data.size(); }

  Nostd::Vector<V> get_values() const override {
    Nostd::Vector<V> res(this->data.size());
    for (size_t i = 0; i < this->data.size(); i++)
      res[i] = data[i]->second;
    return res;
  }

  Nostd::Vector<Nostd::Pair<const K, V> *> as_vector() const override {
    return this->data;
  }

  void clear() override { data.clear(); }

  V &operator[](K key) override {
    for (size_t i = 0; i < this->data.size(); i++)
      if (data[i]->first == key)
        return data[i]->second;
    throw std::invalid_argument("UnorderedMap: No value found for that key");
  }

  const V &operator[](K key) const override {
    for (size_t i = 0; i < this->data.size(); i++)
      if (data[i]->first == key)
        return data[i]->second;
    throw std::invalid_argument("UnorderedMap: No value found for that key");
  }

  iterator begin() { return this->data.begin(); }
  iterator end() { return this->data.end(); }

  const_iterator cbegin() const { return this->data.cbegin(); }
  const_iterator cend() const { return this->data.cend(); }

  reverse_iterator rbegin() const { return this->data.rbegin(); }
  reverse_iterator rend() const { return this->data.rend(); }
};

} // namespace Nostd
#endif
