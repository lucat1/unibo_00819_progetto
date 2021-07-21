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
  Data::Pawns::Hero player;
  Position *position;
  Nostd::List<Nostd::Matrix<Engine::BlockTile *>> environment;
  World(const Data::Database &d) noexcept;

  // Add new assembled chunk to enviroment
  void add_chunk() noexcept;

private:
  const unsigned int LOADED_CHUNKS = 50;
  ChunkAssembler assembler;
};

} // namespace World

#endif
