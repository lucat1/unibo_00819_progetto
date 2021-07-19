/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  04/22/2021

  chunk_assembler.hpp: description TODO.
*/

#ifndef WORLD_CHUNK_ASSEMBLER_HPP
#define WORLD_CHUNK_ASSEMBLER_HPP

#include "../data/map_chunk.hpp"
#include "../data/scenery.hpp"
#include "../engine/block_tile.hpp"
#include "../nostd/matrix.hpp"
#include "../nostd/vector.hpp"
#include "random_generator.hpp"
#include <cstddef>

namespace World {

class ChunkAssembler {
private:
  const Nostd::Vector<Data::MapChunk> *chunks;
  const Nostd::Vector<Data::Scenery> *sceneries;
  const World::RandomGenerator random_gen;
  Data::Scenery current_scenery;
  const Data::MapChunk *current_chunk;

  Nostd::Matrix<Engine::BlockTile *>
  assemble_scenery(const Data::MapChunk *, const Data::Scenery) const noexcept;

public:
  ChunkAssembler() = delete;

  ChunkAssembler(const Nostd::Vector<Data::MapChunk> &,
                 const Nostd::Vector<Data::Scenery> &);

  Nostd::Matrix<Engine::BlockTile *> get() const noexcept;

  // Returns the next Data::MapChunk to draw
  void next_chunk() noexcept;
};

} // namespace World

#endif
