#ifndef UNORDEREDMAP_HPP
#define UNORDEREDMAP_HPP

#include "map.hpp"
#include "pair.hpp"
#include "vector.hpp"
#include <exception>

namespace Nostd {
template <typename K, typename V> class UnorderedMap : public Map<K, V> {
private:
  Nostd::Vector<Nostd::Pair<K, V>> data;

public:
  UnorderedMap() { data = Nostd::Vector<Nostd::Pair<K, V>>(); }

  ~UnorderedMap() { delete data; }

  void add(K key, V value) override {
    for (auto &x : data) {
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
        data.erase(this->data.begin() + i);
        return;
      }
  }

  bool empty() override { return this->data.empty(); }

  // Check if the map contains an element
  bool contains(K key) override {
    // todo: waiting for noNostd::Vector implementation
    for (auto &x : this->data)
      if (key == x.first)
        return true;
    return false;
  }

  // Returns all the value in a Nostd::Vector<T>
  Nostd::Vector<V> get_values() override {
    Nostd::Vector<V> res;
    for (auto &x : this->data)
      res.push_back(x.second);
    return res;
  }

  // Returns all the key-values as a Nostd::Vector<Nostd::Pair<K,V>>
  Nostd::Vector<Nostd::Pair<K, V>> as_vector() override { return this->data; }

  // Access a value from his key
  V &operator[](K key) override {
    for (auto &x : this->data)
      if (x.first == key)
        return x.second;
    throw std::invalid_argument("UnorderedMap: No value found for that key");
  }
};

} // namespace Nostd
#endif
