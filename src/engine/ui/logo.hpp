/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  03/29/2021

  logo.hpp: Defines the Engine::UI::Logocomponent which displays a static, hard
  coded logo ascii text. It is used in the Engine::Menu::Main drawable.
*/
#ifndef ENGINE_UI_LOGO_HPP
#define ENGINE_UI_LOGO_HPP

#include "text_box.hpp"

namespace Engine {
namespace UI {
class Logo : public TextBox {
public:
  Logo(uint16_t max_width, uint16_t max_height);

  Nostd::Pair<uint16_t, uint16_t> size();
};

} // namespace UI
} // namespace Engine

#endif // ENGINE_UI_LOGO_HPP
