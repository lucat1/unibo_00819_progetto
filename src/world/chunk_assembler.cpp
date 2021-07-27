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
  this->chunks_assembled = 0;
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

void ChunkAssembler::next_scenery() noexcept {
  auto rand = random_gen.get_random(this->sceneries->size());
  this->current_scenery = &this->sceneries->at(rand);
}

// Combine a Data::MapChunk with a Data::Scenery to make a
// Nostd::Matrix<World::MapPixel>.
// Sky color is chosen using Fibonacci's sequence.
Matrix<BlockTile *>
ChunkAssembler::assemble_scenery(const MapChunk *chunk,
                                 const Scenery *scenery) const noexcept {
  BlockTile *nullPixel =
      new BlockTile('?', Color::transparent, Color::transparent);
  Matrix<BlockTile *> res({chunk->height, chunk->width()}, nullPixel);
  size_t sky_index = scenery->sky.size() - 1;
  size_t sky_counter = 2 * fib(sky_index);
  for (size_t i{0}; i < chunk->height; i++) {
    for (size_t j{0}; j < chunk->width(); j++) {
      MapUnit map_unit = chunk->at(i).at(j).value();
      if (map_unit == MapUnit::nothing || map_unit == MapUnit::enemy ||
          map_unit == MapUnit::item)
        res.at(i).at(j).value() =
            new BlockTile(' ', Color::transparent, scenery->sky[sky_index]);
      else if (map_unit == MapUnit::ground)
        res.at(i).at(j).value() = new BlockTile(
            elaborate_autotile(chunk, &scenery->ground, j, i),
            scenery->ground.foreground, scenery->ground.background);
      else if (map_unit == MapUnit::platform)
        res.at(i).at(j).value() = new BlockTile(
            elaborate_autotile(chunk, &scenery->platform, j, i),
            scenery->platform.foreground, scenery->ground.background);
    }
    if (sky_index > 0) {
      if (--sky_counter == 0) {
        sky_index--;
        sky_counter = 2 * fib(sky_index);
      }
    }
  }
  return res;
}

inline size_t ChunkAssembler::fib(const size_t &n) const noexcept {
  if (n == 0 || n == 1)
    return 1;
  size_t a = 1;
  size_t b = 1;
  for (size_t i = 2; i <= n; i++) {
    int c = b;
    b += a;
    a = c;
  }
  return b;
}

char ChunkAssembler::elaborate_autotile(const MapChunk *chunk,
                                        const Scenery::Autotile *tile,
                                        const int &x,
                                        const int &y) const noexcept {
  if (y == 0 || chunk->at(y - 1).at(x).value() == MapUnit::nothing) {
    if (x == 0)
      return tile->top_left;
    else if (x == (int)chunk->width() - 1)
      return tile->top_right;
    if (chunk->at(y)->at(x - 1).value() != MapUnit::nothing) {
      if (chunk->at(y)->at(x + 1).value() != MapUnit::nothing)
        return tile->top;
      else
        return tile->top_right;
    } else
      return tile->top_left;
  } else if (y == chunk->height - 1 ||
             chunk->at(y + 1).at(x).value() == MapUnit::nothing) {
    if (x == 0)
      return tile->bottom_left;
    else if (x == (int)chunk->width() - 1)
      return tile->bottom_right;
    if (chunk->at(y)->at(x - 1).value() != MapUnit::nothing) {
      if (chunk->at(y)->at(x + 1).value() != MapUnit::nothing)
        return tile->bottom;
      else
        return tile->bottom_right;
    } else
      return tile->bottom_left;
  } else {
    if (x == 0)
      return tile->left;
    else if (x == (int)chunk->width() - 1)
      return tile->right;
    if (chunk->at(y)->at(x - 1).value() != MapUnit::nothing) {
      if (chunk->at(y)->at(x + 1).value() != MapUnit::nothing)
        return tile->center;
      else
        return tile->right;
    } else
      return tile->left;
  }
}
Matrix<BlockTile *> ChunkAssembler::get() noexcept {
  const MapChunk *const c = this->current_chunk;
  this->chunks_assembled++;
  if (chunks_assembled % 10 == 0)
    next_scenery();
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
