#include "position.hpp"

using namespace World;

void Position::move_left() noexcept {
  if (x != 0)
    x--;
  else if (*fragment != *environment.begin()) {
    fragment = std::prev(fragment);
    x = (*fragment).extent(1) - 1;
  }
}

void Position::move_right() noexcept {
  if ((size_t)x != (*fragment).extent(1) - 1)
    x++;
  else {
    fragment = std::next(fragment);
    x = 0;
  }
}

void Position::move_up() noexcept {
  // TODO
}

void Position::move_down() noexcept {
  // TODO
}

int Position::get_x() const noexcept { return this->x; }
int Position::get_y() const noexcept { return this->y; }
void Position::set_x(const int &x) noexcept { this->x = x; }
void Position::set_y(const int &y) noexcept { this->y = y; }
