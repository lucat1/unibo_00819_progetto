/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  08/01/2021

  position.cpp: implementation of World::Position.
*/

#include "position.hpp"
#include "../data/map_chunk.hpp"
#include "fragment.hpp"
#include "world.hpp"

using namespace Engine;
using namespace Nostd;

using World::Fragment;
using World::Position;

Position::Position(const List<Fragment> *environment,
                   List<Fragment>::iterator fragment, size_t x, size_t y) {
  this->x = x;
  this->y = y;
  this->environment = environment;
  this->fragment = fragment;
}

List<Fragment>::iterator Position::get_fragment() const noexcept {
  return this->fragment;
}

bool Position::move_left() {
  if (x != 0)
    x--;
  else if (fragment != environment->begin()) {
    fragment = std::prev(fragment);
    x = fragment->tiles.extent(1) - 1;
  } else
    return false; // first column of the first chunk (and so we do nothing)
  return true;
}

bool Position::move_right() {
  if (x != fragment->tiles.extent(1) - 1)
    x++;
  else {
    if (fragment == environment->end())
      return false; // last column of the last chunk (and so we do nothing)
    fragment = std::next(fragment);
    x = 0;
  }
  return true;
}

bool Position::move_up() {
  if (!y)
    return false; // first row (and so we do nothing)
  --y;
  return true;
}

bool Position::move_down() {
  if (y == Data::MapChunk::height - 1) // last row (and so we do nothing)
    return false;
  ++y;
  return true;
}

size_t Position::get_x() const noexcept { return this->x; }

size_t Position::get_y() const noexcept { return this->y; }
