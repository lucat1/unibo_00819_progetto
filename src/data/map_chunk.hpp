/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/06/2021

  map_chunk.hpp: user interface of Data::MapChunk and its helper entities.
*/

#ifndef DATA_MAP_CHUNK_HPP
#define DATA_MAP_CHUNK_HPP

#include <cstddef>
#include <istream>

#include "../nostd/matrix.hpp"

namespace Data {

/*
  A MapUnit, as its name suggests, is the basic unit of a MapChunk. As such, it
  can be used to describe what can be found at a certain position of the game
  world (but not its appearence). Its underlying type is char so that a MapChunk
  can be represented in a neat, visual fashion.
*/
enum class MapUnit : char {
  nothing = '.',
  ground = '#',
  platform = '=',
  enemy = '!', // every enemy is drawn over MapUnit.nothing
  item = '$'   // every item is drawn over MapUnit.nothing
};

// A MapUnit can be read from an input stream using its underlying character.
std::istream &operator>>(std::istream &, MapUnit &);

/*
  A MapChunk describes the topology of a piece of the game world, but not its
  appearence. This is greatly different from the current state of part of the
  game world.
*/
class MapChunk : public Nostd::Matrix<MapUnit> {
public:
  // width is mandatory
  MapChunk() = delete;
  // - width is the number of columns of the map
  // - the starting row is the one used to let the player enter from the left
  // - the ending row is the one used to let the player exit from the right
  // - value is the initial value of every MapUnit in it
  MapChunk(size_t width, MapUnit value = MapUnit::nothing);
  MapChunk(MapChunk &&) = default;
  MapChunk &operator=(MapChunk &&) = default;
  MapChunk(const MapChunk &) = default;
  MapChunk &operator=(const MapChunk &) = default;

  ~MapChunk() = default;

  // capacity
  size_t width() const noexcept;      // number of columns
  constexpr static size_t height{24}; // number of rows
};

// A stream can represent a MapChunk using:
// - a line with a single size_t (the width of the MapChunk)
// - MapChunk::height lines, each containing as many valid MapUnit chars as the
// width
//   of the map
std::istream &operator>>(std::istream &, MapChunk &);

} // namespace Data

#include "../nostd/matrix.cpp"

#endif
