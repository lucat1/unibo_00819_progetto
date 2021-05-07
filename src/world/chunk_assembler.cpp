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

ChunkAssembler::ChunkAssembler(Nostd::Vector<Data::MapChunk> chunks) {
  this->chunks = chunks;
  adjacency_list = new Vector<ChunkData>[4];
  fill_list();
}

// TODO That's a mock
ChunkAssembler::ChunkAssembler() {
  adjacency_list = new Vector<ChunkData>[4];
  fill_list();
}

// TODO that's a mock
void ChunkAssembler::fill_list(bool is_mock = false) noexcept {
  if (adjacency_list == nullptr)
    return;

  Vector<ChunkData> chunk_data;
  if (is_mock) {
    for (size_t i = 0; i < 4; i++) {
      const size_t b = rand() % 4;
      const size_t e = rand() % 4;
      ChunkData c = {i, b, e, nullptr};
      chunks.push_back(c);
    }
  } else {
    for (size_t i = 0; i < chunks.size(); i++) {
      ChunkData c = {i, chunks.at(i).};
    }
  }

  for (ChunkData first : chunks) {
    std::cout << "{ id : " << first.id << " b: " << first.begin
              << " e: " << first.end << std::endl;
    for (ChunkData second : chunks) {
      if (first.id == second.id)
        continue;
      if (first.end == second.begin) {
        adjacency_list[first.id].push_back(second);
      }
    }
  }
}

void ChunkAssembler::print_list() const noexcept {
  for (size_t i = 0; i < 4; i++) {
    std::cout << i << "-";
    for (ChunkData c : adjacency_list[i]) {
      std::cout << c.id << " ";
    }
    std::cout << std::endl;
  }
}

ChunkAssembler::ChunkData ChunkAssembler::next() noexcept {
  // TODO
  /*
  if current is null then
      > current = first(adj_list)
   else
      let rand = this->random_gen->next(len(adj_list[current->id]))
      > current = adj_list[current->id][rand]
  */
}
