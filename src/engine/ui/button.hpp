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

// Button draws a (hopefully) single line text box with big margins
// (side_padding) and colors it prpoerly to make it resemble a button
class Button : public TextBox {
private:
  dim text_size(szu max_width, szu max_height);

public:
  static const constexpr szu side_padding = 4;

  Button(const Nostd::WString &content = "");
  Button(const char *content = "");

  void show(WINDOW *window, szu x, szu y, szu max_width, szu max_height);
  dim size(szu max_width, szu max_height);
};

} // namespace UI
} // namespace Engine

#endif // ENGINE_UI_BUTTON_HPP
