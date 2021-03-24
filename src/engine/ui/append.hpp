#ifndef ENGINE_UI_APPEND_HPP
#define ENGINE_UI_APPEND_HPP

#include "box.hpp"
#include <algorithm>
using namespace std;

namespace Engine {
namespace UI {

template <typename T>
// Creates a new %T instance and adds it to the target Box's list of children.
// The width and height of the new box can be defined relatively to the new
// parent's dimentions with the w and h parameters
T *append(Box *target, float w, float h, map<Box::Props, uint16_t> props = {}) {
  uint16_t width = target->max_child_width * min(w, (float)1);
  uint16_t height = target->max_child_height * min(h, (float)1);
  T *box = new T(width, height, props);
  target->add_child(box);
  return box;
}

template <typename T, typename A>
// Creates a new %T instance and adds it to the target Box's list of children.
// The width and height of the new box can be defined relatively to the new
// parent's dimentions with the w and h parameters
T *append(Box *target, float w, float h, map<Box::Props, uint16_t> props = {},
          A extra = T::append_default_value) {
  uint16_t width = target->max_child_width * min(w, (float)1);
  uint16_t height = target->max_child_height * min(h, (float)1);
  T *box = new T(width, height, props, extra);
  target->add_child(box);
  return box;
}

} // namespace UI
} // namespace Engine

#endif // ENGINE_UI_APPEND_HPP
