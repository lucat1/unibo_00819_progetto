#ifndef APPEND_HPP
#define APPEND_HPP

#include "box.hpp"
#include <algorithm>
using namespace std;

namespace Engine {
namespace UI {

template <typename T>
// Creates a new %T instance and adds it to the target Box's list of children.
// The width and height of the new box can be defined relatively to the new
// parent's dimentions with the w and h parameters
T *append(Box *target, float w, float h) {
  uint16_t width = target->max_width * min(w, (float)1);
  uint16_t height = target->max_height * min(h, (float)1);
  T *box = new T(width, height);
  target->add_child(box);
  return box;
}

template <typename T, typename A>
// Creates a new %T instance and adds it to the target Box's list of children.
// The width and height of the new box can be defined relatively to the new
// parent's dimentions with the w and h parameters
T *append(Box *target, float w, float h, A arg) {
  uint16_t width = target->max_width * min(w, (float)1);
  uint16_t height = target->max_height * min(h, (float)1);
  T *box = new T(width, height, arg);
  target->add_child(box);
  return box;
}

} // namespace UI
} // namespace Engine

#endif // APPEND_HPP
