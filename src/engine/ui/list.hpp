#ifndef LIST_HPP
#define LIST_HPP

#include "box.hpp"

namespace Engine {
namespace UI {

class List : public Box {
protected:
  wchar_t marker;

public:
  static List append(Box box);
  List(uint8_t width, uint8_t height, wchar_t marker);
};

} // namespace UI
} // namespace Engine

#endif // LIST_HPP
