#ifndef BOX_HPP
#define BOX_HPP

#include "../../nostd/pair.hpp"
#include <ncurses.h>
#include <stdint.h>
using namespace Nostd;

namespace Engine {
namespace UI {

class Box {
public:
  uint16_t max_width, max_height;
  Box *first_child, *last_child, *sibling, *parent;

  Box(uint16_t max_width, uint16_t max_height);

  virtual void show(WINDOW *window, uint16_t x, uint16_t y);
  virtual Pair<uint16_t, uint16_t> size();
  void add_child(Box *box);
};

} // namespace UI
} // namespace Engine

#endif // BOX_HPP
