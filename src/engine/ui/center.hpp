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

// Centers its content either veritcally or horizontally.
// NOTE: does not respect the padding values. If padding is needed please wrap
// this element in a standard Engine::UI::Box.
class Center : public Box {
private:
  bool center_horizontally = false;

public:
  Center() = default;
  void propb(Box::Property key, bool value);

  void show(WINDOW *window, szu x, szu y, szu max_width, szu max_height);
  dim size(szu max_width, szu max_height);
};

} // namespace UI
} // namespace Engine

#endif // ENGINE_UI_CENTER_HPP
