/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Andreea Scrob #989372
  03/24/2021

  vector.test.hpp: tests for Nostd::Vector
*/
#include "vector.hpp"
#include "pair.hpp"
#include "test.hpp"
#include <cassert>

using namespace Nostd;

int touched = 0;

int main() {
  it("constructs a vector with no elements", [] {
    Vector<int> v;
    assert(v.size() == 0);
    assert(v.capacity() == 1);
  });

  it("constructs a vector with a given size", [] {
    Vector<int> v(58);
    assert(v.size() == 58);
    assert(v.capacity() == 87);
  });

  it("constructs a vector containing n times the given element", [] {
    Vector<int> v(20, 79);
    assert(v.size() == 20);
    assert(v.capacity() == 30);
    for (size_t i = 0; i < v.size(); i++)
      assert(v[i] == 79);
  });

  it("constructs a vector as a copy of another one", [] {
    Vector<int> original;
    for (size_t i = 0; i < 100; i++)
      original.push_back(i);

    Vector<int> cpy = Vector<int>(original);
    for (size_t i = 0; i < 100; i++)
      assert(cpy[i] == original[i]);
  });

  it("constructs a vector by moving the data from another one", [] {
    Vector<int> original;
    for (size_t i = 0; i < 100; i++)
      original.push_back(i);

    Vector<int> cpy = original;
    for (size_t i = 0; i < 100; i++)
      assert(cpy[i] == original[i]);
  });

  it("adds one element to the vector", [] {
    Vector<int> v;
    v.push_back(1337);
    assert(v.at(0) == 1337);
  });

  it("cleans the vector", [] {
    Vector<int> v;
    v.push_back(124);
    v.push_back(1268);
    v.push_back(1594);
    v.clear();
    assert(v.size() == 0);
    assert(v.capacity() == 1);
  });

  it("removes one element from the vector", [] {
    Vector<int> v;
    v.push_back(124);
    v.push_back(1268);
    v.push_back(1594);
    v.erase(1);
    assert(v.size() == 2);
    assert(v[0] == 124);
    assert(v[1] == 1594);
  });

  it("resizes the vector to the given length", [] {
    Vector<int> v;
    for (int i = 0; i < 100; i++) {
      v.push_back(i);
    }

    v.resize(50);

    for (int i = 0; i < 50; i++)
      assert(v[i] == i);
  });

  it("accepts complex elements as values", [] {
    Vector<Pair<int, int>> v;
    Pair<int, int> p = {1, 1};
    v.push_back(p);
    assert(v[0] == p);
  });

  class A {
  public:
    A() { touched++; }
    A(const A &) { touched++; }
  };

  it("allocates but does not construct elements", [] {
    Vector<A> v(5);
    assert(touched == 0);
  });

  it("allocates and constructs elements", [] {
    A test;
    Vector<A> v(5, test);
    assert(touched == 6); // 5 constructed classes plus the `test` instance
  });

  it("iterates forward", [] {
    Vector<size_t> v;
    for (size_t i = 0; i < 100; i++)
      v.push_back(i);

    size_t i = 0;
    for (auto x : v) {
      assert(x == i);
      i++;
    }
  });

  it("iterates backwards", [] {
    Vector<size_t> v;
    for (size_t i = 0; i < 100; i++)
      v.push_back(i);

    size_t i = 99;
    for (auto z = v.rbegin(); z != v.rend(); z++) {
      auto x = *z;
      assert(x == i);
      i--;
    }
  });

  it("iterates forward without modifying", [] {
    Vector<size_t> v;
    for (size_t i = 0; i < 100; i++)
      v.push_back(i);

    size_t i = 0;
    for (auto z = v.cbegin(); z != v.cend(); z++) {
      auto x = *z;
      assert(x == i);
      i++;
    }
  });

  it("iterates backward without modifying", [] {
    Vector<size_t> v;
    for (size_t i = 0; i < 100; i++)
      v.push_back(i);

    size_t i = 99;
    for (auto z = v.crbegin(); z != v.crend(); z++) {
      auto x = *z;
      assert(x == i);
      i--;
    }
  });
}
