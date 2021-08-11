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
using namespace Nostd;
using namespace Engine;

using AChunk = World::World::AssembledChunk;

// World::World constructor
World::World::World(const Database &d) noexcept
    : player{d.heroes()[0], nullptr}, assembler(d.map_chunks(), d.sceneries()) {
  add_chunk(DEFAULT_CHUNKS_REFILL);
  this->player.second = new Position(&environment, environment.begin());
}

// Add new assembled chunk to enviroment
void World::World::add_chunk(const int &) noexcept {
  for (size_t i{0}; i < this->DEFAULT_CHUNKS_REFILL; i++) {
    this->environment.push_back(this->assembler.get());
    this->assembler.next_chunk();
  }
}
