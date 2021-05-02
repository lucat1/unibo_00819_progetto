// 2 maggio
#ifndef WORLD_RANDOM_GENERATOR_HPP
#define WORLD_RANDOM_GENERATOR_HPP

#include <cstdlib>
#include <ctime>

namespace World {

class RandomGenerator {
private:
  time_t seed;

public:
  using uint = size_t;

  // Init random with seed from current time
  RandomGenerator();

  // Get random number between 0 and bound parameter
  uint next(uint bound);

  // Seed filed getter
  time_t get_seed();
};

} // namespace World

#endif
