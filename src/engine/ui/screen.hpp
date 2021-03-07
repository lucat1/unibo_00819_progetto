#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "box.hpp"

#define SCREEN_COLS 80
#define SCREEN_LINES 25

namespace Engine {

class Screen : public Box {
public:
  bool open();
  bool recenter();
  void close();

private:
  WINDOW *terminal;
  int terminal_cols, terminal_lines, terminal_offset_cols,
      terminal_offset_lines;
  bool measure();
};

} // namespace Engine

#endif
