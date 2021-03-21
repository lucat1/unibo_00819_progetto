#ifndef BOX_HPP
#define BOX_HPP

#include "../../nostd/pair.hpp"
#include <map>
#include <ncurses.h>
#include <stdint.h>
using namespace std;
using namespace Nostd;

namespace Engine {
namespace UI {

class Box {
protected:
  // padding(left|right|top|bottom)
  uint16_t pl = 0, pr = 0, pt = 0, pb = 0;
  // direction vertical, float right
  bool dv = false, fr = false;

public:
  enum Props {
    DIRECTION, // vertical = 0, horizontal = 1
    FLOAT,     // left = 0, right = 1

    // paddsings
    PADDING_LEFT,
    PADDING_RIGHT,
    PADDING_TOP,
    PADDING_BOTTOM,
  };

  uint16_t max_width, max_height, max_child_width, max_child_height;
  Box *first_child = nullptr, *last_child = nullptr, *sibling = nullptr,
      *parent = nullptr;

  Box(uint16_t max_width, uint16_t max_height,
      map<enum Box::Props, uint16_t> props = {});

  virtual void show(WINDOW *window, uint16_t x, uint16_t y);
  virtual Pair<uint16_t, uint16_t> size();
  void add_child(Box *box);
};

} // namespace UI
} // namespace Engine

#endif // BOX_HPP
