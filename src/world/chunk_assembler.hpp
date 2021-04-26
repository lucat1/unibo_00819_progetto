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

#include "../data/map.hpp"
#include "../nostd/vector.hpp"
#include "random_object.hpp"
#include <cstddef>

namespace World {

class ChunkAssembler {
private:
  // TODO
  struct ChunkData {
    const size_t id;
    const size_t begin;
    const size_t end;
    const Data::Map *map;
  };

  Nostd::Vector<ChunkData> *adjacency_list = nullptr;
  World::RandomObject random_obj;

  void fill_list() noexcept;
  ChunkData next() noexcept;

public:
  ChunkAssembler();

  void print_list() const noexcept;
};

} // namespace World

#endif
