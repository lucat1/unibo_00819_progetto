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

#include <iostream>

namespace Nostd {

template <typename K, typename V> class UnorderedMap : public Map<K, V> {
private:
  mutable Nostd::Vector<Nostd::Pair<K, V>> data;

public:
  UnorderedMap() {}

  // Add new key and value to the map
  void put(K key, V value) override {
    for (size_t i = 0; i < data.size(); i++) {
      Nostd::Pair<K, V> x = data[i];
      if (x.first == key) {
        x.second = value;
        return;
      }
    }
    data.push_back({key, value});
  }

  void remove(K key) override {
    for (size_t i = 0; i < this->data.size(); i++)
      if (data[i].first == key) {
        data.erase(i);
        return;
      }
  }

  bool empty() const override { return this->data.empty(); }

  bool contains(K key) const override {
    for (size_t i = 0; i < this->data.size(); i++)
      if (key == data[i].first)
        return true;
    return false;
  }

  size_t size() const override { return this->data.size(); }

  Nostd::Vector<V> get_values() const override {
    Nostd::Vector<V> res(this->data.size());
    for (size_t i = 0; i < this->data.size(); i++)
      res[i] = data[i].second;
    return res;
  }

  Nostd::Vector<Nostd::Pair<K, V>> as_vector() const override {
    return this->data;
  }

  void clear() override { data.clear(); }

  V &operator[](K key) override {
    for (size_t i = 0; i < this->data.size(); i++)
      if (data[i].first == key)
        return data[i].second;
    throw std::invalid_argument("UnorderedMap: No value found for that key");
  }

  const V &operator[](K key) const override {
    for (size_t i = 0; i < this->data.size(); i++)
      if (data[i].first == key)
        return data[i].second;
    throw std::invalid_argument("UnorderedMap: No value found for that key");
  }
};

} // namespace Nostd
#endif
