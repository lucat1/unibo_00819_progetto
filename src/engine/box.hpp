#ifndef BOX_HPP
#define BOX_HPP

#include <ncurses.h>

namespace Engine {

class Box {
public:
  Box *children;
  Box *sibling;

  void show();

protected:
  WINDOW *window;
};

} // namespace Engine

#endif
