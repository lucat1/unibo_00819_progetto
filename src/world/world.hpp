/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  07/18/2021

  world.hpp: World::World definition. This class represent the World module
  interface with the rest of the modules. It manages the creation of new parts
  of the map (via a World::ChunkAssembler instance) and provides players,
  enemies, items and projectiles positions.
*/

#ifndef WORLD_WORLD_HPP
#define WORLD_WORLD_HPP

#include "../data/database.hpp"
#include "../data/pawns/enemy.hpp"
#include "../data/pawns/hero.hpp"
#include "../data/pawns/item.hpp"
#include "../data/pawns/projectile.hpp"
#include "../nostd/list.hpp"
#include "../nostd/pair.hpp"
#include "chunk_assembler.hpp"
#include "fragment.hpp"
#include "position.hpp"
#include "world_expansion.hpp"
#include <stdexcept>

namespace World {

class World {
public:
  // Default number of new chunks loaded on request
  constexpr static size_t default_chunks_refill{50};
  Nostd::List<Fragment> environment;
  // Player and his position
  Nostd::Pair<Data::Pawns::Hero, Position> player;
  // Enemies and their positions
  Nostd::List<Nostd::Pair<Data::Pawns::Enemy, Position>> enemies;
  // Items and their positions
  Nostd::List<Nostd::Pair<Data::Pawns::Item, Position>> items;
  // Projectiles and their positions
  Nostd::List<Nostd::Pair<Data::Pawns::Projectile, Position>> projectiles;

  World(const Data::Database &) noexcept;
  World(const Data::Database &, Data::Pawns::Hero) noexcept;

  // Add new assembled chunks to enviroment
  void add_chunk(const size_t &n = default_chunks_refill) noexcept;

  // Expand World::World data with and instance of World::WorldExpansion
  World &operator+=(WorldExpansion &) noexcept;

private:
  ChunkAssembler assembler;
};

} // namespace World

#endif
