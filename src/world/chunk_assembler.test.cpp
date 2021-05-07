/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  04/23/2021

  chunck_assembler.test.cpp: tests for World::ChunckAssembler.
*/
#include "../data/database.hpp"
#include "../nostd/test.hpp"
#include "chunk_assembler.hpp"
#include <cassert>

using namespace World;
using namespace Nostd;
using namespace Data;

int main() {
  it("does something better no ask", [] {
    Database d("tests/alma.conf.csv", "tests/assets/", "tests/scoreboard.csv");
    assert(d.map_chunks().size() == 2);
    ChunkAssembler assembler(d.map_chunks());
    assembler.print_list();
  });
  return 0;
}
