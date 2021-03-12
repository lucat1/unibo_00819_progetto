#ifndef LIST_HPP
#define LIST_HPP

#include "box.hpp"

namespace Engine {
namespace UI {

class List : public Box {
private:
  wchar_t marker;

public:
  List(uint8_t width, uint8_t height, wchar_t marker);

  static List append(Box box);
};

} // namespace UI
} // namespace Engine

#endif // LIST_HPP
