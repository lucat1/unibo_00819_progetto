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
  bound, inclusive:
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

  /*
    Returns a pseudorandom integer in the [0, bound] range emulating a uniform
    distribution, where bound is assumed to be non-negative. The old C standard
    library is used.

    This method can be useful when you want to deal with equally probable
    outcomes.
  */
  size_t get_random(size_t bound) const noexcept;

  /*
    Returns a pseudorandom integer in the [0, bound] range emulating a limited
    Poisson distribution, where mean is assumed to be also in [0, bound] and
    bound must be non-negative.

    This method can be useful when you want outcomes to become progressively
    more probable as you get closer to mean.
  */
  size_t get_poisson_random(size_t mean, size_t bound);

  /*
    Same as get_poisson_random, except for the actual mean, which is ultimately
    computed as "bound - antimean".
  */
  size_t get_poisson_random_reverse(size_t antimean, size_t bound);

  /*
     Applies a mathematical function designed to represent the expected
     difficulty of the game at a certain moment in time. The index of the
     current game phase is represented by len, which is assumed to be non-null;
     the maximum difficulty is represented by bound, which is assumed to be
     greater than 1. An omographic function is used: the difficulty level starts
     at 0 and then increases while asymptotically approaching bound from below.
  */
  static size_t calculate_mean(size_t len, size_t bound);

  // Seed getter
  time_t get_seed() const noexcept;
};

} // namespace World

#endif
