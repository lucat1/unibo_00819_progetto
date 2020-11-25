#ifndef ENGINE_HPP
#define ENGINE_HPP

class Box {
public:
  Box *children;
  Box *sibling;

  void draw();
};

#endif
