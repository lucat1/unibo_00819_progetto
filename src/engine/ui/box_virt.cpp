#include "box_virt.hpp"
using namespace Engine::UI;

// by default VirtBox is just a container, so we just render its children
// for simplicity we assume children stack one under the other.
// it's more than enough for the menus we'll have to implement
void BoxVirt::show(WINDOW *window, uint16_t x, uint16_t y) {
  BoxVirt *iter = this->children;
  uint8_t next_y = y, max_y = y + height;
  while (iter != NULL) {
    // don't render items outside of this Box
    // TODO: scrollbars (?)
    if (next_y + iter->height > max_y)
      break;

    iter->show(window, x, next_y);
    next_y = next_y + iter->height;
    iter = iter->sibling;
  }
}
