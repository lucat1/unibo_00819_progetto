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
  static List *append(Box *box, float w, float h, const wchar_t marker = L'*');
};

} // namespace UI
} // namespace Engine

#endif // LIST_HPP
