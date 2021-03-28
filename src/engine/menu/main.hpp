/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  03/22/2021

  main.hpp: Defines the Engine::Menu::Main drawable, which is the main menu for
  the game. It is the first interactive screen printed to the user when the game
  is launched. It's aim is to allow the user to tweak settings or start a new
  match.
*/
#ifndef ENGINE_MENU_MAIN_HPP
#define ENGINE_MENU_MAIN_HPP

#include "../drawable.hpp"
#include "../ui/box.hpp"

namespace Engine {
namespace Menu {

class Main : public Drawable {
private:
  UI::Box *root;

  UI::Box *generate();
  void redraw();

public:
  Main(WINDOW *window);
  ~Main();

  void handle_event(Event e);
};

} // namespace Menu
} // namespace Engine

#endif // ENGINE_MENU_MAIN_HPP
