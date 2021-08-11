/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/09/2021

  map_chunk.cpp: implementation of Data::MapChunk and its helper entities.
*/

#include "map_chunk.hpp"

#include <stdexcept>

using Data::MapChunk;
using Data::MapUnit;

std::istream &Data::operator>>(std::istream &i, MapUnit &m) {
  char c;
  if (i >> c)
    m = static_cast<MapUnit>(c);
  return i;
}

MapChunk::MapChunk(size_t width, MapUnit value)
    : Nostd::Matrix<MapUnit>({height, width}, value) {}

size_t MapChunk::width() const noexcept { return extent(1); }

std::istream &Data::operator>>(std::istream &i, MapChunk &m) {
  size_t w;
  if (i >> w) {
    m = MapChunk(w);
    for (auto &row : m) {
      i.ignore();
      for (auto &cell : row)
        i >> cell.value();
    }
    i.ignore();
  }
  return i;
}
