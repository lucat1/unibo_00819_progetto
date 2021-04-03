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
#include <cassert>
#include <exception>
#include <stdexcept>

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
    bool ex = false;
    try {
      tm[22] = 12;
    } catch (std::invalid_argument &e) {
      ex = true;
    }
    assert(ex);
  });

  Nostd::it("gets values of tmap", [] {
    Nostd::TreeMap<int, int> tm;
    tm.put(2, 5);
    tm.put(4, 25);
    auto v = tm.get_values();
    assert(v.size() == 2);
  });

  Nostd::it("checks the size of the tmap", [] {
    Nostd::TreeMap<int, int> tm;
    tm.put(3, 4);
    tm.put(3, 4);
    tm.put(3, 4);
    tm.put(3, 4);
    tm.put(3, 4);
    assert(tm.size() == 1);
    tm.put(33, 4);
    tm.put(23, 4);
    assert(tm.size() == 3);
  });

  Nostd::it("checks wheter the tmap contains an element", [] {
    Nostd::TreeMap<int, int> tm;
    tm.put(4, 5);
    assert(tm.contains(4));
    assert(!tm.contains(5));
  });

  /*Nostd::it("removes an element from the tmap", [] {
    Nostd::TreeMap<int, int> tm;
    tm.put(10, 10);
    tm.put(5, 5);
    tm.put(3, 3);
    tm.put(6, 6);
    tm.put(20, 20);
    tm.put(1, 1);
    tm.remove(5);
    tm.remove(6);
    tm.remove(3);
    tm.remove(10);
    assert(tm.get_values().size() == 2);
  });
*/
  Nostd::it("Remove leaf", [] {
    Nostd::TreeMap<int, int> tm;
    tm.put(10, 10);
    tm.put(5, 5);
    tm.remove(5);
    assert(tm.size() == 1);
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
