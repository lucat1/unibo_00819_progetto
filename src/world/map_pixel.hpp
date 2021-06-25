/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  06/24/2021

  tree_map.test.cpp: tests for Nostd::TreeMap.
*/
#ifndef WORLD_MAP_PIXEL_HPP
#define WORLD_MAP_PIXEL_HPP

#include "../engine/tile.hpp"

namespace World {
class MapPixel : public Engine::Tile {
private:
  wchar_t c;
  Engine::Color bg;
  Engine::Color fg;

public:
  MapPixel() = default;
  MapPixel(wchar_t icon, Engine::Color fg, Engine::Color bg) noexcept;

  Engine::Color background() const override;
  Engine::Color foreground() const override;
  wchar_t character() const override;

  // Required for being Regular
  bool operator==(MapPixel) const;
  // Required for being Regular
  bool operator!=(MapPixel) const;
};
} // namespace World

#endif
