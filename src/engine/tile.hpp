/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/12/2021

  Mattia Girolimetto #977478
  06/26/21

  tile.hpp: user interface of Engine::Tile.
*/

#ifndef ENGINE_TILE_HPP
#define ENGINE_TILE_HPP

#include "colorable.hpp"

namespace Engine {

/*
  Interface for any Colorable entity which can be printed on screen using a
  single character.
*/
class Tile : public Colorable {
public:
  Tile() = default;
  Tile(Tile &&) = default;
  Tile &operator=(Tile &&) = default;
  Tile(const Tile &) = default;
  Tile &operator=(const Tile &) = default;

  virtual char character() const;
  virtual ~Tile() = default;

  bool operator==(const Tile &) const;
  bool operator!=(const Tile &) const;
};

} // namespace Engine

#endif
