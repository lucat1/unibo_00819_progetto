/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  06/26/2021

  Stefano Volpe #969766
  06/26/2021

  block_tile.cpp: implementation of Engine::BlockTile.
*/

#include "block_tile.hpp"

using Engine::BlockTile;

BlockTile::BlockTile(wchar_t character, Engine::Color foreground,
                     Engine::Color background)
    : EntityTile{character, foreground}, bg{background} {}

auto BlockTile::background() const noexcept -> Color { return bg; }
