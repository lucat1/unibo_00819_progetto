// 2 maggio
#include "random_generator.hpp"

using namespace World;

RandomGenerator::RandomGenerator() {
  seed = time(nullptr);
  srand(this->seed);
}

RandomGenerator::uint RandomGenerator::get_random(uint bound) {
  return rand() % bound;
}

time_t RandomGenerator::get_seed() { return this->seed; }
