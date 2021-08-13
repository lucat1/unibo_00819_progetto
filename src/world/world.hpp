/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  07/18/2021

  world.hpp: World::World definition.
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

namespace World {

class World {
public:
  static const size_t DEFAULT_CHUNKS_REFILL = 50;

  Nostd::List<Fragment> environment;
  Nostd::Pair<Data::Pawns::Hero, Position> player;
  Nostd::List<Nostd::Pair<Data::Pawns::Enemy, Position>> enemies;
  Nostd::List<Nostd::Pair<Data::Pawns::Item, Position>> items;
  Nostd::List<Nostd::Pair<Data::Pawns::Projectile, Position>> projectiles;

  World(const Data::Database &d) noexcept;
  World(const Data::Database &d, Data::Pawns::Hero h) noexcept;

  // Add new assembled chunks to enviroment
  void add_chunk(const int &) noexcept;

private:
  ChunkAssembler assembler;
};

} // namespace World

#endif
