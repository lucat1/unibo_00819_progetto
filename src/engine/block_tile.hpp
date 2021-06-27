/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/26/2021

  block_tile.hpp: user interface of Engine::BlockTile.
*/

#ifndef ENGINE_BLOCK_TILE_HPP
#define ENGINE_BLOCK_TILE_HPP

#include "colorable.hpp"
#include "entity_tile.hpp"

namespace Engine {

/*
  A BlockTile stores its character and colors in three different variables,
*/
class BlockTile : public virtual EntityTile {
public:
  BlockTile() = default;
  BlockTile(wchar_t, Engine::Color = Engine::Color::transparent,
            Engine::Color background = Engine::Color::transparent);
  BlockTile(BlockTile &&) = default;
  BlockTile &operator=(BlockTile &&) = default;
  BlockTile(const BlockTile &) = default;
  BlockTile &operator=(const BlockTile &) = default;

  ~BlockTile() = default;

  Color background() const noexcept override final;

private:
  Engine::Color bg{Engine::Color::transparent};
};

} // namespace Engine

#endif
