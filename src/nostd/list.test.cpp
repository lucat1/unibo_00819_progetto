#include <assert.h>
#include "../util/test.hpp"
#include "list.hpp"
using namespace Nostd;

int main() {
  it("constructs a list with no elements", {
    List<int> l;
    assert(l.size() == 0);
  });

  it("pushes an element in front of the list", {
    List<int> l;
    l.push_front(5);
    assert(l.front() == 5);
    assert(l.back() == 5);
  });

  it("pushes an element at the end of the list", {
    List<int> l;
    l.push_back(5);
    assert(l.front() == 5);
    assert(l.back() == 5);
  });

  it("has the same head and tail with just one element", {
    List<int> l;
    l.push_back(97);
    assert(l.front() == l.back());
  });

  it("deletes the first element in front of the list", {
    List<int> l;
    l.push_back(5);
    l.push_back(9);
    l.push_front(7);
    l.push_back(8);
    l.pop_front();
    assert(l.front() == 5);
  });

  it("deletes the last element at the end of the list", {
    List<int> l;
    l.push_back(7);
    l.push_back(27);
    l.pop_back();
    assert(l.size() == 1);
    assert(l.front() == 7);
  });

  it("removes matching values", {
    List<int> l;
    l.push_back(8);
    l.push_back(89);
    l.push_back(9);
    l.remove(9);
    assert(l.front() == 8);
    assert(l.back() == 89);
    assert(l.size() == 2);
  });

  it("changes the length of the list", {
    List<int> l;
    l.push_back(278);
    l.push_back(490);
    l.push_back(89);
    l.resize(2, 8);
    assert(l.front() == 278);
    assert(l.back() == 490);
    assert(l.size() == 2);
  });

  it("copy content from another list", {
    List<int> l;
    l.push_back(3);
    l.push_back(6);
    List<int> m(l);
    assert(l.size() == m.size());
    assert(l.front() == m.front());
    assert(l.back() == m.back());
  });

  it("moves its elements to another list", {
    List<int> l;
    l.push_back(3);
    l.push_back(6);
    List<int> m = l;
    assert(l.size() == m.size());
    assert(l.front() == m.front());
    assert(l.back() == m.back());
  });
}