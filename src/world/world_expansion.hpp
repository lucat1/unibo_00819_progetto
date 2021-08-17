/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  08/16/2021

  world_extension.hpp: World::WorldExpansion definition.
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
  const Data::MapChunk *const map_chunk;
  const Nostd::Matrix<Engine::Tile *> tiles;
  Nostd::Matrix<Data::Pawns::Enemy *> enemies_matrix;
  Nostd::List<Data::Pawns::Enemy> enemies_list;
  Nostd::Matrix<Data::Pawns::Item *> items_matrix;
  Nostd::List<Data::Pawns::Item> items_list;

  WorldExpansion(const Data::MapChunk *const map_chunk,
                 const Nostd::Matrix<Engine::Tile *> &tiles,
                 const Nostd::Matrix<Data::Pawns::Enemy *> &enemies_matrix,
                 const Nostd::List<Data::Pawns::Enemy> &enemies_list,
                 const Nostd::Matrix<Data::Pawns::Item *> &items_matrix,
                 const Nostd::List<Data::Pawns::Item> &items_list);
};
} // namespace World
#endif
