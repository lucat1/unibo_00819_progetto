#ifndef ENGINE_UI_LIST_HPP
#define ENGINE_UI_LIST_HPP

#include "box.hpp"

namespace Engine {
namespace UI {

class List : public Box {
private:
  wchar_t marker;

public:
  static const uint16_t default_left_padding;
  static const wchar_t append_default_value;

  List(uint16_t max_width, uint16_t max_height,
       const wchar_t marker = append_default_value);

  void show(WINDOW *window, uint16_t x, uint16_t y);
  Nostd::Pair<uint16_t, uint16_t> size();
};

} // namespace UI
} // namespace Engine

#endif // ENGINE_UI_LIST_HPP
