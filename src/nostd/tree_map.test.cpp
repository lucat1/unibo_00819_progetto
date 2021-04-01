/*
  UniversNostd::ity of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  04/01/2021

  tree_map.test.cpp: tests for Nostd::TreeMap.
*/

#include "test.hpp"
#include "tree_map.hpp"

int main() {

  Nostd::it("puts elements into tmap", [] {
    Nostd::TreeMap<int, int> tm;
    tm.put(2, 5);
    tm.put(4, 10);
    tm.put(1, 23);
    tm.put(5, 111);
  });

  Nostd::it("tests operator []", [] {
    Nostd::TreeMap<int, int> tm;
    tm.put(2, 5);
    tm[2] = 10;
    assert(tm[2] == 10);
  });

  Nostd::it("gets values of tmap", [] {
    Nostd::TreeMap<int, int> tm;
    tm.put(2, 5);
    tm.put(4, 25);
    auto v = tm.get_values();
    assert(v.size() == 2);
  });

  Nostd::it("checks wheter the tmap contains an element", [] {
    Nostd::TreeMap<int, int> tm;
    tm.put(4, 5);
    assert(tm.contains(4));
  });

  Nostd::it("removes an element from the tmap", [] {
    Nostd::TreeMap<int, int> tm;
    tm.put(4, 5);
    tm.put(14, 10);
    tm.remove(4);
    assert(tm.get_values().size() == 1);
  });

  Nostd::it("puts elements into tmap", [] {
    Nostd::TreeMap<int, int> tm;
    tm.put(2, 5);
    tm.put(4, 10);
    tm.put(1, 23);
    tm.put(5, 111);
    tm.clear();
    assert(tm.get_values().size() == 0);
  });

  return 0;
}
