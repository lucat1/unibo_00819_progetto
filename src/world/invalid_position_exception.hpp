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

#include <exception>
#include <string>

namespace World {

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

#endif
