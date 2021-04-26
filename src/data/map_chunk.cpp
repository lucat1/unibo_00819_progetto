/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/09/2021

  map_chunk.cpp: implementation of Data::MapChunk.
*/

#include "map_chunk.hpp"

#include <stdexcept>

using Data::MapChunk;
using Data::MapUnit;

std::basic_istream<char> &Data::operator>>(std::basic_istream<char> &i,
                                           MapUnit &m) {
  m = static_cast<MapUnit>(i.get());
  return i;
}

MapChunk::MapChunk(size_t width, size_t starting_row, MapUnit value)
    : Nostd::Matrix<MapUnit>({height, width}, value) {
  if (starting_row >= height) {
    strt_row = 0;
    throw std::invalid_argument("starting_row >= height");
  }
  strt_row = starting_row;
}

size_t MapChunk::width() const noexcept { return extent(1); }

size_t MapChunk::starting_row() const noexcept { return strt_row; }

std::basic_istream<char> &Data::operator>>(std::basic_istream<char> &i,
                                           MapChunk &m) {
  size_t w, s;
  if (i >> w >> s) {
    m = MapChunk(w, s);
    for (auto &row : m) {
      i.ignore();
      for (auto &cell : row)
        i >> cell.value();
    }
    i.ignore();
  }
  return i;
}
