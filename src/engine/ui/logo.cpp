/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  03/29/2021

  logo.cpp: Implements the Engine::UI::Logocomponent which simply hijacks a
  TextBox by overwiring the lines content and placing inside of it its hardcoded
  logo lines.
*/

#include "logo.hpp"
#include "../../data/palette.hpp"

constexpr const wchar_t *Engine::UI::Logo::logo[];

Engine::UI::Logo::Logo() : TextBox(L"") {
  propc(Box::Property::foreground, Data::Palette::logo.first);
  propc(Box::Property::background, Data::Palette::logo.second);
}

Engine::UI::TextBox::strings
Engine::UI::Logo::split_content(const Nostd::WString content, szu max_width) {
  strings lines;
  for (size_t i = 0; i < logo_height; i++)
    lines.push_back(logo[i]);

  return lines;
}

void Engine::UI::Logo::show(WINDOW *window, szu x, szu y, szu max_width,
                            szu max_height) {
  // force the text box to draw the logo
  lines = split_content(content, max_width);
  old_max_width = max_width;

  TextBox::show(window, x, y, max_width, max_height);
}

Engine::UI::Box::dim Engine::UI::Logo::size(szu max_width, szu max_height) {
  return {logo_width, logo_height};
}
