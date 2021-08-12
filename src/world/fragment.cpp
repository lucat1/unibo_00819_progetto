/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  08/12/2021

  fragment.cpp: implementation of World::Fragment.
*/

#include "fragment.hpp"

World::Fragment::Fragment(const Nostd::Matrix<Data::MapUnit> *const mu,
                          const Nostd::Matrix<Engine::Tile *> &t,
                          const Nostd::Matrix<Data::Pawns::Enemy *> &e,
                          const Nostd::Matrix<Data::Pawns::Item *> &i)
    : map_units{mu}, tiles{t}, enemies{e}, items{i} {}
