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

const Engine::UI::Box::szu Engine::UI::List::default_left_padding = 2;
const wchar_t Engine::UI::List::append_default_value = L'*';

Engine::UI::List::List(const wchar_t marker) : Box() {
  // override props which are fixed for lists
  this->pl = 2;
  this->dh = false;
  this->fr = false;
  this->marker = marker;
}

void Engine::UI::List::show(WINDOW *window, szu x, szu y, szu max_width,
                            szu max_height) {
  Box::show(window, x, y, max_width, max_height);
  szu rel_y = 0, remaining_height = max_height - pt - pb;

  for (Box *it = first_child; it != nullptr && rel_y < remaining_height;
       it = it->sibling) {
    szu child_height = it->size(max_width, max_height).second;
    mvwaddch(window, y + rel_y + (child_height / 2), x + 1, marker);

    rel_y += child_height;
    remaining_height -= child_height;
  }
}
