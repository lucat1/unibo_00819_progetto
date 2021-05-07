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
#include "../nostd/vector.hpp"
#include "random_generator.hpp"
#include <cstddef>

namespace World {

class ChunkAssembler {
private:
  struct ChunkData {
    const size_t id;
    const size_t begin;
    const size_t end;
    const Data::MapChunk *map;
  };

  Nostd::Vector<Data::MapChunk> chunks;
  Nostd::Vector<ChunkData> *adjacency_list = nullptr;
  World::RandomGenerator random_gen;
  Data::MapChunk *current = nullptr;

  // Create the adjacency list. Called from the constractor.
  void fill_list() noexcept;
  // Returns the next Data::MapChunk to draw
  ChunkData next() noexcept;

public:
  ChunkAssembler();

  ChunkAssembler(Nostd::Vector<Data::MapChunk>);

  void print_list() const noexcept;
};

} // namespace World

#endif
