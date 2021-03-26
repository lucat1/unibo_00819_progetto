#include "box.hpp"
#include "../../nostd/pair.hpp"
#include <algorithm>
#include <exception>

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
  // if we already have allocated a pair then we can just return it
  if ((pair = find_pair(fg, bg)) != -1)
    return pair;

  // oterwhise we allocate a new pair and add it to the vector of pairs for this
  // Box so later on when the box will be delted we'll also be albe to free any
  // excess color pairs
  pair = alloc_pair(fg, bg == -1 ? color_to_short(Color::black) : bg);
  if (pair == -1)
    // we got an allocation error, throw an exception
    throw std::bad_alloc();

  used_color_pairs.push_back(pair);
  return pair;
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
  this->max_child_height = max_width - pt - pb;
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

void Engine::UI::Box::update(std::map<enum Box::Props, uint16_t> props) {
  std::map<enum Engine::UI::Box::Props, uint16_t>::iterator it;
  for (it = props.begin(); it != props.end(); it++) {
    switch (it->first) {
    case DIRECTION:
      dv = it->second > 0 ? true : false;
      break;
    case FLOAT:
      fr = it->second > 0 ? true : false;
      break;

    case PADDING_LEFT:
      pl = it->second;
      break;
    case PADDING_RIGHT:
      pr = it->second;
      break;
    case PADDING_TOP:
      pt = it->second;
      break;
    case PADDING_BOTTOM:
      pb = it->second;
      break;

    case FOREGROUND:
      color = true;
      fg = short_to_color(it->second);
      break;
    case BACKGROUND:
      color = true;
      bg = short_to_color(it->second);
      break;
    }
  }
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

Engine::UI::Box *Engine::UI::Box::child(size_t n) {
  Box *it = first_child;
  while (it != nullptr && n--) {
    it = it->sibling;
  }
  return it;
}

void Engine::UI::Box::show(WINDOW *window, uint16_t x, uint16_t y) {
  // values are given a defualt value supposing we are positioning items
  // horizontally (dv = 0) on the left (fr = 0)
  uint16_t rel_x = pl, rel_y = pt;
  if (fr)
    rel_x = max_child_width - pr;

  // iterate over all the children and display then in the approrpriate position
  Box *it = first_child;
  while (it != nullptr && rel_x < max_child_width && rel_y < max_child_height) {
    // Pair<width, height>
    auto child_size = it->size();
    it->show(window, x + rel_x + (fr ? -child_size.first : 0), y + rel_y);

    // TODO: fix float right?
    rel_x = rel_x + (dv ? child_size.first : 0);
    if (!dv)
      rel_y += child_size.second;
    it = it->sibling;
  }
}

Nostd::Pair<uint16_t, uint16_t> Engine::UI::Box::size() {
  uint16_t width = 0, height = 0;
  for (Box *it = first_child; it != nullptr; it = it->sibling) {
    // Pair<width, height>
    auto child_size = it->size();
    width = fr ? max_width : width + child_size.first;
    height =
        dv ? std::max(height, child_size.second) : height + child_size.second;
  }

  uint16_t w = width + pl + pr, h = height + pt + pb;
  return {w, h};
}

Engine::Color Engine::UI::Box::foreground() { return fg; }
Engine::Color Engine::UI::Box::background() { return bg; }
