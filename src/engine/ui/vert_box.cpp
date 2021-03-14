#include "vert_box.hpp"
#include <algorithm>
using namespace std;
using namespace Engine::UI;

VertBox::VertBox(uint16_t max_width, uint16_t max_height)
    : Box(max_width, max_height) {}

void VertBox::show(WINDOW *window, uint16_t x, uint16_t y) {
  Box *iter = this->first_child;
  uint16_t next_x = x, max_x = x + max_width;
  while (iter != nullptr) {
    Pair<uint16_t, uint16_t> isize = iter->size();
    // don't render items outside of this Box
    // TODO: scrollbars (?)
    if (next_x + isize.second > max_x)
      break;

    iter->show(window, next_x, y);
    next_x = next_x + isize.first;
    iter = iter->sibling;
  }
}

Pair<uint16_t, uint16_t> VertBox::size() {
  Box *iter = this->first_child;
  uint16_t width = 0, height = 0;
  while (iter != nullptr) {
    Pair<uint16_t, uint16_t> size = iter->size();
    width += size.first;
    height = max(height, size.second);

    iter = iter->sibling;
  }

  return {width, height};
}
