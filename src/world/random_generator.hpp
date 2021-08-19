/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  05/02/2021

  random_generator.hpp: World::RandomGenerator definition.
*/

#ifndef WORLD_RANDOM_GENERATOR_HPP
#define WORLD_RANDOM_GENERATOR_HPP

#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <random>

namespace World {

class RandomGenerator {
private:
  const time_t seed;
  std::default_random_engine random_engine;

public:
  // Init random with seed from current time
  RandomGenerator();

  // Get random number between 0 and bound parameter
  const size_t get_random(size_t bound) const noexcept;

  // Designed for items
  const size_t get_poisson_random(size_t mean, size_t bound);

  // Designed for enemies
  const size_t get_poisson_random_reverse(size_t mean, size_t bound);

  // Seed filed getter
  time_t get_seed() const noexcept;
};

} // namespace World

#endif
