/*
  University of bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  03/22/2021

  center.hpp: Declares the Engine::UI::Center class, which is just a Box with
  the extended functionality of being able to center items
  horizonatlly/vertically.
*/
#ifndef ENGINE_UI_CENTER_HPP
#define ENGINE_UI_CENTER_HPP

#include "box.hpp"

namespace Engine {
namespace UI {
class Center : public Box {
private:
  bool center_horizontally = 0;

public:
  Center(uint16_t max_width, uint16_t max_height);
  void propb(Box::Property key, bool value);

  void show(WINDOW *window, uint16_t x, uint16_t y);
  Nostd::Pair<uint16_t, uint16_t> size();
};

} // namespace UI
} // namespace Engine

#endif // ENGINE_UI_CENTER_HPP
