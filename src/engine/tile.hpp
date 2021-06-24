/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  06/12/2021

  Stefano Volpe #969766
  06/12/2021

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
protected:
  Tile() = default;

public:
  virtual wchar_t character() const;
  virtual ~Tile() = default;
};

} // namespace Engine

#endif
