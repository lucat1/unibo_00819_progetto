#ifndef ENGINE_UI_BOX_HPP
#define ENGINE_UI_BOX_HPP

#include "../../nostd/pair.hpp"
#include "../colorable.hpp"
#include <map>
#include <ncurses.h>
#include <stdint.h>

namespace Engine {
namespace UI {

class Box : public Colorable {
protected:
  static size_t ncurses_pair_index;

  // child list values
  Box *first_child = nullptr, *last_child = nullptr;
  // padding(left|right|top|bottom)
  uint16_t pl = 0, pr = 0, pt = 0, pb = 0;
  // direction vertical, float right, should we paint custom colors
  bool dv = false, fr = false;

  // color values
  bool color = false;
  Engine::Color fg = Colorable::foreground(), bg = Colorable::background();

public:
  enum Props {
    DIRECTION, // vertical = 0, horizontal = 1
    FLOAT,     // left = 0, right = 1

    // paddsings
    PADDING_LEFT,
    PADDING_RIGHT,
    PADDING_TOP,
    PADDING_BOTTOM,

    FOREGROUND,
    BACKGROUND,
  };

  uint16_t max_width, max_height, max_child_width, max_child_height;
  Box *sibling = nullptr, *parent = nullptr;

  Box(uint16_t max_width, uint16_t max_height,
      std::map<enum Box::Props, uint16_t> props = {});
  void update(std::map<enum Box::Props, uint16_t> props);

  virtual void show(WINDOW *window, uint16_t x, uint16_t y);
  virtual Nostd::Pair<uint16_t, uint16_t> size();
  void add_child(Box *box);
  Box *child(size_t n);

  Engine::Color foreground();
  Engine::Color background();
  int color_pair();
};

} // namespace UI
} // namespace Engine

#endif // ENGINE_UI_BOX_HPP
