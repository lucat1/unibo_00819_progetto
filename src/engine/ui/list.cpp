/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  03/14/2021

  list.cpp: Implements the Engine::UI::List class methods. It is a minimal
  variation of the box container where we take care to properly place children
  and display the needed markers.
*/
#include "list.hpp"

const uint16_t Engine::UI::List::default_left_padding = 2;
const wchar_t Engine::UI::List::append_default_value = L'*';

Engine::UI::List::List(uint16_t max_width, uint16_t max_height,
                       const wchar_t marker)
    : Box(max_width, max_height) {
  // override props which are fixed for lists
  this->pl = 2;
  this->dh = false;
  this->fr = false;
  this->marker = marker;
  this->max_child_width = max_child_width - pl;
}

// draws each child prefixed by a centered marker
void Engine::UI::List::show(WINDOW *window, uint16_t x, uint16_t y) {
  Box::show(window, x, y);
  uint16_t rel_y = 0;
  Box *it = first_child;

  while (it != nullptr && rel_y < max_child_height) {
    auto child_size = it->size();
    mvwaddch(window, y + rel_y + (child_size.second / 2), x, marker);
    rel_y += child_size.second;
    it = it->sibling;
  }
}

Nostd::Pair<uint16_t, uint16_t> Engine::UI::List::size() {
  auto psize = Box::size();
  // the list removes 2 chars from the width to make room for the markers so
  // here we sum that to the size of its children (calculated by the method at
  // Box::size)
  uint16_t width = psize.first + default_left_padding;
  return {width, psize.second};
}
