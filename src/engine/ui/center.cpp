/*
  University of bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  03/21/2021

  center.cpp: Implements the Engine::UI::Center class with its centering
  computations.
*/
#include "center.hpp"
#include <cmath>

Engine::UI::Center::Center(uint16_t max_width, uint16_t max_height)
    : Box(max_width, max_height) {}

void Engine::UI::Center::propb(Box::Property key, bool value) {
  switch (key) {
  case Box::Property::center_horizontal:
    center_horizontally = value;
    break;
  default:
    Box::propb(key, value);
  }
}

void Engine::UI::Center::show(WINDOW *window, uint16_t x, uint16_t y) {
  start_color(window);
  if (center_horizontally) {
    uint16_t rel_y = 0;
    for (Box *it = first_child; it != nullptr && rel_y < max_height;
         it = it->sibling) {
      auto size = it->size();
      uint16_t rel_x = std::max((max_width - size.first) / 2, 0);
      it->show(window, x + rel_x, y + rel_y);
      rel_y += size.second;
    }
  } else {
    uint16_t rel_y = std::max((max_height - Box::size().second) / 2, 0);
    for (Box *it = first_child; it != nullptr && rel_y < max_height;
         it = it->sibling) {
      it->show(window, x, y + rel_y);
      rel_y += it->size().second;
    }
  }
  end_color(window);
}

Nostd::Pair<uint16_t, uint16_t> Engine::UI::Center::size() {
  auto size = Box::size();
  uint16_t width = size.first, height = size.second;
  if (center_horizontally)
    width = max_width;
  else
    height = max_height;

  return {width, height};
}
