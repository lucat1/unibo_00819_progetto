/*
  University of bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  07/01/2021

  strict_box.hpp: Declares the Engine::UI::StrictBox class which acts as a
  standard box but has an additional layer of size restriction in the form of
  absolute maximum dimentions.
*/

#ifndef ENGINE_UI_STRICT_BOX_HPP
#define ENGINE_UI_STRICT_BOX_HPP

#include "box.hpp"

namespace Engine {
namespace UI {

// Draws a standard box with a constrained absolute maximum width and height
class StrictBox : public Box {
private:
  szu absolute_max_width, absolute_max_height;

public:
  StrictBox(Box::dim max_dimentions);

  dim size(szu max_width, szu max_height);
};

} // namespace UI
} // namespace Engine

#endif // ENGINE_UI_STRICT_BOX_HPP
