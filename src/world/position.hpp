/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  08/01/2021

  position.cpp: World::Position definition.
*/

#ifndef WORLD_POSITION_HPP
#define WORLD_POSITION_HPP

#include "../engine/block_tile.hpp"
#include "../engine/screen.hpp"
#include "../nostd/list.hpp"
#include "../nostd/matrix.hpp"
#include "fragment.hpp"
#include <iterator>

namespace World {

class Position {
private:
  const Nostd::List<Fragment> *environment;
  Nostd::List<Fragment>::iterator fragment;
  size_t x;
  size_t y;
  static const size_t INITIAL_Y = 19;

public:
  Position(const Nostd::List<Fragment> *environment,
           Nostd::List<Fragment>::iterator fragment, size_t x = 0,
           size_t y = INITIAL_Y);

  size_t get_x() const noexcept;
  size_t get_y() const noexcept;
  Nostd::List<Fragment>::iterator get_fragment() const noexcept;

  bool move_left();

  bool move_right();

  bool move_down();

  bool move_up();

  bool operator==(Position) const;

  bool operator!=(Position) const;
};

class InvalidPositionException : public std::exception {
private:
  std::string message;

public:
  InvalidPositionException(const int &x, const int &y) {
    this->message = "(" + std::to_string(x) + " " + std::to_string(y) +
                    ") isn't a valid position";
  }

  const char *what() const noexcept override { return message.c_str(); }
};

} // namespace World

#endif // WORLD_POSITION_HPP
