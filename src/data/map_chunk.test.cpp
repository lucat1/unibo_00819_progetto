/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/09/2021

  map_chunk.test.cpp: tests for Data::MapChunk and its helper entities.
*/

#include <cassert>

#include "../nostd/test.hpp"
#include "map_chunk.hpp"

using Data::MapChunk;
using Data::MapUnit;
using Nostd::it;

int main() {
  it("constructs a Map", [] {
    MapChunk m(2, MapUnit::ground);
    for (auto &row : m)
      for (auto &cell : row)
        assert(cell.value() == MapUnit::ground);
  });
  it("returns the right", [] {
    MapChunk m(33);
    assert(m.width() == 33);
  });
}
