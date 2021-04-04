/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  04/04/2021

  settings.hpp: Defines the Engine::Menu::Settings drawable, which is the
  options menu of the game, allowing the user to interact and modify the game
  before launching a match.
*/
#ifndef ENGINE_MENU_SETTINGS_HPP
#define ENGINE_MENU_SETTINGS_HPP

#include "../ui/button.hpp"
#include "../ui/logo.hpp"
#include "menu.hpp"

namespace Engine {
namespace Menu {

class Settings : public Menu {
  // inherit the parent constructor
  using Menu::Menu;

private:
  int focused = 0, max_focused = 1;
  int clicked_on = -1;

protected:
  UI::Box *generate();
  UI::Box *curr_box();
  UI::Box *next_box();
  UI::Box *prev_box();
  void focus(UI::Box *box);
  void unfocus(UI::Box *box);

public:
  bool is_over();
  template <typename T> T get_result();
};

} // namespace Menu
} // namespace Engine

#endif // ENGINE_MENU_SETTINGS_HPP
