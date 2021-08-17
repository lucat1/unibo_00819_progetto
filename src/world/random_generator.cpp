/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  05/02/2021

  random_generator.cpp: implementation for World::RandomGenerator.
*/

#include "random_generator.hpp"

using namespace World;

RandomGenerator::RandomGenerator() : seed(time(nullptr)) { srand(this->seed); }

const size_t RandomGenerator::get_random(const size_t &bound) const noexcept {
  return rand() % bound;
}

time_t RandomGenerator::get_seed() const noexcept { return this->seed; }
