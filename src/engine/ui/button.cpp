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

Engine::UI::Button::Button(const wchar_t *content) : TextBox(content) {}
Engine::UI::Button::Button(const Nostd::WString &content) : TextBox(content) {}

Engine::UI::Box::dim Engine::UI::Button::text_size(szu max_width,
                                                   szu max_height) {
  szu w = max_width - (2 * side_padding) - pl - pr,
      h = max_height - (2 * side_padding) - pt - pb;
  return {w, h};
}

void Engine::UI::Button::show(WINDOW *window, szu x, szu y, szu max_width,
                              szu max_height) {
  auto text_max_sz = text_size(max_width, max_height);

  // draw the button's background
  auto sz = TextBox::size(text_max_sz.first, text_max_sz.second);
  start_color(window);
  for (uint16_t i = 0; i < sz.second + 2; i++)
    mvwhline(window, y + i + pt, x + pl, ' ', sz.first + 2 * side_padding);
  end_color(window);

  attron(A_BOLD);
  TextBox::show(window, x + side_padding + pl, y + 1 + pt, text_max_sz.first,
                text_max_sz.second);
  attroff(A_BOLD);
}

Engine::UI::Box::dim Engine::UI::Button::size(szu max_width, szu max_height) {
  auto text_max_sz = text_size(max_width, max_height);
  auto sz = TextBox::size(text_max_sz.first, text_max_sz.second);

  szu width = pl + pr + sz.first + 2 * side_padding,
      height = pt + pb + sz.second + 2;
  return {width, height};
}
