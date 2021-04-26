/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  04/23/2021

  random_object.hpp
*/
#include "./random_object.hpp"
#include <cstddef>

using namespace World;

inline size_t RandomObject::get_rand(const size_t &max) const noexcept {
  return rand() % max;
}
