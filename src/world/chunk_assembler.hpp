/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  04/22/2021

  chunk_assembler.hpp: World::ChunkAssembler definition.
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
  const static size_t MAX_CHUNKS_HEIGHT_DIFFERECE = 5;

  const Nostd::Vector<Data::MapChunk> *const chunks;
  const Nostd::Vector<Data::Scenery> *const sceneries;
  const Nostd::Vector<Data::Pawns::Enemy> *const enemies;
  const Nostd::Vector<Data::Pawns::Item> *const items;
  const Data::Scenery *current_scenery;
  const Data::MapChunk *current_chunk;
  RandomGenerator random_gen;
  size_t chunks_assembled;

  Nostd::Matrix<Engine::Tile *>
  assemble_scenery(const Data::MapChunk *,
                   const Data::Scenery *) const noexcept;

  Nostd::Pair<Nostd::List<Data::Pawns::Enemy>,
              Nostd::Matrix<Data::Pawns::Enemy *>>
  assemble_enemies(const Data::MapChunk *) noexcept;

  Nostd::Pair<Nostd::List<Data::Pawns::Item>,
              Nostd::Matrix<Data::Pawns::Item *>>
  assemble_items(const Data::MapChunk *) noexcept;

  char elaborate_autotile(const Data::MapChunk *,
                          const Data::Scenery::Autotile *, const size_t &,
                          const size_t &) const noexcept;

  inline size_t fib(const size_t &) const noexcept;
  inline bool is_ground_or_platform(const Data::MapUnit &) const noexcept;

public:
  ChunkAssembler() = delete;

  ChunkAssembler(const Nostd::Vector<Data::MapChunk> *,
                 const Nostd::Vector<Data::Scenery> *,
                 const Nostd::Vector<Data::Pawns::Enemy> *,
                 const Nostd::Vector<Data::Pawns::Item> *);

  constexpr static size_t sceneries_duration = 25;

  WorldExpansion get(void) noexcept;

  // Returns the next Data::MapChunk to draw
  void next_chunk(void) noexcept;

  void next_scenery(void) noexcept;

  const Data::MapChunk *get_current_chunk(void) const noexcept;
  const Data::Scenery *get_current_scenery(void) const noexcept;

  void dispose(Nostd::Matrix<Engine::Tile *> &) noexcept;
};

} // namespace World

#endif
