#ifndef BOX_HPP
#define BOX_HPP

#include <ncurses.h>
#include <unistd.h>

namespace Engine {
namespace UI {

class Box {
protected:
  WINDOW *window;

public:
  uint16_t width, height;
  Box *children, *sibling, *parent;

  Box(uint8_t width, uint8_t height);
  static Box *append(Box *box, float w, float h);

  void add_child(Box *box);
  void show(uint16_t x, uint16_t y);
};

} // namespace UI
} // namespace Engine

#endif // BOX_HPP
