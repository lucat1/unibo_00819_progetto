/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  07/01/2021

  mugshot.cpp: Implements the Engine::UI::Mugshot class to draw a matrix of
  tiles
*/

#include "mugshot.hpp"

Engine::UI::Mugshot::Mugshot(const Data::Mugshot &mugshot) : mugshot{mugshot} {}

void Engine::UI::Mugshot::propc(Box::Property key, Color color) {}

// show the mugshot at the given position while cropping it to fit the max_width
// and max_height parameters
void Engine::UI::Mugshot::show(WINDOW *window, szu x, szu y, szu max_width,
                               szu max_height) {
  szu x_inc = 0, y_inc = 0;
  for (auto &row : mugshot) {
    if (y_inc > max_height)
      break;

    for (auto &cell : row) {
      if (x_inc > max_width)
        break;

      short pixel_color = color_to_short(cell.value());
      int color = Engine::UI::color_pair(pixel_color, pixel_color);
      Engine::UI::start_color(window, color);
      mvwaddch(window, y + y_inc, x + x_inc, u' ');
      Engine::UI::end_color(window, color);
      x_inc++;
    }
    x_inc = 0;
    y_inc++;
  }
}

Engine::UI::Box::dim Engine::UI::Mugshot::size(szu max_width, szu max_height) {
  return {(szu)mugshot.width, (szu)mugshot.height};
}
