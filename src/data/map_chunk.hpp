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
  enemy = '!',
  item = '$'
};

std::basic_istream<char> &operator>>(std::basic_istream<char> &, MapUnit &);

/*
  A MapChunk describes the topology of a piece of the game world, but not its
  appearence. This is greatly different from the current state of part of the
  game world.
*/
class MapChunk : public Nostd::Matrix<MapUnit> {
public:
  // width is mandatory
  MapChunk() = delete;
  // width is the number of columns of the map, value is the initial value of
  // every MapUnit in it
  MapChunk(size_t width, size_t starting_row, size_t ending_row,
           MapUnit value = MapUnit::nothing);
  MapChunk(MapChunk &&) = default;
  MapChunk &operator=(MapChunk &&) = default;
  MapChunk(const MapChunk &) = default;
  MapChunk &operator=(const MapChunk &) = default;

  ~MapChunk() = default;

  // capacity
  size_t width() const noexcept;
  constexpr static size_t height{20};

  // 0-based index of the player's starting row (usually right above floor)
  size_t starting_row() const noexcept;
  // 0-based index of the player's ending row (usually right above floor)
  size_t ending_row() const noexcept;

private:
  size_t strt_row, end_row;
};

// A stream can represent a MapChunk using:
// - a line with a single size_t (the width of the MapChunk)
// - MapChunk::height lines, each containing as many valid MapUnit chars as the
// width
//   of the map
std::basic_istream<char> &operator>>(std::basic_istream<char> &, MapChunk &);

} // namespace Data

#include "../nostd/matrix.cpp"

#endif
