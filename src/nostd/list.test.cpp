#include <assert.h>
#include "../util/test.hpp"
#include "list.hpp"
using namespace Nostd;

int main() {
  it("constructs a list with no elements", {
    List<int> l;
    assert(l.size() == 0);
  });
  // TODO: more tests

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
}