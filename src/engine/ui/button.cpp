/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  03/22/2021

  button.cpp: Implements the rendering (done via a ncurses subwindow) of the
  Engine::UI::Button element. Most work is done in the show method to create the
  ncurses' window and set its content properly.
*/
#include "button.hpp"

Engine::UI::Button::Button(uint16_t max_width, uint16_t max_height,
                           const wchar_t *content)
    : TextBox(max_width - 2, max_height - 2, content) {}
Engine::UI::Button::Button(uint16_t max_width, uint16_t max_height,
                           Nostd::WString &&content)
    : TextBox(max_width - 2, max_height - 2, content.c_str()) {}

void Engine::UI::Button::show(WINDOW *window, uint16_t x, uint16_t y) {
  start_color(window);
  // draw the button's background
  auto sz = TextBox::size();
  for (uint16_t i = 0; i < sz.second + 2; i++)
    mvwhline(window, y + i, x, ' ', sz.first + 2 * side_padding);

  attron(A_BOLD);
  TextBox::show(window, x + side_padding, y + 1);
  attroff(A_BOLD);
  end_color(window);
}

Nostd::Pair<uint16_t, uint16_t> Engine::UI::Button::size() {
  auto osize = TextBox::size();
  uint16_t width = pl + pr + osize.first + 2 * side_padding,
           height = pt + pb + osize.second + 2;
  return {width, height};
}
