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
#include <curses.h>

#include <iostream>
using namespace std;

Engine::UI::Button::Button(uint16_t max_width, uint16_t max_height,
                           const wchar_t *content)
    : TextBox(max_width - 2, max_height - 2, content) {}
Engine::UI::Button::Button(uint16_t max_width, uint16_t max_height,
                           Nostd::WString &&content)
    : TextBox(max_width - 2, max_height - 2, content.c_str()) {}
Engine::UI::Button::~Button() {
  werase(button_window);
  delwin(button_window);
  button_window = nullptr;
}

void Engine::UI::Button::show(WINDOW *window, uint16_t x, uint16_t y) {
  auto osize = TextBox::size();
  uint16_t abs_x, abs_y;
  getbegyx(window, abs_y, abs_x);

  if (button_window != nullptr)
    mvwin(button_window, abs_y + y, abs_x + x);
  else
    button_window =
        newwin(pt + osize.second + 2, pl + osize.first + 2 * side_padding,
               abs_y + y, abs_x + x);

  int color = color_pair();
  if (color != -1)
    wbkgd(button_window, color);
  werase(button_window);

  attron(A_BOLD);
  TextBox::show(button_window, side_padding, 1);
  attroff(A_BOLD);
  /* cout << "l8r" << endl; */
  redrawwin(button_window);
  wrefresh(button_window);
}

Nostd::Pair<uint16_t, uint16_t> Engine::UI::Button::size() {
  auto osize = TextBox::size();
  uint16_t width = pl + pr + osize.first + 2 * side_padding,
           height = pt + pb + osize.second + 2;
  return {width, height};
}
