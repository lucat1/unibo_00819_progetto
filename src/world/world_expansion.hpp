/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  08/16/2021

  world_extension.hpp: World::WorldExpansion definition. This struct is used in
  order to hold the informations created by World::ChunksAssembler that
  World::World needs to expand.
*/

#ifndef WORLD_WORLDEXPANSION_HPP
#define WORLD_WORLDEXPANSION_HPP

#include "../data/pawns/enemy.hpp"
#include "../data/pawns/item.hpp"
#include "../nostd/list.hpp"
#include "../nostd/pair.hpp"
#include "fragment.hpp"
#include "position.hpp"

namespace World {
struct WorldExpansion {
  // Last Data::MapChunk assembled
  const Data::MapChunk *const map_chunk;
  // Last effective chunk assembled in form of a Matrix of Engine::Tile*
  const Nostd::Matrix<Engine::Tile *> chunk_assembled;
  // Enemies references stored in a matrix whose coordinates represent their
  // positions
  Nostd::Matrix<Data::Pawns::Enemy *> enemies_matrix;
  // Effective enemies list
  Nostd::List<Data::Pawns::Enemy> enemies_list;
  // Items references stored in a matrix whose coordinates represent their
  // positions
  Nostd::Matrix<Data::Pawns::Item *> items_matrix;
  // Effective items list
  Nostd::List<Data::Pawns::Item> items_list;

  WorldExpansion(const Data::MapChunk *const,
                 const Nostd::Matrix<Engine::Tile *> &,
                 const Nostd::Matrix<Data::Pawns::Enemy *> &,
                 const Nostd::List<Data::Pawns::Enemy> &,
                 const Nostd::Matrix<Data::Pawns::Item *> &,
                 const Nostd::List<Data::Pawns::Item> &);
};
} // namespace World
#endif
