#include "list.hpp"
using namespace Engine::UI;

List::List(uint8_t width, uint8_t height, const wchar_t marker)
    : Box(width, height) {
  this->marker = marker;
}

// Creates a new List instance and adds it to the target Box's children.
List *List::append(Box *target, float w, float h, const wchar_t marker) {
  // - 2 for the marker and a space
  List *list = new List((target->width * w) - 2, target->height * h, marker);
  target->add_child(list);
  return list;
}

void List::show(WINDOW *window, uint16_t x, uint16_t y) {
  Box *iter = this->first_child;
  uint8_t next_y = y, max_y = y + height;
  while (iter != NULL) {
    // don't render items outside of this Box
    // TODO: scrollbars (?)
    if (next_y + iter->height > max_y) {
      break;
    }

    mvwaddch(window, next_y, x, marker);
    iter->show(window, x + 2, next_y);
    next_y = next_y + iter->height;
    iter = iter->sibling;
  }
}
