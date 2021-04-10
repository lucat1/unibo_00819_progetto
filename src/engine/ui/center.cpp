/*
  University of bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  03/21/2021

  center.cpp: Implements the Engine::UI::Center class with its centering
  computations.
*/

#include "center.hpp"
#include <algorithm>

void Engine::UI::Center::propb(Box::Property key, bool value) {
  switch (key) {
  case Box::Property::center_horizontal:
    center_horizontally = value;
    dh = value;
    break;
  default:
    Box::propb(key, value);
  }
}

void Engine::UI::Center::show(WINDOW *window, szu x, szu y, szu max_width,
                              szu max_height) {
  start_color(window);
  // fill the box's space with the provided background color
  auto sz = size(max_width, max_height);
  for (szu i = 0; i < sz.second; i++)
    mvwhline(window, y + i, x, ' ', sz.first);

  szu rel_y =
          center_horizontally
              ? 0
              : std::max(
                    (max_height - Box::size(max_width, max_height).second) / 2,
                    0),
      rel_x =
          center_horizontally
              ? std::max(
                    (max_width - Box::size(max_width, max_height).first) / 2, 0)
              : 0,
      remaining_width = max_width, remaining_height = max_height;

  for (Box *it = first_child; it != nullptr; it = it->sibling) {
    auto size = it->size(remaining_width, remaining_width);
    it->show(window, x + rel_x, y + rel_y, size.first, size.second);

    if (center_horizontally) {
      rel_x += size.first;
      remaining_width -= size.first;
    } else {
      rel_y += size.second;
      remaining_height -= size.second;
    }
  }

  end_color(window);
  wnoutrefresh(window);
}

Engine::UI::Box::dim Engine::UI::Center::size(szu max_width, szu max_height) {
  auto size = Box::size(max_width, max_height);
  szu width = size.first, height = size.second;
  if (center_horizontally)
    width = max_width;
  else
    height = max_height;

  return {width, height};
}
