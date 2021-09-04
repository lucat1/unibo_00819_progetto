/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Andreea Scrob #989372
  03/27/2021

  list.test.cpp: tests for Nostd::List
*/

#include "list.hpp"
#include "test.hpp"

#include <cassert>

using namespace Nostd;

int main() {
  it("constructs a list with no elements", [] {
    List<int> l;
    assert(l.size() == 0);
  });

  it("pushes an element in front of the list", [] {
    List<int> l;
    l.push_front(5);
    assert(l.front() == 5);
    assert(l.back() == 5);
  });

  it("pushes an element at the end of the list", [] {
    List<int> l;
    l.push_back(5);
    assert(l.front() == 5);
    assert(l.back() == 5);
  });

  it("has the same head and tail with just one element", [] {
    List<int> l;
    l.push_back(97);
    assert(l.front() == l.back());
  });

  it("deletes the first element in front of the list", [] {
    List<int> l;
    l.push_back(5);
    l.push_back(9);
    l.push_front(7);
    l.push_back(8);
    l.pop_front();
    assert(l.front() == 5);
  });

  it("deletes the last element at the end of the list", [] {
    List<int> l;
    l.push_back(7);
    l.push_back(27);
    assert(l.size() == 2);
    l.pop_back();
    assert(l.size() == 1);
    assert(l.front() == 7);
  });

  it("changes the length of the list", [] {
    List<int> l;
    l.push_back(278);
    l.push_back(490);
    l.push_back(89);
    l.resize(2, 8);
    assert(l.front() == 278);
    assert(l.back() == 490);
    assert(l.size() == 2);
  });

  it("inserts new elements", [] {
    List<int> l;
    l.insert(l.begin(), 3);
    l.insert(l.begin(), 1);
    l.insert(l.end(), 4);
    l.insert(++l.begin(), 2);
    auto p = l.begin();
    assert(*p == 1);
    p++;
    assert(*p == 2);
    p++;
    assert(*p == 3);
    p++;
    assert(*p == 4);
  });

  it("removes matching values", [] {
    List<int> l;
    l.push_back(8);
    l.push_back(89);
    l.push_back(9);
    l.remove(9);
    assert(l.front() == 8);
    assert(l.back() == 89);
    assert(l.size() == 2);
  });

  it("copy content from another list", [] {
    List<int> l;
    l.push_back(3);
    l.push_back(6);
    List<int> m(l);
    assert(l.size() == m.size());
    assert(l.front() == m.front());
    assert(l.back() == m.back());
  });

  it("moves its elements to another list", [] {
    List<int> l;
    l.push_back(3);
    l.push_back(6);
    List<int> m = l;
    assert(l.size() == m.size());
    assert(l.front() == m.front());
    assert(l.back() == m.back());
  });
  it("iterates forward", [] {
    List<size_t> l;
    for (size_t i = 0; i < 100; i++)
      l.push_back(i);

    size_t i = 0;
    for (auto x : l) {
      assert(x == i);
      i++;
    }
  });

  it("iterates backwards", [] {
    List<size_t> l;
    for (size_t i = 0; i < 100; i++)
      l.push_back(i);

    size_t i = 99;
    for (auto z = l.rbegin(); z != l.rend(); z++) {
      auto x = *z;
      assert(x == i);
      i--;
    }
  });

  it("iterates forward without modifying", [] {
    List<size_t> l;
    for (size_t i = 0; i < 100; i++)
      l.push_back(i);

    size_t i = 0;
    for (auto z = l.cbegin(); z != l.cend(); z++) {
      auto x = *z;
      assert(x == i);
      i++;
    }
  });

  it("iterates backward without modifying", [] {
    List<size_t> l;
    for (size_t i = 0; i < 100; i++)
      l.push_back(i);

    size_t i = 99;
    for (auto z = l.crbegin(); z != l.crend(); z++) {
      auto x = *z;
      assert(x == i);
      i--;
    }
  });
}
