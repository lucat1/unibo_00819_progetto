#ifndef VERT_BOX_HPP
#define VERT_BOX_HPP

#include "box.hpp"

namespace Engine {
namespace UI {

class VertBox : public Box {
public:
  VertBox(uint16_t max_width, uint16_t max_height);

  void show(WINDOW *window, uint16_t x, uint16_t y);
  Pair<uint16_t, uint16_t> size();
};

} // namespace UI
} // namespace Engine

#endif // VERT_BOX_HPP
