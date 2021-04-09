/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/09/2021

  map.cpp: implementation of Data::Map.
*/

#include "map.hpp"

using Data::Map;
using Data::MapUnit;

std::basic_istream<char> &operator>>(std::basic_istream<char> &i, MapUnit &m) {
  m = static_cast<MapUnit>(i.get());
  return i;
}

Map::Map(size_t width, MapUnit value)
    : Nostd::Matrix<MapUnit>({height, width}, value) {}

size_t Map::width() const noexcept { return extent(1); }

std::basic_istream<char> &operator>>(std::basic_istream<char> &i, Map &m) {
  size_t w;
  i >> w;
  m = Map(w);
  for (auto &row : m) {
    for (auto &cell : row)
      i >> cell.value();
    i.ignore();
  }
  return i;
}
