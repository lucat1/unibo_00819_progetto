#include "box.hpp"
#include <algorithm>
#include <ncurses.h>
#include <unistd.h>
using namespace std;
using namespace Engine::UI;

// Engine::UI::Box has nothing to do with ncurses's box function
// We use Box as a UI primitive to build interfaces. For example each block
// (be it a List, a Button, a Checkbox) extends the box class, which provides
// rendering primitives such as the automatic display of its children in the
// appropriate order
Box::Box(uint16_t max_width, uint16_t max_height) {
  this->max_width = max_width;
  this->max_height = max_height;
  this->first_child = nullptr;
  this->last_child = nullptr;
  this->sibling = nullptr;
  this->parent = nullptr;
}

// internal usage only!
// used to add a new child to the list of children of this *box
// NOTE(to self): add_child makes the width and height of the child not exceed
// the ones of the parent
void Box::add_child(Box *new_box) {
  if (new_box->max_width > max_width)
    new_box->max_width = max_width;

  if (new_box->max_height > max_height)
    new_box->max_height = max_height;

  if (last_child != nullptr)
    last_child->sibling = new_box;

  new_box->sibling = nullptr;
  new_box->parent = this;

  last_child = new_box;
  if (first_child == nullptr)
    first_child = new_box;
}

// by default VirtBox is just a container, so we just render its children
// for simplicity we assume children stack one under the other.
// it's more than enough for the menus we'll have to implement
void Box::show(WINDOW *window, uint16_t x, uint16_t y) {
  Box *iter = this->first_child;
  uint16_t next_y = y, max_y = y + max_height;
  while (iter != nullptr) {
    bsize isize = iter->size();
    // don't render items outside of this Box
    // TODO: scrollbars (?)
    if (next_y + isize.s[1] > max_y)
      break;

    iter->show(window, x, next_y);
    next_y = next_y + isize.s[1];
    iter = iter->sibling;
  }
}

bsize_t Box::size() {
  Box *iter = this->first_child;
  uint16_t width = 0, height = 0;
  while (iter != nullptr) {
    bsize_t size = iter->size();
    width = max(width, size.s[0]);
    height += size.s[1];

    iter = iter->sibling;
  }

  return bsize_t{{width, height}};
}
