/*
  University of bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  03/15/2021

  text_box.hpp: Defines the Engine::UI::TextBox class used to display text in
  the UI with the constraint of fitting the give max_width.
*/

#ifndef ENGINE_UI_TEXT_BOX_HPP
#define ENGINE_UI_TEXT_BOX_HPP

#include "../../nostd/wstring.hpp"
#include "box.hpp"

namespace Engine {
namespace UI {

// Displays a text content and wraps a long sentence in multiple lines properly
//
// NOTE: deliberately ignores any padding given. To achieve that wrap this
// element inside a Box
class TextBox : public Box {
public:
  using strings = Nostd::Vector<Nostd::WString>;

protected:
  Nostd::WString content;
  strings lines;
  szu old_max_width = -1;
  // updates the lines by re-splitting the content if necessary( namely width
  // has changed)
  void update_lines(szu max_width);

public:
  // splits the content into various lines to fit into `max_width` and adds
  // '-' where necessary, when splitting a word
  static strings split_content(const Nostd::WString content, szu max_width);

  static constexpr const char *append_default_value = "";
  TextBox(const Nostd::WString &content = "");
  TextBox(const char *content = "");

  void show(WINDOW *window, szu x, szu y, szu max_width, szu max_height);
  dim size(szu max_width, szu max_height);
};

} // namespace UI
} // namespace Engine

#endif // ENGINE_UI_TEXT_BOX_HPP
