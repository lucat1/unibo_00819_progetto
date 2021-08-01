/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  01/08/2021

  position.cpp: Implementation of World::Position.
*/

#include "position.hpp"
using namespace World;
using namespace Nostd;
using namespace Engine;

Position::Position(const List<Matrix<BlockTile *>> *environment, int x, int y) {
  this->environment = environment;
  this->fragment = environment->begin();
}

void Position::move_left() {
  if (x != 0)
    x--;
  else if (*fragment != *environment->begin()) {
    fragment = std::prev(fragment);
    x = (*fragment).extent(1) - 1;
  } else
    throw InvalidPositionException(x, y);
}

void Position::move_right() {
  if ((size_t)x != (*fragment).extent(1) - 1)
    x++;
  else {
    fragment = std::next(fragment);
    x = 0;
  }
}

void Position::move_up() { y = std::max(y - 1, 0); }

void Position::move_down() { y = std::min(y + 1, 24); }

int Position::get_x() const noexcept { return this->x; }
int Position::get_y() const noexcept { return this->y; }
