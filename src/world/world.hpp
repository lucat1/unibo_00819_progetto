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
#include "../world/chunk_assembler.hpp"
#include "position.hpp"

namespace World {
class World {
public:
  using AssembledChunk = Nostd::Matrix<Engine::BlockTile *>;

  Nostd::List<AssembledChunk> environment;
  Data::Pawns::Hero player;
  Position *position;

  World(const Data::Database &d) noexcept;

  // Add new assembled chunk to enviroment
  void add_chunk() noexcept;

private:
  const size_t LOADED_CHUNKS = 50;
  ChunkAssembler assembler;
};

} // namespace World

#endif
