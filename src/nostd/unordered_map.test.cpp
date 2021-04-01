
/*
  UniversNostd::ity of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  04/01/2021

  unordered_map.test.cpp: tests for Nostd::UnorderedMap.
*/

#include "test.hpp"
#include "unordered_map.hpp"
#include <cassert>

int main() {
  Nostd::it("puts elements into  an umap", [] {
    Nostd::UnorderedMap<int, int> um;
    um.put(2, 5);
    um.put(4, 10);
    um.put(1, 23);
    um.put(5, 111);
  });
  Nostd::it("operator []", [] {
    Nostd::UnorderedMap<int, int> um;
    um.put(2, 5);
    um[2] = 10;
    assert(um[2] == 10);
  });

  Nostd::it("gets values from a umap", [] {
    Nostd::UnorderedMap<int, int> um;
    um.put(2, 5);
    um.put(4, 25);
    Nostd::Vector<int>  v = um.get_values();
    std::cout << v.size() << std::endl;
    assert(v.size() == 2);
  });

  Nostd::it("checks wheter an umap contains an element or not", [] {
    Nostd::UnorderedMap<int, int> um;
    um.put(4, 5);
    assert(um.contains(4));
  });

  Nostd::it("removes and element from an umap", [] {
    Nostd::UnorderedMap<int, int> um;
    um.put(4, 5);
    um.put(10, 15);
    um.remove(4);
    assert(um.get_values().size() == 1);
  });

  Nostd::it("clears the umap", [] {
    Nostd::UnorderedMap<int, int> um;
    um.put(2, 5);
    um.put(4, 10);
    um.put(1, 23);
    um.put(5, 111);
    um.clear();
    assert(um.get_values().size() == 0);
  });

  return 0;
}
