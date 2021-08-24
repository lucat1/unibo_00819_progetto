/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  08/16/2021

  world_expansion.cpp: World::WorldExpansion implementation. This struct has
  only a constructor.

*/

#include "world_expansion.hpp"

using Data::MapChunk;
using Data::Pawns::Enemy;
using Data::Pawns::Item;
using Engine::Tile;
using Nostd::List;
using Nostd::Matrix;
using World::WorldExpansion;

WorldExpansion::WorldExpansion(const MapChunk *const map_chunk,
                               const Matrix<Tile *> &chunk_assembled,
                               const Matrix<Enemy *> &enemies_matrix,
                               const List<Enemy> &enemies_list,
                               const Matrix<Item *> &items_matrix,
                               const List<Item> &items_list)

    : map_chunk(map_chunk), chunk_assembled(chunk_assembled),
      enemies_matrix(enemies_matrix), enemies_list(enemies_list),
      items_matrix(items_matrix), items_list(items_list) {}
