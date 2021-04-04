/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  03/31/2021

  menu.hpp: Defines the Engine::Menu::Menu base class which we use as a further
  abstraction on top of the Drawable class. We can make certain assumptions
  about the mechanic of menus so that we can share more functionality acorss
  them.
*/
#ifndef ENGINE_MENU_MENU_HPP
#define ENGINE_MENU_MENU_HPP

#include "../drawable.hpp"
#include "../ui/box.hpp"

// A Menu is an opinionated class used to share common functionaliteis across
// menus, based on these assumptions:
// - Each menus is going to contain some form of a UI structure, therefore we
// provide a virtual method called `generate` to build the initial UI tree.
//   - The aforementioned method is going to populate the `root` of the UI which
//   is going to be kept in memory throughout the existance of the menu and
//   modified across time
// - The UI in a menu is only changed upon the reception of events, so we can
// remove this duty from various Menu implementations and centralize this code
// here
// - All menus are going to have so called "focusable" items. They are items
// which the user can focus, as a way of selecting them and therefore being able
// to interact with them. To provide a movement across these focusable items on
// the arrival on `move_*` events, the subclasses are requested to implement the
// `next_box`, `prev_box` which return a pointer to the next/previous UI element
// to focus
// - Two more methods are required to implement the just-mentioned
// functionality:
//   - `focus` which changes the UI visuals to notify the user that a certain
//   element has gain focus
//   - `unfocus` which changes the UI visuals to notify the user that a certain
//   element has lost focus
namespace Engine {
namespace Menu {

class Menu : public Drawable {
private:
  bool first_draw = true;
  void redraw();

protected:
  UI::Box *root = nullptr;

  virtual UI::Box *generate() = 0;
  virtual UI::Box *curr_box() = 0;
  virtual UI::Box *next_box() = 0;
  virtual UI::Box *prev_box() = 0;
  virtual void focus(UI::Box *box) = 0;
  virtual void unfocus(UI::Box *box) = 0;
  virtual void interact(UI::Box *box) = 0;

public:
  Menu(WINDOW *window);
  ~Menu();
  void handle_event(Event e);
};

} // namespace Menu
} // namespace Engine

#endif // ENGINE_MENU_MENU_HPP
