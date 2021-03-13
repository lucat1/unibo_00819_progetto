#ifndef LIST_HPP
#define LIST_HPP

#include "box.hpp"

namespace Engine {
namespace UI {

class List : public Box {
private:
  wchar_t marker;

public:
  List(uint8_t width, uint8_t height, const wchar_t marker = L'*');

  void show(WINDOW *window, uint16_t x, uint16_t y);
  bsize_t size();
};

} // namespace UI
} // namespace Engine

#endif // LIST_HPP
