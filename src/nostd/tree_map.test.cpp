/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  04/01/2021

  tree_map.test.cpp: tests for Nostd::TreeMap.
*/

#include "test.hpp"
#include "tree_map.hpp"
#include <cassert>

using namespace Nostd;

int main() {
  it("puts elements into tmap", [] {
    TreeMap<int, int> tm;
    tm.put(2, 5);
    tm.put(4, 10);
    tm.put(1, 23);
    tm.put(5, 111);
  });

  it("tests operator []", [] {
    TreeMap<int, int> tm;
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

  it("gets values of tmap", [] {
    TreeMap<int, int> tm;
    tm.put(2, 5);
    tm.put(4, 25);
    auto v = tm.get_values();
    assert(v.size() == 2);
  });

  it("checks the size of the tmap", [] {
    TreeMap<int, int> tm;
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

  it("checks wheter the tmap contains an element", [] {
    TreeMap<int, int> tm;
    tm.put(4, 5);
    assert(tm.contains(4));
    assert(!tm.contains(5));
  });

<<<<<<< HEAD
  Nostd::it("removes leaf", [] {
    Nostd::TreeMap<int, int> tm;
=======
  it("removes leaf", [] {
    TreeMap<int, int> tm;
>>>>>>> 80b891c9a6382910e38e2460f2bbe7cd76405ac2
    tm.put(10, 10);
    tm.put(5, 5);
    tm.remove(5);
    assert(tm.size() == 1);
  });

  it("removes single childed node", [] {
    TreeMap<int, int> tm;
    // remove left left
    tm.put(10, 10);
    tm.put(5, 5);
    tm.put(4, 4);
    tm.remove(5);
    assert(tm.size() == 2);

    // remove left right
    tm.put(5, 5);
    tm.remove(4);
    assert(tm.size() == 2);

    // remove right left
    tm.put(20, 20);
    tm.put(15, 15);
    tm.remove(20);
    assert(tm.size() == 3);

    // remove right right
    tm.put(20, 20);
    tm.remove(15);
    assert(tm.size() == 3);
  });

  it("removes node with two children", [] {
    TreeMap<int, int> tm;
    tm.put(10, 10);
    tm.put(5, 5);
    tm.put(6, 6);
    tm.put(3, 3);
    tm.put(1, 1);
    tm.remove(5);
    assert(tm.size() == 4);
  });

  it("puts elements into tmap", [] {
    TreeMap<int, int> tm;
    tm.put(2, 5);
    tm.put(4, 10);
    tm.put(1, 23);
    tm.put(5, 111);
    tm.clear();
    assert(tm.size() == 0);
  });

  Nostd::it("gets tmap's pairs as Vector", [] {
    Nostd::TreeMap<int, int> tm;
    tm.put(2, 5);
    tm.put(4, 10);
    tm.put(1, 23);
    assert(tm.as_vector().size() == 3);
  });

  return 0;
}
