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

constexpr const wchar_t *Engine::UI::Logo::logo[];

Engine::UI::Logo::Logo() : TextBox(L"") {
  propc(Box::Property::foreground, Color::red);
}

Engine::UI::TextBox::strings
Engine::UI::Logo::split_content(const Nostd::WString content, szu max_width) {
  strings lines;
  for (size_t i = 0; i < logo_height; i++)
    lines.push_back(logo[i]);

  return lines;
}
