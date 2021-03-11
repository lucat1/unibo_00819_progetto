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
  this->children = nullptr;
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
// NOTE to self: add_child makes the width and height of the child not exceed
// the ones of the parent
void Box::add_child(Box *new_box) {
  if (new_box->width > this->width)
    new_box->width = this->width;

  if (new_box->height > this->height)
    new_box->height = this->height;

  new_box->sibling = this->children;
  new_box->parent = this;
  this->children = new_box;
}

void Box::show(uint16_t x, uint16_t y) {}
