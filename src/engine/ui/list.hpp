/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  02/14/2021

  list.hpp: Defines the Engine::UI::List class. A list is a container which
  holds a number of children placed one after the other in a vertical
  orientation. Each child is preceeded by a marker (one singole wchar).
*/
#ifndef ENGINE_UI_LIST_HPP
#define ENGINE_UI_LIST_HPP

#include "box.hpp"

namespace Engine {
namespace UI {

// draws each child prefixed by a centered marker
class List : public Box {
private:
  wchar_t marker;

public:
  static const uint16_t default_left_padding;
  static const wchar_t append_default_value;

  List(const wchar_t marker = append_default_value);

  void show(WINDOW *window, szu x, szu y, szu max_width, szu max_height);
};

} // namespace UI
} // namespace Engine

#endif // ENGINE_UI_LIST_HPP
