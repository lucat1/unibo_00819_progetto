/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/09/2021

  map_chunk.cpp: implementation of Data::MapChunk.
*/

#include "map_chunk.hpp"

using Data::MapChunk;
using Data::MapUnit;

std::basic_istream<char> &Data::operator>>(std::basic_istream<char> &i,
                                           MapUnit &m) {
  m = static_cast<MapUnit>(i.get());
  return i;
}

MapChunk::MapChunk(size_t width, MapUnit value)
    : Nostd::Matrix<MapUnit>({height, width}, value) {}

size_t MapChunk::width() const noexcept { return extent(1); }

std::basic_istream<char> &Data::operator>>(std::basic_istream<char> &i,
                                           MapChunk &m) {
  size_t w;
  i >> w;
  m = MapChunk(w);
  for (auto &row : m) {
    i.ignore();
    for (auto &cell : row)
      i >> cell.value();
  }
  return i;
}
