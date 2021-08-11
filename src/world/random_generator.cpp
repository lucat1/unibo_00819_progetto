// 2 maggio
#include "random_generator.hpp"

using namespace World;

RandomGenerator::RandomGenerator() : seed(time(nullptr)) { srand(this->seed); }

const RandomGenerator::uint
RandomGenerator::get_random(const uint &bound) const noexcept {
  return rand() % bound;
}

time_t RandomGenerator::get_seed() const noexcept { return this->seed; }
