/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/09/2021

  map.test.cpp: tests for Data::Map.
*/

#include <cassert>

#include "../nostd/test.hpp"
#include "map.hpp"

using Data::Map;
using Data::MapUnit;
using Nostd::it;

int main() {
  it("constructs a Map", [] {
    Map m(2, MapUnit::ground);
    for (auto &row : m)
      for (auto &cell : row)
        assert(cell.value() == MapUnit::ground);
  });
  it("returns the right width", [] { assert(Map(33).width() == 33); });
}
