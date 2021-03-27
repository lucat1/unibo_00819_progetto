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
  if (center_horizontally)
    Box::show(window, x + std::floor((max_width - Box::size().first) / 2), y);
  else
    Box::show(window, x, y + std::floor((max_height - Box::size().second) / 2));
}

Nostd::Pair<uint16_t, uint16_t> Engine::UI::Center::size() {
  if (center_horizontally)
    return {max_width, Box::size().second};
  else
    return {Box::size().first, max_height};
}
