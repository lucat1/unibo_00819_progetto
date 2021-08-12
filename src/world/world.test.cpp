/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  04/23/2021

  world.test.cpp: tests for World::Wold.
*/
#include "world.hpp"
#include "../data/database.hpp"
#include "../nostd/test.hpp"
#include "chunk_assembler.hpp"
#include "fragment.hpp"
#include <cassert>

using Data::Database;
using Nostd::it;
using World::ChunkAssembler;
using World::Fragment;

int main() {
  it("tests World::ChunkAssebler's functionality", [] {
    Database d("tests/overengineered.conf.csv", "tests/assets/",
               "tests/scoreboard.csv");
    assert(d.map_chunks().size() == 11);
    ChunkAssembler assembler(d.map_chunks(), d.sceneries());
    Fragment m = assembler.get();
    // TODO
  });
  it("does something better no ask", [] {
    Database d("tests/overengineered.conf.csv", "tests/assets/",
               "tests/scoreboard.csv");
    World::World w(d);
  });
  return 0;
}
