/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  07/01/2021

  arrow.cpp: Implements the Engine::UI::Arrow class, which draws arrows of the
  fixed size
*/

#include "arrow.hpp"

Engine::UI::Arrow::Arrow(bool left) { this->left = left; }

void Engine::UI::Arrow::show(WINDOW *window, szu x, szu y, szu max_width,
                             szu max_height) {
  start_color(window);
  // first half of the arrow
  for (size_t i = 0; i < width; i++) {
    mvwaddch(window, y + i, x +(left ? width-i-1 : i), left ? L'/' : L'\\');
  }
  for (size_t i = 0; i < width; i++) {
    mvwaddch(window, y + width + i, x + (left ? i :width - i - 1), left ? L'\\' : L'/');
  }
  end_color(window);
}

Engine::UI::Box::dim Engine::UI::Arrow::size(szu max_width, szu max_height) {
  return {width, height};
}
