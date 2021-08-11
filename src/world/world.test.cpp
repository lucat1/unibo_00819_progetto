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
#include <cassert>

using namespace Nostd;
using namespace Data;
using namespace Engine;

using WWorld = World::World;
using WChunkAssembler = World::ChunkAssembler;

int main() {
  it("tests World::ChunkAssebler's functionality", [] {
    Database d("tests/overengineered.conf.csv", "tests/assets/",
               "tests/scoreboard.csv");
    assert(d.map_chunks().size() == 11);
    WChunkAssembler assembler(d.map_chunks(), d.sceneries());
    Matrix<Tile *> m = assembler.get();
    // TODO
  });
  it("does something better no ask", [] {
    Database d("tests/overengineered.conf.csv", "tests/assets/",
               "tests/scoreboard.csv");
    WWorld w(d);
  });
  return 0;
}
