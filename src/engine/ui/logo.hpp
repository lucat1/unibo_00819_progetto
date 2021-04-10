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

// NOTE: deliberately ignores any padding given. To achieve that wrap this
// element inside a Box
class Logo : public TextBox {
public:
  static constexpr const szu logo_width = 28, logo_height = 6;
  static constexpr const wchar_t *logo[logo_height] = {
      L"        _                   ", L"       | |                  ",
      L"  __ _ | | _ __ ___    __ _ ", L" / _` || || '_ ` _ \\  / _` |",
      L"| (_| || || | | | | || (_| |", L" \\__,_||_||_| |_| |_| \\__,_|",
  };

  // constructs the parent class (TextBox) with the static logo strings
  Logo();

  // override the TextBox's split_content function to always assign the logo
  // data
  strings split_content(const Nostd::WString content, szu max_width);
};

} // namespace UI
} // namespace Engine

#endif // ENGINE_UI_LOGO_HPP
