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
#include "../nostd/matrix.hpp"
#include "../nostd/vector.hpp"
#include "map_pixel.hpp"
#include "random_generator.hpp"
#include <cstddef>

namespace World {

class ChunkAssembler {
private:
  struct ChunkInfo {
    size_t id;
    Data::MapChunk *chunk;
  };

  Nostd::Vector<Data::MapChunk> chunks;
  Nostd::Vector<Data::Scenery> sceneries;
  Nostd::Vector<ChunkInfo> *adjacency_list = nullptr;
  World::RandomGenerator random_gen;
  Data::Scenery current_scenery;
  ChunkInfo *current = nullptr;

  // Create the adjacency list. Called from the constractor.
  void fill_list() noexcept;

  // Returns the next Data::MapChunk to draw
  Data::MapChunk *next_chunk() noexcept;

  Nostd::Matrix<MapPixel> assemble_scenery(const Data::MapChunk *,
                                           const Data::Scenery) const noexcept;

public:
  ChunkAssembler() = delete;

  ChunkAssembler(Nostd::Vector<Data::MapChunk>, Nostd::Vector<Data::Scenery>);

  Nostd::Matrix<MapPixel> get() noexcept;

  void print_list() const noexcept;
  void print_scenery(Data::Scenery) noexcept;
};

} // namespace World

#endif
