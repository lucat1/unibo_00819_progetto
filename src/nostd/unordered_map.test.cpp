
/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  04/01/2021

  unordered_map.test.cpp: tests for Nostd::UnorderedMap.
*/

#include "../util/test.hpp"
#include "unordered_map.hpp"
#include <cassert>

using namespace Nostd;

int main() {
  it("puts elements into  an umap", {
    Nostd::UnorderedMap<int, int> um;
    um.put(2, 5);
    um.put(4, 10);
    um.put(1, 23);
    um.put(5, 111);
  });
  it("operator []", {
    Nostd::UnorderedMap<int, int> um;
    um.put(2, 5);
    um[2] = 10;
    assert(um[2] == 10);
  });

  it("gets values from a umap", {
    Nostd::UnorderedMap<int, int> um;
    um.put(2, 5);
    um.put(4, 25);
    auto v = um.get_values();
    assert(v.size() == 2);
  });

  it("checks wheter an umap contains an element or not", {
    Nostd::UnorderedMap<int, int> um;
    um.put(4, 5);
    assert(um.contains(4));
  });

  it("removes and element from an umap", {
    Nostd::UnorderedMap<int, int> um;
    um.put(4, 5);
    um.put(10, 15);
    um.remove(4);
    assert(um.get_values().size() == 1);
  });

  return 0;
}
