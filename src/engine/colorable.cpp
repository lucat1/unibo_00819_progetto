/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  03/20/2021

  colorable.cpp: Implements the default methods for the pure virtual class
  Engine::Colorable.
*/
#include "colorable.hpp"

<<<<<<< HEAD
int Engine::color_to_int(Color c) noexcept { return static_cast<int>(c); }
=======
short Engine::color_to_short(Color c) noexcept { return static_cast<short>(c); }

Engine::Color Engine::short_to_color(short c) noexcept {
  return static_cast<Engine::Color>(c);
}
>>>>>>> 2e9becb (add coloring support to TextBoxes)

Engine::Color Engine::Colorable::foreground() const { return Color::white; }

Engine::Color Engine::Colorable::background() const {
  return Color::transparent;
}
