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
#include "../data/pawns/hero.hpp"
#include "../nostd/list.hpp"
#include "../nostd/pair.hpp"
#include "../world/chunk_assembler.hpp"
#include "position.hpp"

namespace World {
class World {
public:
  static const size_t DEFAULT_CHUNKS_REFILL = 50;
  using AssembledChunk = Nostd::Matrix<Engine::Tile *>;

  Nostd::List<AssembledChunk> environment;
  Nostd::Pair<Data::Pawns::Hero, Position *> player;

  World(const Data::Database &d) noexcept;

  // Add new assembled chunk to enviroment
  void add_chunk(const int &) noexcept;

private:
  ChunkAssembler assembler;
};

} // namespace World

#endif
