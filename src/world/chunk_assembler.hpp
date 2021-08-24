/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  04/22/2021

  chunk_assembler.hpp: World::ChunkAssembler definition. This class represent
  the core of the World module. It has been designed to take an instance of
  Data::Database in input and produce an output for Engine and Game
  modules. It has four steps to complete:
    1. Chose which chunk and scenery must be used.
    2. Combine them to describe how the map looks like.
    3. Chose how often enemies appear and describe where they are located.
    4. Chose how often items appear and describe where they are located.
  All these randomly and keeping track of the increasing game difficulty.
*/

#ifndef WORLD_CHUNK_ASSEMBLER_HPP
#define WORLD_CHUNK_ASSEMBLER_HPP

#include "../data/map_chunk.hpp"
#include "../data/pawns/enemy.hpp"
#include "../data/pawns/item.hpp"
#include "../data/scenery.hpp"
#include "../engine/tile.hpp"
#include "../nostd/matrix.hpp"
#include "../nostd/vector.hpp"
#include "fragment.hpp"
#include "position.hpp"
#include "random_generator.hpp"
#include "world_expansion.hpp"
#include <cstddef>

namespace World {

class ChunkAssembler {
private:
  // Map chunks from database
  const Nostd::Vector<Data::MapChunk> *const chunks;

  // Sceneries from database
  const Nostd::Vector<Data::Scenery> *const sceneries;

  // Enemies from database
  const Nostd::Vector<Data::Pawns::Enemy> *const enemies;

  // Items from database
  const Nostd::Vector<Data::Pawns::Item> *const items;

  // Random number generator. Used to get the randomness needed from the
  // assembler to produce a good map
  World::RandomGenerator random_gen;

  // Reference to the Data::Scenery the assembler is using at the moment
  const Data::Scenery *current_scenery;

  // Reference to the Data::MapChunk the assembler is using at the moment
  const Data::MapChunk *current_chunk;

  // Counter for the number of chunks assembled.
  // Used to keep track of when there is the need to change current_scenery and
  // to get (in combination with random_gen methods) the map difficulty
  // increasing
  size_t chunks_assembled;

  // Decide randomly which Data::MapChunk should be next to draw
  void next_chunk(void) noexcept;

  // Decide which Data::Scenery should be used to paint the map
  void next_scenery(void) noexcept;

  // Taken a Data::MapChunk and a Data::Scenery references in input it will
  // merge them togheter returning a Nostd::Matrix containing Engine::Tile*
  // representing the map.
  Nostd::Matrix<Engine::Tile *>
  assemble_scenery(const Data::MapChunk *,
                   const Data::Scenery *) const noexcept;

  // Taken a Data::MapChunk reference in input it will returns all the enemies
  // inside the chunk and their positions
  Nostd::Pair<Nostd::List<Data::Pawns::Enemy>,
              Nostd::Matrix<Data::Pawns::Enemy *>>
  assemble_enemies(const Data::MapChunk *) noexcept;

  // Taken a Data::MapChunk reference in input it will returns all the items
  // inside the chunk and their positions
  Nostd::Pair<Nostd::List<Data::Pawns::Item>,
              Nostd::Matrix<Data::Pawns::Item *>>
  assemble_items(const Data::MapChunk *) noexcept;

  // Given a Data::MapChunk, a Data::Scenery::Autotile* and the coordinates of a
  // chunk's cell it will return a char representing the cell graphically
  char elaborate_autotile(const Data::MapChunk *,
                          const Data::Scenery::Autotile *, const size_t &,
                          const size_t &) const noexcept;

  // Helper function to calcoulate Fibonacci's function from a positive integer.
  // Used to decide how to draw the gradient of the sky
  inline size_t fib(const size_t &) const noexcept;

  // Helper function for elaborate_autotile
  inline bool is_ground_or_platform(const Data::MapUnit &) const noexcept;

public:
  ChunkAssembler() = delete;

  ChunkAssembler(const Nostd::Vector<Data::MapChunk> *,
                 const Nostd::Vector<Data::Scenery> *,
                 const Nostd::Vector<Data::Pawns::Enemy> *,
                 const Nostd::Vector<Data::Pawns::Item> *);

  // Point of communication with World::World. It returns an instance of
  // World::WorldExpansion containing all the data World::World needs to expand
  WorldExpansion get(void) noexcept;

  // Getters
  const Data::MapChunk *get_current_chunk(void) const noexcept;
  const Data::Scenery *get_current_scenery(void) const noexcept;

  // Used to clear and destroy pointers inside a Nostd::Matrix
  void dispose(Nostd::Matrix<Engine::Tile *> &) noexcept;
};

} // namespace World

#endif
