/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  07/18/2021

  world.cpp: Implementation for World::World.
*/

#include "world.hpp"
#include "chunk_assembler.hpp"

using namespace Data;

World::World::World(const Database &d) noexcept
    : assembler(d.map_chunks(), d.sceneries()) {
  enviroment.push_back(assembler.get());
  assembler.next_chunk();
  enviroment.push_back(assembler.get());
}
