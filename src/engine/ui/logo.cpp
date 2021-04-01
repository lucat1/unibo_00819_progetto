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

const uint16_t logo_width = 28, logo_height = 6;
const wchar_t *logo[logo_height] = {
    L"        _                   ", L"       | |                  ",
    L"  __ _ | | _ __ ___    __ _ ", L" / _` || || '_ ` _ \\  / _` |",
    L"| (_| || || | | | | || (_| |", L" \\__,_||_||_| |_| |_| \\__,_|",
};

Engine::UI::Logo::Logo(uint16_t max_width, uint16_t max_height)
    : TextBox(max_width - 2, max_height - 2, L"") {
  lines.clear();
  for (size_t i = 0; i < logo_height; i++)
    lines.push_back(logo[i]);

  propc(Box::Property::foreground, Color::red);
}

Nostd::Pair<uint16_t, uint16_t> Engine::UI::Logo::size() {
  return {logo_width, logo_height};
}
