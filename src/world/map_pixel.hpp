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

#include "../engine/colorable.hpp"

namespace World {
class MapPixel : public Engine::Colorable {
private:
  Engine::Color fg;
  Engine::Color bg;

public:
  wchar_t icon;

  MapPixel(wchar_t icon, Engine::Color fg, Engine::Color bg) noexcept;

  Engine::Color background() const override;
  Engine::Color foreground() const override;

  // Required for being Regular
  bool operator==(MapPixel);
};
} // namespace World

#endif
