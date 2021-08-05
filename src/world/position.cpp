/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  01/08/2021

  position.cpp: Implementation of World::Position.
*/

#include "position.hpp"
#include "../data/map_chunk.hpp"

using namespace World;
using namespace Nostd;
using namespace Engine;

Position::Position(const List<Matrix<BlockTile *>> *environment, int x, int y) {
  this->x = x;
  this->y = y;
  this->environment = environment;
  this->fragment = environment->begin();
}

void Position::move_left() {
  if (x != 0)
    x--;
  else if (*fragment != *environment->begin()) {
    fragment = std::prev(fragment);
    x = (*fragment).extent(1) - 1;
  }
  // else we are in the first column of the first chunk so we do nothing
}

void Position::move_right() {
  if ((size_t)x != (*fragment).extent(1) - 1)
    x++;
  else {
    if (*fragment == *environment->end()) {
      // TODO generate more chunk
    }
    fragment = std::next(fragment);
    x = 0;
  }
}

List<Matrix<BlockTile *>>::iterator Position::get_fragment() const noexcept {
  return this->fragment;
}
void Position::move_up() { y = std::max(y - 1, 0); }

void Position::move_down() {
  y = std::min(y + 1, (int)Data::MapChunk::height - 1);
}

int Position::get_x() const noexcept { return this->x; }
int Position::get_y() const noexcept { return this->y; }
