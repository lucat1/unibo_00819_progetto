/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  03/13/2021

  box.cpp: Implements the Engine::UI::Box class. We mainly take care of childern
  placement, color assignment when drawing and focus on providing a solid base
  upon which other components can be built with the minimal adjustment.
*/

#include "box.hpp"
#include "../../nostd/pair.hpp"
#include "../screen.hpp"
#include <algorithm>
#include <exception>
#include <stdexcept>

// this map for colors _could_ be avoided if we have
// alloc_pair, free_pair, find_pair on macos
// TODO: lower memory usage with an ordered map when available
// (its gonna increase computation time toughfrom O(1) to O(log n)
// but n will be a small number still (in the 10-30s range)
short map[256 + (100 * 256)] = {0};
short i = 1;

// returns a new color_pair based on the fg and bg arguments
// we cache already initializes color pairs.
int Engine::UI::color_pair(short vfg, short vbg) {
  // check if fg == white and bg == transparent and in this case just return as
  // we are not coloring this box.
  if (short_to_color(vfg) == Color::white &&
      short_to_color(vbg) == Color::transparent)
    return -1;

  short bg = std::max((short)0, vbg);
  short fg = std::max((short)0, vfg);
  short hash = fg + (100 * bg);
  if (map[hash] != 0)
    return map[hash];

  int k = i++;
  init_pair(k, fg, bg);
  map[hash] = COLOR_PAIR(k);
  return map[hash];
}

void Engine::UI::start_color(WINDOW *window, int pair) {
  if (pair != -1)
    wattron(window, pair);
}

void Engine::UI::end_color(WINDOW *window, int pair) {
  if (pair != -1)
    wattroff(window, pair);
}

Engine::UI::Box::~Box() {
  Box *it = first_child;
  while (it != nullptr) {
    Box *tmp = it;
    it = it->sibling;
    delete tmp;
  }
}

void Engine::UI::Box::add_child(Box *new_box) {
  if (last_child != nullptr)
    last_child->sibling = new_box;

  new_box->sibling = nullptr;
  new_box->parent = this;
  last_child = new_box;
  if (first_child == nullptr)
    first_child = new_box;
}

int Engine::UI::Box::color_pair() { return UI::color_pair(fg, bg); }

void Engine::UI::Box::start_color(WINDOW *window) {
  UI::start_color(window, color_pair());
}

void Engine::UI::Box::end_color(WINDOW *window) {
  UI::end_color(window, color_pair());
}

Engine::Color Engine::UI::Box::foreground() const { return short_to_color(fg); }
Engine::Color Engine::UI::Box::background() const { return short_to_color(bg); }

void Engine::UI::Box::propc(Box::Property key, Color color) {
  switch (key) {
  case Box::Property::foreground:
    fg = color_to_short(color);
    break;
  case Box::Property::background:
    bg = color_to_short(color);
    break;
  default:
    throw std::invalid_argument(
        "canont assign a color property with a bool/size value");
  }
}

void Engine::UI::Box::propb(Box::Property key, bool value) {
  switch (key) {
  case Box::Property::direction_horizontal:
    dh = value;
    break;
  case Box::Property::float_right:
    fr = value;
    break;
  default:
    throw std::invalid_argument(
        "canont assign a bool property with a size/Color value");
  }
}

void Engine::UI::Box::props(Box::Property key, szu value) {
  switch (key) {
  case Box::Property::padding_left:
    pl = value;
    break;
  case Box::Property::padding_right:
    pr = value;
    break;
  case Box::Property::padding_top:
    pt = value;
    break;
  case Box::Property::padding_bottom:
    pb = value;
    break;
  default:
    throw std::invalid_argument(
        "canont assign a size property with a bool/Color value");
  }
}

Engine::UI::Box *Engine::UI::Box::child(size_t n) {
  Box *it = first_child;
  while (it != nullptr && n--) {
    it = it->sibling;
  }
  return it;
}

void Engine::UI::Box::show(WINDOW *window, szu x, szu y, szu max_width,
                           szu max_height) {
  start_color(window);
  // fill the box's space with the provided background color
  auto sz = size(max_width, max_height);
  for (szu i = 0; i < sz.second; i++)
    mvwhline(window, y + i, x, ' ', sz.first);

  // positioning and with values updated as we loop trough child rendering
  szu rel_x = pl, rel_y = pt, remaining_width = max_width - pl - pr,
      remaining_height = max_height - pt - pb;

  // iterate over all the children and display then in the approrpriate position
  for (Box *it = first_child; it != nullptr; it = it->sibling) {
    auto child_size = it->size(remaining_width, remaining_height);
    if (fr)
      it->show(window, x + max_width - pr - rel_x, y + rel_y, child_size.first,
               child_size.second);
    else
      it->show(window, x + rel_x, y + rel_y, child_size.first,
               child_size.second);

    if (dh) {
      rel_x += child_size.first;
      remaining_width -= child_size.first;
    } else {
      rel_y += child_size.second;
      remaining_height -= child_size.second;
    }
  }
  end_color(window);
  wnoutrefresh(window);
}

Engine::UI::Box::dim Engine::UI::Box::size(szu max_width, szu max_height) {
  szu width = 0, height = 0;
  for (Box *it = first_child; it != nullptr; it = it->sibling) {
    auto child_size = it->size(max_width, max_height);
    width = dh ? width + child_size.first : std::max(width, child_size.first);
    height =
        dh ? std::max(height, child_size.second) : height + child_size.second;
  }
  if (fr)
    width = max_width;

  szu w = width + pl + pr, h = height + pt + pb;
  return {w, h};
}
