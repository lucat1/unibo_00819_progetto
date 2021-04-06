/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/06/2021

  map.hpp: user interface of Data::Map.
*/

#ifndef DATA_MAP_HPP
#define DATA_MAP_HPP

#include <istream>

#include "../nostd/matrix.hpp"

namespace Data {

/*
  A MapUnit, as its name suggests, is the basic unit of a Map. As such, it can
  be used to describe what can be found at a certain position of the game world
  (but not its appearence). Its underlying type is char so that a Map can be
  represented in a neat, visual fashion.
*/
enum class MapUnit : char {
  nothing = ' ',
  ground = '#',
  platform = '=',
  enemy = '!',
  item = '$'
};

/*
  A Map describes the topology of a piece of the game world, but not its
  appearence. This is greatly different from the current state of part of the
  game world.
*/
class Map : public Nostd::Matrix<MapUnit> {
public:
  // width is mandatory
  Map() = delete;
  Map(size_t width, MapUnit value = MapUnit::nothing);
  // move
  Map(Map &&);
  Map &operator=(Matrix &&);
  // copy
  Map(const Map &);
  Map &operator=(const Map &);

  ~Map();

  // capacity
  size_t width() const noexcept;
  constexpr static size_t height{20};
};

// A stream can represent a Map using:
// - a line with a single int (the width of the Map)
// - Map::height lines, each containing as many valid MapUnit chars as the width
//   of the map
std::basic_istream<wchar_t> &operator>>(std::basic_istream<wchar_t> &, Map &);

} // namespace Data

#endif
