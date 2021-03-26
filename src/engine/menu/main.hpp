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

  void handle_event(Event e);
};

} // namespace Menu
} // namespace Engine

#endif // ENGINE_MENU_MAIN_HPP
