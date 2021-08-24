/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  05/02/2021

  Stefano Volpe #969766
  08/19/21

  random_generator.cpp: implementation for World::RandomGenerator.
*/

#include "random_generator.hpp"
#include <cstddef>
#include <random>
#include <stdexcept>

using namespace World;

RandomGenerator::RandomGenerator() : seed(time(nullptr)), random_engine(seed) {
  srand(seed);
}

size_t RandomGenerator::get_random(size_t bound) const noexcept {
  return rand() % bound;
}

time_t RandomGenerator::get_seed() const noexcept { return seed; }

size_t RandomGenerator::get_poisson_random(size_t mean, size_t bound) {
  if (!mean || mean > bound)
    throw std::invalid_argument(
        "Invalid mean: mean can't be 0 or greater than bound");
  std::poisson_distribution<size_t> distribution(mean);
  const int n = bound - distribution(random_engine) - 1;
  return n < 0 ? bound : n;
}

size_t RandomGenerator::get_poisson_random_reverse(size_t mean, size_t bound) {
  return get_poisson_random(bound - mean, bound);
}

size_t RandomGenerator::calculate_mean(size_t x, size_t b) {
  if (b <= 1)
    throw std::invalid_argument("Bound must be greater than 1");
  return (1 - static_cast<long double>(b)) / (x * b - x + 1) + b;
}
