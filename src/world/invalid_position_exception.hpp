/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  08/01/2021

  invalid_position.hpp: InvalidPositionException class definition. This
  exception is made to be thrown when a World::Position reahes invalid
  coordinate.
*/
#ifndef WORLD_INVALID_POSITION_HPP
#define WORLD_INVALID_POSITION_HPP

#include "../engine/utils.hpp"
#include "../nostd/string.hpp"
#include <exception>

namespace World {

class InvalidPositionException : public std::exception {
private:
  Nostd::String message;

public:
  InvalidPositionException(const int &x, const int &y) {
    message = "(";
    Engine::Utils::stringify(x, message);
    message.append(",");
    Engine::Utils::stringify(y, message);
    message.append(") is not a valid position.");
  }

  const char *what() const noexcept override { return message.c_str(); }
};

} // namespace World

#endif
