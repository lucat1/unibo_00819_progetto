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
#include <algorithm>
#include <exception>
#include <stdexcept>

// the documentation on `man new_pair` was extremely useful in understanding
// ncurses' color and color_pair system. I suggest a read to understand what and
// why we did things the way they are. Here's a copy of the man page:
// https://man7.org/linux/man-pages/man3/new_pair.3x.html
int Engine::UI::Box::color_pair() {
  // check if fg == white and bg == transparent and in this case just return as
  // we are not coloring this box. Colors taken from Engine::Color enum and
  // Engine::Colorable default values and hardcoded for performance
  if (fg == 15 && bg == -1)
    return -1;

  int pair;
  short bg = this->bg < 0 ? 0 : this->bg;
  // if we already have allocated a pair then we can just return it
  if ((pair = find_pair(fg, bg)) != -1)
    return pair;

  // oterwhise we allocate a new pair and add it to the vector of pairs for this
  // Box so later on when the box will be delted we'll also be albe to free any
  // excess color pairs
  pair = alloc_pair(fg, bg);
  if (pair == -1)
    // we got an allocation error, throw an exception
    throw std::bad_alloc();

  used_color_pairs.push_back(pair);
  return COLOR_PAIR(pair);
}

void Engine::UI::Box::start_color(WINDOW *window) {
  int pair = color_pair();
  if (pair != -1)
    wattron(window, pair);
}

void Engine::UI::Box::end_color(WINDOW *window) {
  int pair = color_pair();
  if (pair != -1)
    wattroff(window, pair);
}

// Engine::UI::Box has nothing to do with ncurses's box function
// We use Box as a UI primitive to build interfaces. For example each block
// (be it a List, a Button, a Checkbox) extends the box class, which provides
// rendering primitives such as the automatic display of its children in the
// appropriate order
Engine::UI::Box::Box(uint16_t max_width, uint16_t max_height) {
  this->max_width = max_width;
  this->max_height = max_height;
  this->max_child_width = max_width - pl - pr;
  this->max_child_height = max_height - pt - pb;
}

// frees all instances created by the Box class.
// namely: all color pairs,
Engine::UI::Box::~Box() {
  for (size_t i = 0; i < used_color_pairs.size(); i++) {
    free_pair(used_color_pairs[i]);
  }
  Box *it = first_child;
  while (it != nullptr) {
    Box *tmp = it;
    it = it->sibling;
    delete tmp;
  }
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

void Engine::UI::Box::props(Box::Property key, uint16_t value) {
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

void Engine::UI::Box::show(WINDOW *window, uint16_t x, uint16_t y) {
  start_color(window);
  // values are given a defualt value supposing we are positioning items
  // horizontally (dh = 0) on the left (fr = 0)
  uint16_t rel_x = pl, rel_y = pt;
  if (fr)
    rel_x = max_child_width - pr;

  // iterate over all the children and display then in the approrpriate position
  Box *it = first_child;
  while (it != nullptr && rel_x < max_child_width && rel_y < max_child_height) {
    auto child_size = it->size();
    it->show(window, x + rel_x - (fr ? child_size.first : 0), y + rel_y);

    rel_x = rel_x + (dh ? child_size.first : 0);
    if (!dh)
      rel_y += child_size.second;
    it = it->sibling;
  }
  end_color(window);
}

Nostd::Pair<uint16_t, uint16_t> Engine::UI::Box::size() {
  uint16_t width = 0, height = 0;
  for (Box *it = first_child; it != nullptr; it = it->sibling) {
    auto child_size = it->size();
    width = fr ? max_width : width + child_size.first;
    height =
        dh ? std::max(height, child_size.second) : height + child_size.second;
  }

  uint16_t w = width + pl + pr, h = height + pt + pb;
  return {w, h};
}

void Engine::UI::Box::add_child(Box *new_box) {
  new_box->max_width = std::min(new_box->max_width, max_child_width);
  new_box->max_height = std::min(new_box->max_height, max_child_height);
  if (last_child != nullptr)
    last_child->sibling = new_box;

  new_box->sibling = nullptr;
  new_box->parent = this;
  last_child = new_box;
  if (first_child == nullptr)
    first_child = new_box;
}
