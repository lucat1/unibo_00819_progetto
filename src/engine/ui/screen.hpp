#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "box.hpp"

#define SCREEN_COLS 80
#define SCREEN_LINES 25

namespace Engine {
namespace UI {

class Screen : public Box {
private:
  // x, y are the offest from the screen (left, top) to start
  // printing inside the game centered window (Box instance)
  uint16_t x, y, terminal_cols, terminal_lines;
  bool can_fit();

public:
  Screen();

  bool open();
  bool update();
  void close();
};

} // namespace UI
} // namespace Engine

#endif // SCREEN_HPP
