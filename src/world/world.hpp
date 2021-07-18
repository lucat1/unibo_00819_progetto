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
#include "../nostd/list.hpp"
#include "../world/chunk_assembler.hpp"

namespace World {
class World {
public:
  Nostd::List<Nostd::Matrix<Engine::BlockTile *>> enviroment;
  World(const Data::Database &d) noexcept;

private:
  ChunkAssembler assembler;
};

} // namespace World

#endif
