#include <assert.h>
#include "../util/test.hpp"
#include "vector.hpp"
using namespace Nostd;

int main() {
  it("constructs a vector with no elements", {
    Vector<int> v;
    assert(v.size() == 0);
    assert(v.capacity() == 1);
  });
  it("constructs a vector with a given size", {
    Vector<int> v(58);
    assert(v.size() == 58);
    assert(v.capacity() == 87);
  });
  it("constructs a vector containing n times the given element", {
    Vector<int> v(20, 79);
    assert(v.size() == 20);
    assert(v.capacity() == 30);
    for (size_t i = 0; i < v.size(); i++)
      assert(v[i] == 79);
  });
  it("adds one element to the array", {
    Vector<int> v;
    v.push_back(1337);
    assert(v.at(0) == 1337);
  });
  it("cleans the vector", {
    Vector<int> v;
    v.push_back(124);
    v.push_back(1268);
    v.push_back(1594);
    v.clear();
    assert(v.size() == 0);
    assert(v.capacity() == 1);
  });
  it("removes one element from the vector", {
    Vector<int> v;
    v.push_back(124);
    v.push_back(1268);
    v.push_back(1594);
    v.erase(1);
    assert(v.size() == 2);
    assert(v[0] == 124);
    assert(v[1] == 1594);
  });
}