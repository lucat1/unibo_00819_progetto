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
Engine::UI::Button::~Button() {
  delwin(button_window);
  button_window = nullptr;
}

void Engine::UI::Button::show(WINDOW *window, uint16_t x, uint16_t y) {
  auto osize = TextBox::size();
  uint16_t abs_x, abs_y;
  getbegyx(window, abs_y, abs_x);

  if (button_window != nullptr)
    delwin(button_window);

  button_window = newwin(osize.second + 2, osize.first + 2 * side_padding,
                         abs_y + y, abs_x + x);
  wclear(button_window);
  refresh();

  int color = color_pair();
  if (color != -1)
    wbkgd(button_window, color);

  // draw a box of ' ' chars to around the text to fill the background
  mvwhline(button_window, 0, 1, ' ', osize.first + side_padding - 1);
  mvwvline(button_window, 0, 0, ' ', osize.second + 2);
  mvwvline(button_window, 0, osize.first + 1, ' ', osize.second + 2);
  mvwhline(button_window, osize.second + 1, 1, ' ',
           osize.first + side_padding - 1);

  TextBox::show(button_window, side_padding, 1);
  refresh();
  wrefresh(button_window);
}
Nostd::Pair<uint16_t, uint16_t> Engine::UI::Button::size() {
  auto osize = TextBox::size();
  uint16_t width = osize.first + 2 * side_padding, height = osize.second + 2;
  return {width, height};
}
