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
#include <cstddef>

using namespace Data;
using namespace Nostd;
using namespace Engine;

using AChunk = World::World::AssembledChunk;

// World::World constructor
World::World::World(const Database &d) noexcept
    : assembler(d.map_chunks(), d.sceneries()) {

  for (size_t i{0}; i < this->LOADED_CHUNKS; i++)
    add_chunk();
}
