/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/26/2021

  entity_tile.hpp: user interface of Engine::EntityTile.
*/

#ifndef ENGINE_ENTITY_TILE_HPP
#define ENGINE_ENTITY_TILE_HPP

#include "colorable.hpp"
#include "tile.hpp"

namespace Engine {

/*
  An EntityTile stores its character and its foreground color in two variables,
  and its background is transparent by default.
*/
class EntityTile : public Tile {
public:
  EntityTile() = default;
  EntityTile(wchar_t, Engine::Color = Engine::Color::transparent);
  EntityTile(EntityTile &&) = default;
  EntityTile &operator=(EntityTile &&) = default;
  EntityTile(const EntityTile &) = default;
  EntityTile &operator=(const EntityTile &) = default;

  virtual ~EntityTile() = default;

  wchar_t character() const noexcept override final;
  Color foreground() const noexcept override final;

private:
  wchar_t chr{L' '};
  Engine::Color fg{Engine::Color::transparent};
};

} // namespace Engine

#endif
