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
#include "../../nostd/list.hpp"
#include "menu.hpp"

namespace Engine {
namespace Menu {

class Results : public Menu {
private:
  const Nostd::List<Data::Result> &results;
  bool has_interacted = 0;
  UI::Box *append_line(UI::Box *parent, int rank, int score,
                       const Nostd::WString &nick);
  UI::Box *append_line(UI::Box *parent, const Nostd::WString &rank,
                       const Nostd::WString &score, const Nostd::WString &nick);

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
  Results(WINDOW *window, const Nostd::List<Data::Result> &results);
  bool is_over();
};

} // namespace Menu
} // namespace Engine

#endif // ENGINE_MENU_RESULTS_HPP
