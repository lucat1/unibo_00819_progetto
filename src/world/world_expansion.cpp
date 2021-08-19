/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  08/16/2021

  world_expansion.cpp: World::WorldExpansion implementation.

*/

#include "world_expansion.hpp"

using namespace World;
using namespace Nostd;
using namespace Data;
using namespace Engine;
using namespace Data::Pawns;

WorldExpansion::WorldExpansion(const MapChunk *const map_chunk,
                               const Matrix<Tile *> &tiles,
                               const Matrix<Enemy *> &enemies_matrix,
                               const List<Enemy> &enemies_list,
                               const Matrix<Item *> &items_matrix,
                               const List<Item> &items_list)

    : map_chunk(map_chunk), tiles(tiles), enemies_matrix(enemies_matrix),
      enemies_list(enemies_list), items_matrix(items_matrix),
      items_list(items_list) {}
