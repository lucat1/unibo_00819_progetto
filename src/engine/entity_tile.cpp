/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/26/2021

  entity_tile.cpp: implementation of Engine::EntityTile.
*/

#include "entity_tile.hpp"

using Engine::EntityTile;

EntityTile::EntityTile(char character, Engine::Color foreground)
    : chr{character}, fg{foreground} {}

char EntityTile::character() const noexcept { return chr; }

auto EntityTile::foreground() const noexcept -> Color { return fg; }
