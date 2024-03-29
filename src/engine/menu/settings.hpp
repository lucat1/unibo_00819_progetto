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

#include "../../data/setting.hpp"
#include "../../nostd/vector.hpp"
#include "../ui/button.hpp"
#include "menu.hpp"

namespace Engine {
namespace Menu {

class Settings : public Menu {
private:
  Nostd::Vector<Data::Setting *> updated;
  Nostd::Vector<Data::Setting> original;
  int focused = 0, max_focused;
  int clicked_on = -1;
  void alloc_updated(Nostd::Vector<Data::Setting> &settings);
  Nostd::Vector<Data::Setting> dereference_updated();
  UI::Button *append_button(UI::Box *parent, const char *str);
  UI::Box *append_line(UI::Box *parent, Data::Setting *setting);

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
  Settings(WINDOW *window, const Nostd::Vector<Data::Setting> &settings);
  ~Settings();

  bool is_over();
  Nostd::Vector<Data::Setting> get_result();
};

} // namespace Menu
} // namespace Engine

#endif // ENGINE_MENU_SETTINGS_HPP
