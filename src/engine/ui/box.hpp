#ifndef BOX_HPP
#define BOX_HPP

#include <ncurses.h>
#include <stdint.h>

namespace Engine {
namespace UI {

typedef struct bsize {
  uint16_t s[2]; // {x, y}
} bsize_t;

class Box {

public:
  uint16_t max_width, max_height;
  Box *first_child, *last_child, *sibling, *parent;

  Box(uint16_t max_width, uint16_t max_height);

  virtual void show(WINDOW *window, uint16_t x, uint16_t y);
  virtual bsize_t size();
  void add_child(Box *box);
};

} // namespace UI
} // namespace Engine

#endif // BOX_HPP
