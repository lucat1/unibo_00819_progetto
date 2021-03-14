#include "list.hpp"
using namespace Engine::UI;

#define LIST_PADDING 2

List::List(uint16_t max_width, uint16_t max_height, const wchar_t marker)
    : Box(max_width, max_height) {
  this->marker = marker;
}

void List::show(WINDOW *window, uint16_t x, uint16_t y) {
  Box *iter = this->first_child;
  uint16_t next_y = y, max_y = y + max_height;
  while (iter != NULL) {
    Pair<uint16_t, uint16_t> isize = iter->size();
    // don't render items outside of this Box
    // TODO: scrollbars (?)
    if (next_y + isize.second > max_y) {
      break;
    }

    mvwaddch(window, next_y, x, marker);
    iter->show(window, x + LIST_PADDING, next_y);
    next_y = next_y + isize.second;
    iter = iter->sibling;
  }
}

Pair<uint16_t, uint16_t> List::size() {
  Pair<uint16_t, uint16_t> psize = Box::size();
  // the list removes 2 chars from the width to make room for the markers so
  // here we sum that to the size of its children (calculated by the method at
  // Box::size)
  uint16_t width = psize.first + LIST_PADDING;
  return {width, psize.second};
}
