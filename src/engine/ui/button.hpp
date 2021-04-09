/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  03/22/2021

  button.hpp: Defines Engine::UI::Button visual component, clearly identifiable
  by its monochrome background, shrot text and interactable nature.
*/
#ifndef ENGINE_UI_BUTTON_HPP
#define ENGINE_UI_BUTTON_HPP

#include "text_box.hpp"

namespace Engine {
namespace UI {
class Button : public TextBox {
private:
  static const constexpr uint16_t side_padding = 4;

public:
  Button(uint16_t max_width, uint16_t max_height,
         Nostd::WString &&content = L"");
  Button(uint16_t max_width, uint16_t max_height, const wchar_t *content = L"");

  void show(WINDOW *window, uint16_t x, uint16_t y);
  Nostd::Pair<uint16_t, uint16_t> size();
};

} // namespace UI
} // namespace Engine

#endif // ENGINE_UI_BUTTON_HPP
