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
#include <iostream>

using namespace Nostd;
using namespace Data;
using namespace Engine;

using WWorld = World::World;
using WChunkAssembler = World::ChunkAssembler;

int main() {
  it("tests World::ChunkAssebler's functionality", [] {
    Database d("tests/alma.conf.csv", "tests/assets/", "tests/scoreboard.csv");
    assert(d.map_chunks().size() == 2);
    WChunkAssembler assembler(d.map_chunks(), d.sceneries());
    Matrix<BlockTile *> m = assembler.get();
    // TODO
  });
  it("does something better no ask", [] {
    Database d("tests/alma.conf.csv", "tests/assets/", "tests/scoreboard.csv");
    WWorld w(d);
    for (auto x : w.enviroment) {
      for (auto r : x) {
        for (auto c : r) {
          std::wcout << c.value()->character();
        }
        std::wcout << std::endl;
      }
      std::wcout << std::endl << std::endl;
    }
  });
  return 0;
}
