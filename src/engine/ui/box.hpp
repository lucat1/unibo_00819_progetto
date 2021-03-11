#ifndef BOX_HPP
#define BOX_HPP

#include <ncurses.h>
#include <unistd.h>

namespace Engine {
namespace UI {

class Box {
public:
  uint8_t width, height;
  Box *children, *sibling, *parent;

  Box(uint8_t width, uint8_t height);
  static Box *append(Box *box, float w, float h);

  void add_child(Box *box);
  void show();

protected:
  WINDOW *window;
};

} // namespace UI
} // namespace Engine

#endif // BOX_HPP
