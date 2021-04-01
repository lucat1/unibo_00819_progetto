/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  04/01/2021

  tree_map.test.cpp: tests for Nostd::TreeMap.
*/

#include "../util/test.hpp"
#include "tree_map.hpp"

using namespace Nostd;

int main() {
  // Treemap

  it("puts elements into tmap", {
    Nostd::TreeMap<int, int> um;
    um.put(2, 5);
    um.put(4, 10);
    um.put(1, 23);
    um.put(5, 111);
  });
  it("tests operator []", {
    Nostd::TreeMap<int, int> um;
    um.put(2, 5);
    um[2] = 10;
    assert(um[2] == 10);
  });

  it("gets values of tmap", {
    Nostd::TreeMap<int, int> um;
    um.put(2, 5);
    um.put(4, 25);
    auto v = um.get_values();
    assert(v.size() == 2);
  });

  it("checks wheter the tmap contains an element", {
    Nostd::TreeMap<int, int> um;
    um.put(4, 5);
    assert(um.contains(4));
  });

  it("removes an element from the tmap", {
    Nostd::TreeMap<int, int> um;
    um.put(4, 5);
    um.put(14, 10);
    um.remove(4);
    assert(um.get_values().size() == 1);
  });
  return 0;
}
