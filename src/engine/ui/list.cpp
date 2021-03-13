#include "list.hpp"
using namespace Engine::UI;

List::List(uint8_t max_width, uint8_t max_height, const wchar_t marker)
    : Box(max_width, max_height) {
  this->marker = marker;
}

void List::show(WINDOW *window, uint16_t x, uint16_t y) {
  Box *iter = this->first_child;
  uint8_t next_y = y, max_y = y + max_height;
  while (iter != NULL) {
    // don't render items outside of this Box
    // TODO: scrollbars (?)
    if (next_y + iter->max_height > max_y) {
      break;
    }

    mvwaddch(window, next_y, x, marker);
    iter->show(window, x + 2, next_y);
    next_y = next_y + iter->max_height;
    iter = iter->sibling;
  }
}
