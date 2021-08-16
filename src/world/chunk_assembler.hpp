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
#include "../engine/block_tile.hpp"
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
  const World::RandomGenerator random_gen;
  const Data::Scenery *current_scenery;
  const Data::MapChunk *current_chunk;
  size_t chunks_assembled;

  Nostd::Matrix<Engine::Tile *>
  assemble_scenery(const Data::MapChunk *,
                   const Data::Scenery *) const noexcept;

  Nostd::Pair<Nostd::List<Data::Pawns::Enemy>,
              Nostd::Matrix<Data::Pawns::Enemy *>>
  assemble_enemies(const Data::MapChunk *) const noexcept;

  Nostd::Pair<Nostd::List<Data::Pawns::Item>,
              Nostd::Matrix<Data::Pawns::Item *>>
  assemble_items(const Data::MapChunk *) const noexcept;

  char elaborate_autotile(const Data::MapChunk *chunk,
                          const Data::Scenery::Autotile *tile, const int &x,
                          const int &y) const noexcept;

  void shift_chunk(Data::MapChunk *chunk, const int &shifting_factor) noexcept;

  inline size_t fib(const size_t &) const noexcept;
  inline bool is_ground_or_platform(const Data::MapUnit &) const noexcept;

public:
  ChunkAssembler() = delete;

  ChunkAssembler(const Nostd::Vector<Data::MapChunk> *,
                 const Nostd::Vector<Data::Scenery> *,
                 const Nostd::Vector<Data::Pawns::Enemy> *,
                 const Nostd::Vector<Data::Pawns::Item> *);

  WorldExpansion get() noexcept;

  // Returns the next Data::MapChunk to draw
  void next_chunk() noexcept;

  void next_scenery() noexcept;

  const Data::Scenery *get_current_scenery() const noexcept;
};

} // namespace World

#endif
