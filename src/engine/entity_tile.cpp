/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  06/26/2021

  Stefano Volpe #969766
  06/26/2021

  entity_tile.cpp: implementation of Engine::EntityTile.
*/

#include "entity_tile.hpp"

using Engine::EntityTile;

EntityTile::EntityTile(wchar_t character, Engine::Color foreground)
    : chr{character}, fg{foreground} {}

wchar_t EntityTile::character() const noexcept { return chr; }

auto EntityTile::foreground() const noexcept -> Color { return fg; }
