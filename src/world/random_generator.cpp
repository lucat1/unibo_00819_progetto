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

using World::RandomGenerator;

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
  const auto n = bound - distribution(random_engine) - 1;
  return n < 0 ? bound : n >= bound ? bound - 1 : n;
}

size_t RandomGenerator::get_poisson_random_reverse(size_t antimean,
                                                   size_t bound) {
  return get_poisson_random(bound - antimean, bound);
}

size_t RandomGenerator::calculate_mean(size_t x, size_t b) {
  if (x == 0)
    throw std::invalid_argument("Length must be non-null");
  if (b <= 1)
    throw std::invalid_argument("Bound must be greater than 1");
  return (1 - static_cast<long double>(b)) / (x * b - x - b + 2) + b;
}
