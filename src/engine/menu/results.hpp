/*
  University of bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  04/26/2021

  results.hpp: Defines the Engine::Menu::Results menu, which displays each
  hero score after the match has ended.
*/

#ifndef ENGINE_MENU_RESULTS_HPP
#define ENGINE_MENU_RESULTS_HPP

#include "../../data/result.hpp"
#include "menu.hpp"

namespace Engine {
namespace Menu {

class Results : public Menu {
private:
  Nostd::Vector<Data::Result> results;
  int focused = 0, max_focused = 0;
  int clicked_on = -1;

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
  Results(WINDOW *window, const Nostd::Vector<Data::Result> &results);
  bool is_over();
};

} // namespace Menu
} // namespace Engine

#endif // ENGINE_MENU_RESULTS_HPP
