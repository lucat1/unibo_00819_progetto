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

#include "../ui/button.hpp"
#include "../ui/logo.hpp"
#include "menu.hpp"

namespace Engine {
namespace Menu {

class Main : public Menu {
  // inherit the parent constructor
  using Menu::Menu;

private:
  int focused = 0, max_focused = 2;
  int clicked_on = -1;
  UI::Button *append_button(UI::Box *parent, const char *str);

protected:
  UI::Box *generate();
  UI::Box *curr_box();
  UI::Box *next_box();
  UI::Box *prev_box();
  void focus(UI::Box *box);
  void unfocus(UI::Box *box);
  void interact(UI::Box *box);
  void decrement(UI::Box *box);
  void increment(UI::Box *box);

public:
  enum class Result {
    none,
    play,
    settings,
    quit,
  };

  bool is_over();
  Result get_result();
};

} // namespace Menu
} // namespace Engine

#endif // ENGINE_MENU_MAIN_HPP
