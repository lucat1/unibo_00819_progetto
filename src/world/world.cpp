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
#include "world_expansion.hpp"

using namespace Data;
using namespace Nostd;
using namespace Engine;

// World::World constructor
World::World::World(const Database &d, Data::Pawns::Hero h) noexcept
    : player{h, {&environment, environment.begin()}},
      assembler(&d.map_chunks(), &d.sceneries(), &d.enemies(), &d.items()) {
  add_chunk(DEFAULT_CHUNKS_REFILL);
  player.second = Position(&environment, environment.begin());
}

World::World::World(const Database &d) noexcept : World(d, d.heroes()[0]) {}

// Add new assembled chunk to enviroment
void World::World::add_chunk(const int &) noexcept {
  for (size_t i{0}; i < this->DEFAULT_CHUNKS_REFILL; i++) {
    WorldExpansion expansion = assembler.get();
    *this += expansion;
    this->assembler.next_chunk();
  }
}

World::World &World::World::operator+=(WorldExpansion &exp) noexcept {
  Fragment fragment(exp.map_chunk, exp.tiles, exp.enemies_matrix,
                    exp.items_matrix);
  environment.push_back(fragment);

  for (size_t y{0}; y < exp.enemies_matrix.extent(0); y++)
    for (size_t x{0}; x < exp.enemies_matrix.extent(1); x++)
      if (exp.enemies_matrix.at(y).at(x).value() != nullptr)
        enemies.push_back({*(exp.enemies_matrix.at(y).at(x).value()),
                           Position(&environment, --environment.end(), x, y)});

  for (size_t y{0}; y < exp.items_matrix.extent(0); y++)
    for (size_t x{0}; x < exp.items_matrix.extent(1); x++)
      if (exp.items_matrix.at(y).at(x).value() != nullptr)
        items.push_back({*(exp.items_matrix.at(y).at(x).value()),
                         Position(&environment, --environment.end(), x, y)});
  return *this;
}
