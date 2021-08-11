/*
  University of bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  07/01/2021

  arrow.hpp: Declares the Engine::UI::Arrow class, draws hardcoded arrows
*/

#ifndef ENGINE_UI_ARROW_HPP
#define ENGINE_UI_ARROW_HPP

#include "box.hpp"

namespace Engine {
namespace UI {

// Draws a left or right arrow of a fixed size with a simple loop
class Arrow : public Box {
public:
  static constexpr const szu width = 3;
  static constexpr const szu height = 6;

private:
  bool left;

public:
  Arrow(bool left);

  void show(WINDOW *window, szu x, szu y, szu max_width, szu max_height);
  dim size(szu max_width, szu max_height);
};

} // namespace UI
} // namespace Engine

#endif // ENGINE_UI_ARROW_HPP
