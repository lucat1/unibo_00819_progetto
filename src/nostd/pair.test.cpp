#include "../nostd/test.hpp"
#include "pair.hpp"
#include <assert.h>
using namespace Nostd;

int main() {
  Pair<char, char> p1 = {'a', 'b'};
  Pair<char, char> p2 = {'a', 'b'};
  Pair<char, char> p3 = {'c', 'd'};
  it("appropriately checks == of two pairs", [p1, p2] { assert(p1 == p2); });

  it("appropriately checks != of two pairs", [p1, p3] { assert(p1 != p3); });
}
