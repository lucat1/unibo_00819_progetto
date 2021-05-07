/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  04/22/2021

  chunk_assembler.cpp: TODO.
*/

#include "chunk_assembler.hpp"
#include <cstddef>
#include <cstdlib>
#include <iostream>

using namespace World;
using namespace Nostd;
using namespace Data;

ChunkAssembler::ChunkAssembler(Vector<MapChunk> chunks) {
  this->chunks = chunks;
  adjacency_list = new Vector<ChunkInfo>[chunks.size()];
  fill_list();
}

// Create the adjacency_list from Chunks using starting_row and ending_row to
// link nodes
void ChunkAssembler::fill_list() noexcept {
  if (adjacency_list == nullptr)
    return;

  Vector<ChunkInfo> infos(chunks.size());
  std::cout << "Chunks: " << std::endl;
  for (size_t i = 0; i < chunks.size(); i++) {
    ChunkInfo x = {i, &chunks[i]};
    infos.at(i) = x;
    std::cout << "{ " << chunks[i].starting_row() << " - "
              << chunks[i].ending_row() << " }" << std::endl;
  }

  for (ChunkInfo first : infos) {
    for (ChunkInfo second : infos) {
      if (first.id == second.id)
        continue;
      if (first.chunk->ending_row() == second.chunk->starting_row()) {
        adjacency_list[first.id].push_back(second);
      }
    }
  }
}

// Debug only
void ChunkAssembler::print_list() const noexcept {
  for (size_t i = 0; i < chunks.size(); i++) {
    std::cout << i << "-";
    for (ChunkInfo c : adjacency_list[i]) {
      std::cout << "(" << c.id << ", " << c.chunk->starting_row() << ", "
                << c.chunk->ending_row() << " ) ";
    }
    std::cout << std::endl;
  }
}

// Generate a random number i between 0 and the number of nodes liked to Current
// and take the i-esim linked node.
MapChunk *ChunkAssembler::next() noexcept {
  if (current == nullptr) {
    current = new ChunkInfo;
    current->id = 0;
    current->chunk = &chunks[0];
  } else {
    auto rand = random_gen.get_random(adjacency_list[current->id].size());
    current = &adjacency_list[current->id][rand];
  }
  return current->chunk;
}
