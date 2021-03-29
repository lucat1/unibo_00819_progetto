/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  03/05/2021

  pair.test.cpp: tests the few pair functionality we have implemented
*/
#include "pair.hpp"
#include "test.hpp"
#include <cassert>
#include <cstring>
#include <sstream>
using Nostd::it;
using namespace Nostd;

int main() {
  Pair<char, char> p1 = {'a', 'b'};
  Pair<char, char> p2 = {'a', 'b'};
  Pair<char, char> p3 = {'c', 'd'};
  it("appropriately checks == of two pairs", [p1, p2] { assert(p1 == p2); });

  it("appropriately checks != of two pairs", [p1, p3] { assert(p1 != p3); });

  it("prints a pair to output stream", [] {
    Pair<char, char> pair = {'k', 'v'};
    std::stringstream out;
    out << pair;
    assert(strcmp(out.str().c_str(), "(k,v)") == 0);
  });
}
