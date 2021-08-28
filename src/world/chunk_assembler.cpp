/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  04/22/2021

  chunk_assembler.cpp: implementation for World::ChunkAssembler.
*/

#include "chunk_assembler.hpp"
#include "../nostd/matrix.hpp"
#include "position.hpp"

using Data::Pawns::Enemy;
using Data::Pawns::Item;
using Engine::BlockTile;
using Engine::Tile;
using namespace World;
using namespace Nostd;
using namespace Data;

ChunkAssembler::ChunkAssembler(const Vector<MapChunk> *chunks,
                               const Vector<Scenery> *sceneries,
                               const Vector<Enemy> *enemies,
                               const Vector<Item> *items)
    : chunks(chunks), sceneries(sceneries), enemies(enemies), items(items),
      current_scenery(nullptr), current_chunk(nullptr), chunks_assembled(0) {}

constexpr size_t ChunkAssembler::sceneries_duration;

// Step 1 implementation (a): select the next MapChunk to assemble using
// Poisson's distribution in order to chose a random number keeping track of the
// difficulty of the game. The first chosen is always the first of the chunks
// vector
void ChunkAssembler::next_chunk() noexcept {
  if (current_chunk == nullptr) {
    this->current_chunk = &this->chunks->at(0);
    return;
  }
  auto rand = random_gen.get_poisson_random(
      RandomGenerator::calculate_mean(chunks_assembled, chunks->size()),
      chunks->size());
  this->current_chunk = &this->chunks->at(rand);
}

// Step 1 implementation (b): select randomly which Scenery will be used next by
// the assembler
void ChunkAssembler::next_scenery() noexcept {
  auto rand = random_gen.get_random(this->sceneries->size());
  this->current_scenery = &this->sceneries->at(rand);
}

