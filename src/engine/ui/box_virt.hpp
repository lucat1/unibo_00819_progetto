#ifndef BOX_VIRT_HPP
#define BOX_VIRT_HPP

#include <ncurses.h>
#include <stdint.h>

namespace Engine {
namespace UI {

class BoxVirt {
public:
  uint16_t width, height;
  BoxVirt *children, *sibling, *parent;

  virtual void show(WINDOW *window, uint16_t x, uint16_t y);
};

} // namespace UI
} // namespace Engine

#endif // BOX_VIRT_HPP
