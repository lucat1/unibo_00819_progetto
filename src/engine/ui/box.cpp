#include "box.hpp"
#include <ncurses.h>
#include <unistd.h>
using namespace Engine::UI;

// Engine::UI::Box has nothing to do with ncurses's box function
// We use Box as a UI primitive to build interfaces. For example each block
// (be it a List, a Button, a Checkbox) extends the box class, which provides
// rendering primitives such as the automatic display of its children in the
// appropriate order
Box::Box(uint16_t width, uint16_t height) {
  this->width = width;
  this->height = height;
  this->first_child = nullptr;
  this->last_child = nullptr;
  this->sibling = nullptr;
  this->parent = nullptr;
}

// Creates a new Box instance and adds it to the target Box's list of children.
// The width and height of the new box can be defined relatively to the new
// parent's dimentions with the w and h parameters
Box *Box::append(Box *target, float w, float h) {
  Box *new_box = new Box(target->width * w, target->height * h);
  target->add_child(new_box);
  return new_box;
}

// internal usage only!
// used to add a new child to the list of children of this *box
// NOTE(to self): add_child makes the width and height of the child not exceed
// the ones of the parent
void Box::add_child(Box *new_box) {
  if (new_box->width > width)
    new_box->width = width;

  if (new_box->height > height)
    new_box->height = height;

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
  uint8_t next_y = y, max_y = y + height;
  while (iter != nullptr) {
    // don't render items outside of this Box
    // TODO: scrollbars (?)
    if (next_y + iter->height > max_y)
      break;

    iter->show(window, x, next_y);
    next_y = next_y + iter->height;
    iter = iter->sibling;
  }
}