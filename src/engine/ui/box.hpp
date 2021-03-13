#ifndef BOX_HPP
#define BOX_HPP

#include <ncurses.h>
#include <stdint.h>

namespace Engine {
namespace UI {

class Box {

public:
  uint16_t width, height;
  Box *first_child, *last_child, *sibling, *parent;

  Box(uint16_t width, uint16_t height);

  virtual void show(WINDOW *window, uint16_t x, uint16_t y);
  static Box *append(Box *box, float w, float h);
  void add_child(Box *box);
};

} // namespace UI
} // namespace Engine

#endif // BOX_HPP
