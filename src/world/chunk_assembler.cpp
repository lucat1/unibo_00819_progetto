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
#include <cstddef>
#include <cstdlib>

using namespace World;
using namespace Nostd;
using namespace Data;
using namespace Engine;

ChunkAssembler::ChunkAssembler(const Vector<MapChunk> &chunks,
                               const Vector<Scenery> &sceneries) {
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
  for (size_t i = 0; i < chunks.size(); i++) {
    ChunkInfo x = {i, &chunks[i]};
    infos.at(i) = x;
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
Matrix<BlockTile *>
ChunkAssembler::assemble_scenery(const MapChunk *chunk,
                                 const Scenery scenery) const noexcept {
  BlockTile *nullPixel =
      new BlockTile('?', Color::transparent, Color::transparent);
  Matrix<BlockTile *> res({chunk->height, chunk->width()}, nullPixel);
  for (size_t i{0}; i < chunk->height; i++) {
    for (size_t j{0}; j < chunk->width(); j++) {
      MapUnit map_unit = chunk->at(i).at(j).value();
      if (map_unit == MapUnit::nothing)
        res.at(i).at(j).value() =
            new BlockTile(' ', Color::transparent, scenery.sky[0]);
      else if (map_unit == MapUnit::ground)
        res.at(i).at(j).value() =
            new BlockTile(scenery.ground.singlet, scenery.ground.foreground,
                          scenery.ground.background);
      else if (map_unit == MapUnit::platform)
        res.at(i).at(j).value() =
            new BlockTile(scenery.platform.singlet, scenery.platform.foreground,
                          scenery.ground.background);
    }
  }
  return res;
}

Matrix<BlockTile *> ChunkAssembler::get() noexcept {
  MapChunk *c = next_chunk();
  return assemble_scenery(c, this->current_scenery);
}

#include "../nostd/matrix.cpp"
