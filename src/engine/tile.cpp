/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/12/21

  Mattia Girolimetto #977478
  06/26/21

  tile.cpp: implementation of Engine::Tile.
*/

#include "tile.hpp"

using Engine::Tile;

wchar_t Tile::character() const { return L' '; }

bool Tile::operator==(const Tile &tile) const {
  return character() == tile.character() && background() == tile.background() &&
         foreground() == tile.foreground();
}

bool Tile::operator!=(const Tile &tile) const { return !(*this == tile); }
