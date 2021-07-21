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

World::World::World(const Database &d) noexcept
    : player{d.heroes()[0]}, assembler(d.map_chunks(), d.sceneries()) {

  for (size_t i{0}; i < this->LOADED_CHUNKS; i++) {
    this->environment.push_back(this->assembler.get());
    this->assembler.next_chunk();
  }
  this->position = new Position(this->environment);
}
