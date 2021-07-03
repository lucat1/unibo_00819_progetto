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
  static constexpr const szu logo_width = 70, logo_height = 8;
  static constexpr const char *logo[logo_height] = {
" _____                                _                              _    ",
"|  _  |                              (_)                            | |   ",
"| | | |_   _____ _ __ ___ _ __   __ _ _ _ __   ___  ___ _ __ ___  __| |   ",
"| | | \\ \\ / / _ \\ '__/ _ \\ '_ \\ / _` | | '_ \\ / _ \\/ _ \\ '__/ _ \\/ _` |   ",
"\\ \\_/ /\\ V /  __/ | |  __/ | | | (_| | | | | |  __/  __/ | |  __/ (_| |   ",
" \\___/  \\_/ \\___|_|  \\___|_| |_|\\__, |_|_| |_|\\___|\\___|_|  \\___|\\__,_|   ",
"                                 __/ |                                    ",
"                                |___/                                     "
  };

  // constructs the parent class (TextBox) with the static logo strings
  Logo();

  // override the TextBox's split_content function to always assign the logo
  // data
  strings split_content(const Nostd::WString content, szu max_width);

  void show(WINDOW *window, szu x, szu y, szu max_width, szu max_height);
  dim size(szu max_width, szu max_height);
};

} // namespace UI
} // namespace Engine

#endif // ENGINE_UI_LOGO_HPP
