/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  04/23/2021

  random_object.hpp
*/
#ifndef RANDOM_OBJECT_HPP
#define RANDOM_OBJECT_HPP

#include <cstddef>
#include <cstdlib>

namespace World {
class RandomObject {
public:
  inline size_t get_rand(const size_t &) const noexcept;
};
} // namespace World

#endif
