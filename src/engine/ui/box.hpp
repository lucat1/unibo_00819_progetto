#ifndef BOX_HPP
#define BOX_HPP

#include "box_virt.hpp"
#include <stdint.h>

namespace Engine {
namespace UI {

class Box : public BoxVirt {

public:
  Box(uint16_t width, uint16_t height);

  static Box *append(Box *box, float w, float h);
  void add_child(Box *box);
};

} // namespace UI
} // namespace Engine

#endif // BOX_HPP
