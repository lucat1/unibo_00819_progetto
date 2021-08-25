/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  05/02/2021

  Stefano Volpe #969766
  08/19/21

  random_generator.hpp: This class main goal is to generate random numbers in a
  smart way for World:ChunkAssembler.
  It exposes three possibility for getting a random number between 0 and a
  bound:
    1. C style random: generate using rand() function from C programming
       language.
    2. Poisson random: generate using Poisson's distribution to manage the
       probability using C++ standard library.
    3. Poisson random reverse: same as previous but reversing the distribution
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
  // C style random seed
  const time_t seed;
  // C++ random engine instance (used only for methods which use Poisson's
  // distrubution)
  std::default_random_engine random_engine;

public:
  // Init random with seed from current time
  RandomGenerator();

  // Get random number between 0 and bound parameter
  size_t get_random(size_t bound) const noexcept;

  // Designed for enemies and chunks  TODO
  size_t get_poisson_random(size_t mean, size_t bound);

  // Designed for items TODO
  size_t get_poisson_random_reverse(size_t mean, size_t bound);

  // TODO
  static size_t calculate_mean(size_t len, size_t bound);

  // Seed getter
  time_t get_seed() const noexcept;
};

} // namespace World

#endif
