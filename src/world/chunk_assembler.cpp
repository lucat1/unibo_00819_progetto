/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  04/22/2021

  chunk_assembler.cpp: TODO.
*/

#include "chunk_assembler.hpp"
#include "../nostd/matrix.hpp"
#include "map_pixel.hpp"
#include <cstddef>
#include <cstdlib>
#include <iostream>

using namespace World;
using namespace Nostd;
using namespace Data;
using namespace Engine;

ChunkAssembler::ChunkAssembler(Vector<MapChunk> chunks,
                               Vector<Scenery> sceneries) {
  this->chunks = chunks;
  this->sceneries = sceneries;
  this->adjacency_list = new Vector<ChunkInfo>[chunks.size()];
  this->current_scenery = sceneries[0];
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
MapChunk *ChunkAssembler::next_chunk() noexcept {
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

// Combine a Data::MapChunk with a Data::Scenery to make a
// Nostd::Matrix<World::MapPixel>.
Matrix<MapPixel>
ChunkAssembler::assemble_scenery(const MapChunk *chunk,
                                 const Scenery scenery) const noexcept {
  MapPixel nullPixel('?', Color::transparent, Color::transparent);
  Matrix<MapPixel> res({chunk->height, chunk->width()}, nullPixel);
  for (size_t i{0}; i < chunk->height; i++) {
    for (size_t j{0}; j < chunk->width(); j++) {
      MapUnit map_unit = chunk->at(i).at(j).value();
      if (map_unit == MapUnit::nothing)
        res.at(i).at(j).value() =
            MapPixel(' ', Color::transparent, scenery.sky[0]);
      else if (map_unit == MapUnit::ground)
        res.at(i).at(j).value() =
            MapPixel(scenery.ground.singlet, scenery.ground.foreground,
                     scenery.ground.background);
      else if (map_unit == MapUnit::platform)
        res.at(i).at(j).value() =
            MapPixel(scenery.platform.singlet, scenery.platform.foreground,
                     scenery.ground.background);
    }
  }
  return res;
}

Matrix<MapPixel> ChunkAssembler::get() noexcept {
  MapChunk *c = next_chunk();
  return assemble_scenery(c, this->current_scenery);
}

// Debug only
void ChunkAssembler::print_scenery(Scenery s) noexcept {
  MapChunk *c = next_chunk();
  Matrix<MapPixel> a = assemble_scenery(c, s);
  std::cout << "Printing scenery" << std::endl;
  for (auto row : a) {
    for (auto x : row)
      std::wcout << x.value().character();
    std::wcout << std::endl;
  }
}
#include "../nostd/matrix.cpp"
