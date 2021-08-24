/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  07/18/2021

  world.cpp: implementation for World::World.
*/

#include "world.hpp"
#include "world_expansion.hpp"

constexpr size_t World::World::default_chunks_refill;

// World::World constructor
World::World::World(const Data::Database &d, Data::Pawns::Hero h) noexcept
    : player{h, {&environment, environment.begin()}},
      assembler(&d.map_chunks(), &d.sceneries(), &d.enemies(), &d.items()) {
  add_chunk();
  player.second = Position(&environment, environment.begin());
}

// World::World constructor
World::World::World(const Data::Database &d) noexcept
    : World(d, d.heroes()[0]) {}

// Add new assembled chunk to enviroment. For each new chunk an instance of
// World::WorldExpansion is added to this World::World
void World::World::add_chunk(const size_t &n) noexcept {
  for (size_t i{0}; i < n; i++) {
    WorldExpansion expansion = assembler.get();
    *this += expansion;
    this->assembler.next_chunk();
  }
}

// This operator describes how a World::WorldExpansion is added to a
// World::World. Basically for each enemy inside
// World::WorldExpansion.enemies_matrix it adds a new instance of
// Nostd::Pair<Data::Pawns::Enemy*, World::Position> to the World::World.enemies
// Vector. Same thing is done with items. It also add a new World::Fragment to
// World::World.enviroment.
World::World &World::World::operator+=(WorldExpansion &exp) noexcept {
  Fragment fragment(exp.map_chunk, exp.chunk_assembled, exp.enemies_matrix,
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
