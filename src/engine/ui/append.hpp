/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  03/17/2021

  append.hpp: a set of two utility functions used to append a children to a
  parent, providing the ability to change the children's relative size and the
  option to use an extra argument for some classes.
*/
#ifndef ENGINE_UI_APPEND_HPP
#define ENGINE_UI_APPEND_HPP

#include "box.hpp"

namespace Engine {
namespace UI {

template <typename T>
// Creates a new %T instance and adds it to the target Box's list of children.
// The width and height of the new box can be defined relatively to the new
// parent's dimentions with the w and h parameters
T *append(Box *target, float w = 1, float h = 1) {
  uint16_t width = w > 1 ? w : target->max_child_width * w;
  uint16_t height = h > 1 ? h : target->max_child_height * h;
  T *box = new T(width, height);
  target->add_child(box);
  return box;
}

template <typename T, typename A>
// Creates a new %T instance and adds it to the target Box's list of children.
// The width and height of the new box can be defined relatively to the new
// parent's dimentions with the w and h parameters
T *append(Box *target, A extra = T::append_default_value, float w = 1,
          float h = 1) {
  uint16_t width = w > 1 ? w : target->max_child_width * w;
  uint16_t height = h > 1 ? h : target->max_child_height * h;
  T *box = new T(width, height, extra);
  target->add_child(box);
  return box;
}

} // namespace UI
} // namespace Engine

#endif // ENGINE_UI_APPEND_HPP
