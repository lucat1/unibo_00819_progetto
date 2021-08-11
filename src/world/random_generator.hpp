// 2 maggio
#ifndef WORLD_RANDOM_GENERATOR_HPP
#define WORLD_RANDOM_GENERATOR_HPP

#include <cstdlib>
#include <ctime>

namespace World {

class RandomGenerator {
private:
  const time_t seed;

public:
  using uint = size_t;

  // Init random with seed from current time
  RandomGenerator();

  // Get random number between 0 and bound parameter
  const uint get_random(const uint &bound) const noexcept;

  // Seed filed getter
  time_t get_seed() const noexcept;
};

} // namespace World

#endif
