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
    bsize isize = iter->size();
    // don't render items outside of this Box
    // TODO: scrollbars (?)
    if (next_x + isize.s[1] > max_x)
      break;

    iter->show(window, next_x, y);
    next_x = next_x + isize.s[0];
    iter = iter->sibling;
  }
}

bsize_t VertBox::size() {
  Box *iter = this->first_child;
  uint16_t width = 0, height = 0;
  while (iter != nullptr) {
    bsize_t size = iter->size();
    width += size.s[0];
    height = max(height, size.s[1]);

    iter = iter->sibling;
  }

  return bsize_t{{width, height}};
}
