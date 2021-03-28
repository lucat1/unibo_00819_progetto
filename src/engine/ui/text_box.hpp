/*
  university of bologna
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

class TextBox : public Box {
public:
  Nostd::WString content;
  Nostd::Vector<Nostd::WString> lines;

  static constexpr const wchar_t *append_default_value = L"";
  TextBox(uint16_t max_width, uint16_t max_height,
          Nostd::WString &&content = L"");
  TextBox(uint16_t max_width, uint16_t max_height,
          const wchar_t *content = L"");

  void split_content();
  Nostd::Pair<uint16_t, uint16_t> size();
  void show(WINDOW *window, uint16_t x, uint16_t y);
};

} // namespace UI
} // namespace Engine

#endif // ENGINE_UI_TEXT_BOX_HPP
