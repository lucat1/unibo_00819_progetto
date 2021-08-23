/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  08/01/2021

  position.cpp: World::Position definition. The aim of this class is to store
  and manage the position of an interactable (e.g. player, enemies, items ...).
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
  // Reference to World::World enviroment: used to be able to move between one
  // fragment and another
  const Nostd::List<Fragment> *environment;
  // List iterator to the current fragment
  Nostd::List<Fragment>::iterator fragment;
  // Coordinates
  size_t x;
  size_t y;
  // Default rendering y
  static const size_t INITIAL_Y = 19;

public:
  Position(const Nostd::List<Fragment> *environment,
           Nostd::List<Fragment>::iterator fragment, size_t x = 0,
           size_t y = INITIAL_Y);

  // Coordinates getters
  size_t get_x(void) const noexcept;
  size_t get_y(void) const noexcept;

  // Fragment iterator getter
  Nostd::List<Fragment>::iterator get_fragment() const noexcept;

  // Methods used to move the coordinates
  bool move_left(void);

  bool move_right(void);

  bool move_down(void);

  bool move_up(void);
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
