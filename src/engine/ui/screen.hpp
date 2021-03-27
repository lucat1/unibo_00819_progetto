#ifndef ENGINE_UI_SCREEN_HPP
#define ENGINE_UI_SCREEN_HPP

#include "box.hpp"

namespace Engine {
namespace UI {

class Screen : public Box {
private:
  // x, y are the offest from the screen (left, top) to start
  // printing inside the game centered window (Box instance)
  WINDOW *window, *screen;
  uint16_t x, y, terminal_cols, terminal_lines;
  bool can_fit();

public:
  static const uint16_t SCREEN_COLS = 80;
  static const uint16_t SCREEN_LINES = 25;
  Screen();

  bool open();
  bool update();
  void close();
};

} // namespace UI
} // namespace Engine

#endif // ENGINE_UI_SCREEN_HPP
