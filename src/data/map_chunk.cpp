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
  char c;
  if (i >> c)
    m = static_cast<MapUnit>(c);
  return i;
}

MapChunk::MapChunk(size_t width, size_t starting_row, size_t ending_row,
                   MapUnit value)
    : Nostd::Matrix<MapUnit>({height, width}, value) {
  if (starting_row >= height) {
    strt_row = 0;
    throw std::invalid_argument("strt_row >= height");
  }
  strt_row = starting_row;
  if (ending_row >= height) {
    end_row = 0;
    throw std::invalid_argument("end_row >= height");
  }
  end_row = ending_row;
}

size_t MapChunk::width() const noexcept { return extent(1); }

size_t MapChunk::starting_row() const noexcept { return strt_row; }

size_t MapChunk::ending_row() const noexcept { return end_row; }

std::basic_istream<char> &Data::operator>>(std::basic_istream<char> &i,
                                           MapChunk &m) {
  size_t w, s, e;
  if (i >> w >> s >> e) {
    m = MapChunk(w, s, e);
    for (auto &row : m) {
      i.ignore();
      for (auto &cell : row)
        i >> cell.value();
    }
    i.ignore();
  }
  return i;
}
