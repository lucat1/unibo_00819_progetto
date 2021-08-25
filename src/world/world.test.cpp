/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  04/23/2021

  world.test.cpp: tests for the entire World module.
*/

#include "world.hpp"
#include "../data/database.hpp"
#include "../nostd/test.hpp"
#include "chunk_assembler.hpp"
#include "fragment.hpp"
#include "random_generator.hpp"
#include <cassert>

using Data::Database;
using Nostd::it;
using World::ChunkAssembler;
using World::RandomGenerator;

int main() {
  it("tests World::ChunkAssebler's functionality", [] {
    Database d("tests/overengineered.conf.csv", "tests/assets/",
               "tests/scoreboard.csv");
    assert(d.map_chunks().size() == 11);
    ChunkAssembler assembler(&d.map_chunks(), &d.sceneries(), &d.enemies(),
                             &d.items());
    auto m = assembler.get();
  });
  it("tests the creation of a new World::World", [] {
    Database d("tests/overengineered.conf.csv", "tests/assets/",
               "tests/scoreboard.csv");
    World::World w(d);
  });
  it("tests World::RandomGenerator functionalities", [] {
    RandomGenerator random_gen = RandomGenerator();
    size_t x = random_gen.get_random(3);
    assert(x < 3 && 0 <= x);
  });
  return 0;
}
