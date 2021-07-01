/*
  University of bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  06/27/2021

  results.hpp: Defines the Engine::Menu::Select menu, used to pick the champion
  for the current match.
*/

#ifndef ENGINE_MENU_SELECT_HPP
#define ENGINE_MENU_SELECT_HPP

#include "../../data/pawns/hero.hpp"
#include "../../nostd/vector.hpp"
#include "menu.hpp"

namespace Engine {
namespace Menu {

class Select : public Menu {
private:
  const Nostd::Vector<Data::Pawns::Hero> &heroes;
  int focused = 0, max_focused;
  int clicked_on = -1;
  void add_arrow(UI::Box *root, bool left);

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
  // a list that would require it to be a double linked list, with the last item
  // poiting to the head, which we did not implement.
  Select(WINDOW *window, const Nostd::Vector<Data::Pawns::Hero> &heroes);
  bool is_over();
  Data::Pawns::Hero get_result();
};

} // namespace Menu
} // namespace Engine

#endif // ENGINE_MENU_SELECT_HPP
