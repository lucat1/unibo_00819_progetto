#include "../util/test.hpp"
#include "pair.hpp"
#include <cassert>
#include <cstring>
#include <sstream>
using namespace Nostd;

int main() {
  Pair<char, char> p1 = {'a', 'b'};
  Pair<char, char> p2 = {'a', 'b'};
  Pair<char, char> p3 = {'c', 'd'};
  it("appropriately checks == of two pairs", { assert(p1 == p2); });

  it("appropriately checks != of two pairs", { assert(p1 != p3); });

  it("prints a pair to output stream", {
    Pair<char, char> pair = {'k', 'v'};
    std::stringstream out;
    out << pair;
    assert(strcmp(out.str().c_str(), "(k,v)") == 0);
  });
}
