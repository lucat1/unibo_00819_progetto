/*
  University of bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  07/01/2021

  mugshot.hpp: Declares the Engine::UI::Mugshot class, which has the only
  purpuse of drawing a mughshot of an hero to screen
*/

#ifndef ENGINE_UI_MUGSHOT_HPP
#define ENGINE_UI_MUGSHOT_HPP

#include "../../data/mugshot.hpp"
#include "box.hpp"

namespace Engine {
namespace UI {

// Displays the mughshot for a champion, which after all is just a Nostd::Matrix
// of n \times n size, so the login will be simple and similar to the general
// game drawing
class Mugshot : public Box {
private:
  Data::Mugshot mugshot;

public:
  Mugshot(const Data::Mugshot &mugshot);
  // overwrite as a noop in this class, colors are defined by mugshot's cells
  void propc(Box::Property key, Color color);

  void show(WINDOW *window, szu x, szu y, szu max_width, szu max_height);
  dim size(szu max_width, szu max_height);
};

} // namespace UI
} // namespace Engine

#endif // ENGINE_UI_MUGSHOT_HPP
