/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  04/01/2021

  map_pixel.cpp: Metohds implementation for World::MapPixel.
*/
#include "map_pixel.hpp"

using namespace World;
using namespace Engine;

MapPixel::MapPixel(wchar_t icon, Color fg, Color bg) noexcept {
  this->icon = icon;
  this->fg = fg;
  this->bg = bg;
}

Color MapPixel::foreground() const { return fg; }
Color MapPixel::background() const { return bg; }

bool MapPixel::operator==(MapPixel m) const { return m.icon == icon; }
bool MapPixel::operator!=(MapPixel m) const { return m.icon != icon; }