// Step 2 implementation: combine a Data::MapChunk with a Data::Scenery to make
// a Nostd::Matrix<World::MapPixel> iterating through each MapUnit. Sky gradient
// is chosen using Fibonacci's sequence.
Matrix<Tile *>
ChunkAssembler::assemble_scenery(const MapChunk *chunk,
                                 const Scenery *scenery) const noexcept {
  Matrix<Tile *> res({chunk->height, chunk->width()});
  size_t sky_index = scenery->sky.size() - 1;
  size_t sky_counter = 2 * fib(sky_index);
  for (size_t i{0}; i < chunk->height; i++) {
    for (size_t j{0}; j < chunk->width(); j++) {
      MapUnit map_unit = chunk->at(i).at(j).value();
      if (map_unit == MapUnit::nothing || map_unit == MapUnit::enemy ||
          map_unit == MapUnit::item)
        res.at(i).at(j).value() = new BlockTile(' ', Engine::Color::transparent,
                                                scenery->sky[sky_index]);
      else if (map_unit == MapUnit::ground)
        res.at(i).at(j).value() = new BlockTile(
            elaborate_autotile(chunk, &scenery->ground, j, i),
            scenery->ground.foreground, scenery->ground.background);
      else if (map_unit == MapUnit::platform)
        res.at(i).at(j).value() = new BlockTile(
            elaborate_autotile(chunk, &scenery->platform, j, i),
            scenery->platform.foreground, scenery->platform.background);
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

// Step 3 implementation: given a MapChunk in input checks enemies presence and
// location
Pair<List<Enemy>, Matrix<Enemy *>>
ChunkAssembler::assemble_enemies(const MapChunk *chunk) noexcept {
  Matrix<Enemy *> matrix({chunk->height, chunk->width()}, nullptr);
  List<Enemy> list;

  for (size_t i{0}; i < chunk->height; i++) {
    for (size_t j{0}; j < chunk->width(); j++) {
      size_t r = random_gen.get_poisson_random(
          RandomGenerator::calculate_mean(chunks_assembled, enemies->size()),
          enemies->size());
      if (chunk->at(i)->at(j)->value() == MapUnit::enemy &&
          r != enemies->size()) {
        list.push_back(enemies->at(r));
        matrix.at(i)->at(j)->value() = &list.back();
      }
    }
  }
  return {list, matrix};
}

// Step 4 implementation: given a MapChunk in input checks items presence and
// location
Pair<List<Item>, Matrix<Item *>>
ChunkAssembler::assemble_items(const MapChunk *chunk) noexcept {
  Matrix<Item *> matrix({chunk->height, chunk->width()}, nullptr);
  List<Item> list;

  for (size_t i{0}; i < chunk->height; i++) {
    for (size_t j{0}; j < chunk->width(); j++) {
      size_t r = random_gen.get_poisson_random_reverse(
          RandomGenerator::calculate_mean(chunks_assembled, items->size()),
          items->size());
      if (chunk->at(i)->at(j)->value() == MapUnit::item && r != items->size()) {
        list.push_back(items->at(r));
        matrix.at(i)->at(j)->value() = &list.back();
      }
    }
  }
  return {list, matrix};
}

// Fibonacci's function helper. It isn't the fastest impementation (\theta(n)
// instead of \theta(log n)) but it's a good compromise beetween performances
// and coding complexity.
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
                                        const size_t &x,
                                        const size_t &y) const noexcept {
  // gop = ground or platform
  if (y == 0 ||
      !is_ground_or_platform(
          chunk->at(y - 1).at(x).value())) { // chunk top or anything upon us
    if (x == 0)                              // chunk start
      return tile->top_left;
    else if (x == chunk->width() - 1) // chunk end
      return tile->top_right;
    if (is_ground_or_platform(chunk->at(y)->at(x - 1).value())) { // gop left
      if (is_ground_or_platform(chunk->at(y)->at(x + 1).value())) // gop right
        return tile->top;
      else
        return tile->top_right;
    } else
      return tile->top_left;
  } else if (y == chunk->height - 1 || // chunk bottom or anything under
             !is_ground_or_platform(chunk->at(y + 1).at(x).value())) {
    if (x == 0) // chunk start
      return tile->bottom_left;
    else if (x == chunk->width() - 1) // chunk end
      return tile->bottom_right;
    if (is_ground_or_platform(chunk->at(y)->at(x - 1).value())) { // gop left
      if (is_ground_or_platform(chunk->at(y)->at(x + 1).value())) // gop right
        return tile->bottom;
      else
        return tile->bottom_right;
    } else
      return tile->bottom_left;
  } else {      // something upon and something under
    if (x == 0) // start of chunk
      return tile->left;
    else if (x == chunk->width() - 1) // end of chunk
      return tile->right;
    if (is_ground_or_platform(chunk->at(y)->at(x - 1).value())) {   // gop left
      if (is_ground_or_platform(chunk->at(y)->at(x + 1).value())) { // gop right
        if (!is_ground_or_platform(chunk->at(y - 1)->at(x - 1).value()))
          return tile->concave_top_left;
        else if (!is_ground_or_platform(chunk->at(y - 1)->at(x + 1).value()))
          return tile->concave_top_right;
        else if (!is_ground_or_platform(chunk->at(y + 1)->at(x - 1).value()))
          return tile->concave_bottom_left;
        else if (!is_ground_or_platform(chunk->at(y + 1)->at(x + 1).value()))
          return tile->concave_bottom_right;
        else
          return tile->center;
      } else
        return tile->right;
    } else
      return tile->left;
  }
}

inline bool
ChunkAssembler::is_ground_or_platform(const MapUnit &u) const noexcept {
  return u == MapUnit::ground || u == MapUnit::platform;
}

// Get a World::WorldExpansion by combining all the assembling steps
WorldExpansion ChunkAssembler::get() noexcept {
  // Step 1
  next_chunk();
  if (chunks_assembled % sceneries_duration == 0)
    next_scenery();
  chunks_assembled++;
  // Step 3
  auto enemies = assemble_enemies(current_chunk);
  // Step 4
  auto items = assemble_items(current_chunk);
  // Step 2
  return WorldExpansion(
      current_chunk, assemble_scenery(current_chunk, current_scenery),
      enemies.second, enemies.first, items.second, items.first);
}

// Getters
const MapChunk *ChunkAssembler::get_current_chunk(void) const noexcept {
  return this->current_chunk;
}
const Scenery *ChunkAssembler::get_current_scenery(void) const noexcept {
  return this->current_scenery;
}

// Clear the clutter
void ChunkAssembler::dispose(Matrix<Tile *> &x) noexcept {
  for (auto &y : x)
    for (auto &z : y) {
      delete z.value();
      z.value() = nullptr;
    }
}

#include "../nostd/matrix.cpp"
