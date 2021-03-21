#include "list.hpp"

const uint16_t Engine::UI::List::default_left_padding = 2;
const wchar_t Engine::UI::List::append_default_value = L'*';

Engine::UI::List::List(uint16_t max_width, uint16_t max_height,
                       map<enum Engine::UI::Box::Props, uint16_t> props,
                       const wchar_t marker)
    : Box(max_width, max_height, props) {
  // override props which are fixed for lists
  this->pl = 2;
  this->dv = false;
  this->fr = false;
  this->marker = marker;
  this->max_child_width = max_width - pl;
}

void Engine::UI::List::show(WINDOW *window, uint16_t x, uint16_t y) {
  Box::show(window, x, y);
  uint16_t rel_y = 0;
  Box *it = first_child;

  while (it != nullptr && rel_y < max_child_height) {
    Pair<uint16_t, uint16_t> child_size = it->size();
    mvwaddch(window, y + rel_y, x, marker);
    rel_y += child_size.second;
    it = it->sibling;
  }
}

Pair<uint16_t, uint16_t> Engine::UI::List::size() {
  Pair<uint16_t, uint16_t> psize = Box::size();
  // the list removes 2 chars from the width to make room for the markers so
  // here we sum that to the size of its children (calculated by the method at
  // Box::size)
  uint16_t width = psize.first + default_left_padding;
  return {width, psize.second};
}
