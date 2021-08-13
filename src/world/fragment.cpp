/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  08/12/2021

  fragment.cpp: implementation of World::Fragment.
*/

#include "fragment.hpp"

using Nostd::Matrix;

World::Fragment::Fragment(const Data::MapChunk *const mc,
                          const Matrix<Engine::Tile *> &t,
                          const Matrix<Data::Pawns::Enemy *> &e,
                          const Matrix<Data::Pawns::Item *> &i,
                          const Matrix<Data::Pawns::Projectile *> &p)
    : map_chunk{mc}, tiles{t}, enemies{e}, items{i}, projectiles{p} {}
