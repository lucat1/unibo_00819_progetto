#include "../util/test.hpp"
#include "pair.hpp"
#include <assert.h>
using namespace Nostd;

int main() {
  Pair<char, char> p1 = {'a', 'b'};
  Pair<char, char> p2 = {'a', 'b'};
  Pair<char, char> p3 = {'c', 'd'};
  it("appropriately checks equality of two pairs", { assert(p1 == p2); });

  it("appropriately checks !equality of two pairs", { assert(p1 != p3); });
}
