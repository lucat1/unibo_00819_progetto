/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  07/18/2021

  world.cpp: implementation for World::World.
*/

#include "world.hpp"
#include "../data/pawns/hero.hpp"
#include "chunk_assembler.hpp"

using namespace Data;
using namespace Nostd;
using namespace Engine;

// World::World constructor
World::World::World(const Database &d, Data::Pawns::Hero h) noexcept
    : player{h, {&environment, environment.begin()}},
      assembler(d.map_chunks(), d.sceneries()) {
  add_chunk(DEFAULT_CHUNKS_REFILL);
  player.second = Position(&environment, environment.begin());
}

World::World::World(const Database &d) noexcept : World(d, d.heroes()[0]) {}

// Add new assembled chunk to enviroment
void World::World::add_chunk(const int &) noexcept {
  for (size_t i{0}; i < this->DEFAULT_CHUNKS_REFILL; i++) {
    this->environment.push_back(this->assembler.get());
    this->assembler.next_chunk();
  }
}
