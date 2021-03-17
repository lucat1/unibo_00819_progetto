#include "../util/test.hpp"
#include "vector.hpp"
#include <assert.h>
using namespace Nostd;

int main() {
  it("adds 1 element to the array", {
    Vector<int> v;
    v.push_back(1337);
    assert(v.at(0) == 1337);
  })
}
