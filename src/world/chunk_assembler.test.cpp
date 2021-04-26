/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  04/23/2021

  chunck_assembler.test.cpp: tests for World::ChunckAssembler.
*/
#include "../nostd/test.hpp"
#include "chunk_assembler.hpp"

using namespace World;
using namespace Nostd;

int main() {
  it("do something better no ask", [] {
    ChunkAssembler assembler;
    assembler.print_list();
  });
  return 0;
}
