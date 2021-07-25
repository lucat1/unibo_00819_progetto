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

using namespace World;
using namespace Nostd;
using namespace Data;
using namespace Engine;

ChunkAssembler::ChunkAssembler(const Vector<MapChunk> &chunks,
                               const Vector<Scenery> &sceneries) {
  this->chunks = &chunks;
  this->sceneries = &sceneries;
  this->current_chunk = &this->chunks->at(0);
  this->current_scenery = &this->sceneries->at(0);
}

// Generate a random number i between 0 and the number of nodes liked to Current
// and take the i-esim linked node.
void ChunkAssembler::next_chunk() noexcept {
  auto rand = random_gen.get_random(this->chunks->size());
  MapChunk *selected = new MapChunk(this->chunks->at(rand));

  // Check for up or down shift
  const size_t oldHeight = this->current_chunk->ending_row();
  const size_t lastHeight = selected->starting_row();
  int diff = oldHeight - lastHeight;
  if (abs(diff) > MAX_CHUNKS_HEIGHT_DIFFERECE) {
    shift_chunk(selected, diff < 0 ? diff + MAX_CHUNKS_HEIGHT_DIFFERECE
                                   : diff - MAX_CHUNKS_HEIGHT_DIFFERECE);
  }
  this->current_chunk = selected;
}

// Combine a Data::MapChunk with a Data::Scenery to make a
// Nostd::Matrix<World::MapPixel>.
Matrix<BlockTile *>
ChunkAssembler::assemble_scenery(const MapChunk *chunk,
                                 const Scenery *scenery) const noexcept {
  BlockTile *nullPixel =
      new BlockTile('?', Color::transparent, Color::transparent);
  Matrix<BlockTile *> res({chunk->height, chunk->width()}, nullPixel);
  size_t sky_index = scenery->sky.size() - 1;
  for (size_t i{0}; i < chunk->height; i++) {
    for (size_t j{0}; j < chunk->width(); j++) {
      MapUnit map_unit = chunk->at(i).at(j).value();
      if (map_unit == MapUnit::nothing)
        res.at(i).at(j).value() =
            new BlockTile(' ', Color::transparent, scenery->sky[sky_index]);
      else if (map_unit == MapUnit::ground)
        res.at(i).at(j).value() =
            new BlockTile(scenery->ground.singlet, scenery->ground.foreground,
                          scenery->ground.background);
      else if (map_unit == MapUnit::platform)
        res.at(i).at(j).value() = new BlockTile(scenery->platform.singlet,
                                                scenery->platform.foreground,
                                                scenery->ground.background);
    }
    if (i % 3 == 0 && sky_index > 0)
      sky_index--;
  }
  return res;
}

Matrix<BlockTile *> ChunkAssembler::get() const noexcept {
  const MapChunk *const c = this->current_chunk;
  return assemble_scenery(c, this->current_scenery);
}

const Scenery *ChunkAssembler::get_current_scenery() const noexcept {
  return this->current_scenery;
}

void ChunkAssembler::shift_chunk(MapChunk *chunk,
                                 const int &shifting_factor) noexcept {
  /*for (auto x : *chunk) {
    for (auto y : x) {
      if (y->value() == MapUnit::nothing)
        std::cout << " ";
      else
        std::cout << "#";
    }
    std::cout << std::endl;
  }*/

  for (size_t i{0}; i < chunk->width(); i++) {
    for (size_t j{0}; j < chunk->height; j++) {
      int shifted_index = j + shifting_factor;
      if (shifted_index >= 0 && shifted_index < (int)chunk->height) {
        chunk->at(j).at(i)->value() = chunk->at(shifted_index).at(i)->value();
      } else if (shifted_index < 0) {
        chunk->at(j).at(i).value() = MapUnit::nothing;
      } else if (shifted_index >= (int)chunk->height) {
        chunk->at(j).at(i).value() = chunk->at(chunk->height - 1).at(i).value();
      }
    }
  }

  /*for (auto x : *chunk) {
    for (auto y : x) {
      if (y->value() == MapUnit::nothing)
        std::cout << " ";
      else
        std::cout << "#";
    }
    std::cout << std::endl;
  }*/
}

#include "../nostd/matrix.cpp"
