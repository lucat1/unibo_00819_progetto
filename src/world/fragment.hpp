/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  08/11/2021

  fragment.hpp: user interface for World::Fragment. This struct represents the
  fragment of the map the user is capable to see on the screen, so it stores an
  assembled chunk and all the interactables (items, enemies and projectiles).
*/

#ifndef WORLD_FRAGMENT_HPP
#define WORLD_FRAGMENT_HPP

#include "../data/map_chunk.hpp"
#include "../data/pawns/enemy.hpp"
#include "../data/pawns/item.hpp"
#include "../data/pawns/projectile.hpp"
#include "../engine/tile.hpp"
#include "../nostd/matrix.hpp"

namespace World {

struct Fragment {
  Fragment(const Data::MapChunk *const, const Nostd::Matrix<Engine::Tile *> &,
           Nostd::Matrix<Data::Pawns::Enemy *> &,
           Nostd::Matrix<Data::Pawns::Item *> &);

  /* Only a pointer to the original MapChunk is stored: there is no need to copy
   * the whole thing.
   */
  const Data::MapChunk *const map_chunk;
  /* "To get runtime polymorphic behavior in C++, the member functions called
   * must be virtual and objects must be manipulated through pointers or
   * references." B. Stroustrup, The C++ Programming Language, 4th ed., Pearson
   * 2013, p. 587. */
  Nostd::Matrix<Engine::Tile *> tiles;
  /* Enemies and items are not stored here, but in a much more convenient data
   * structure: a list. The cells of these matrixes are just pointing to the
   * elemnts of the appropriate list. */
  Nostd::Matrix<Data::Pawns::Enemy *> enemies;
  Nostd::Matrix<Data::Pawns::Item *> items;
  Nostd::Matrix<Data::Pawns::Projectile *> projectiles;
};

} // namespace World

#include "../nostd/matrix.cpp"

#endif
