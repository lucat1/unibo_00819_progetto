/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  01/08/2021

  position.cpp: Implementation of World::WPosition.
*/

#include "position.hpp"
#include "../data/map_chunk.hpp"
#include "world.hpp"
#include <functional>

using namespace Nostd;
using namespace Engine;

using WPosition = World::Position;
using WWorld = World::World;

WPosition::Position(const List<Matrix<BlockTile *>> *environment, int x,
                    int y) {
  this->x = x;
  this->y = y;
  this->environment = environment;
  this->fragment = environment->begin();
}

void WPosition::move_left() {
  if (x != 0)
    x--;
  else if (*fragment != *environment->begin()) {
    fragment = std::prev(fragment);
    x = (*fragment).extent(1) - 1;
  }
  // else we are in the first column of the first chunk so we do nothing
}

void WPosition::move_right() {
  if ((size_t)x != (*fragment).extent(1) - 1)
    x++;
  else {
    if (*fragment == *environment->end()) {
      // TODO invoke World::World::add_chunks()
    }
    fragment = std::next(fragment);
    x = 0;
  }
}

List<Matrix<BlockTile *>>::iterator WPosition::get_fragment() const noexcept {
  return this->fragment;
}
void WPosition::move_up() { y = std::max(y - 1, 0); }

void WPosition::move_down() {
  y = std::min(y + 1, (int)Data::MapChunk::height - 1);
}

int WPosition::get_x() const noexcept { return this->x; }
int WPosition::get_y() const noexcept { return this->y; }
