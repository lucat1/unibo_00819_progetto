#include "box.hpp"
#include "../../nostd/pair.hpp"
#include <algorithm>
#include <map>
#include <ncurses.h>
#include <unistd.h>
using namespace Nostd;

size_t Engine::UI::Box::ncurses_pair_index = 1;

// Engine::UI::Box has nothing to do with ncurses's box function
// We use Box as a UI primitive to build interfaces. For example each block
// (be it a List, a Button, a Checkbox) extends the box class, which provides
// rendering primitives such as the automatic display of its children in the
// appropriate order
Engine::UI::Box::Box(uint16_t max_width, uint16_t max_height,
                     std::map<enum Engine::UI::Box::Props, uint16_t> props) {
  this->max_width = max_width;
  this->max_height = max_height;

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

  this->max_child_width = max_width - pl - pr;
  this->max_child_height = max_width - pt - pb;
}

// internal usage only!
// used to add a new child to the list of children of this *box
// NOTE(to self): add_child makes the width and height of the child not exceed
// the ones of the parent
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

// Engine::UI::Box is merely a container, therefore we are only interested in
// displaying its children and most importantly how we display then. When
// showing the children we have to take into account three major factors:
// - Engine::UI::Box::Props::DIRECTION which defines the direction in which to
// display the children and therefore also imposes relative limits regarding the
// number of children to be shown. TODO: implement scrollbars (?)
//
// - Engine::UI::Box::Props::FLOAT which defines the direction from which we
// should start displaying the children. Left is the most commonly used value
//
// - Engine::UI::Box::Props::PADDING_* adds paddings on the side of the Box
// around its children
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
    Pair<uint16_t, uint16_t> child_size = it->size();
    it->show(window, x + rel_x + (fr ? -child_size.first : 0), y + rel_y);

    // TODO: fix float right?
    rel_x = rel_x + (dv ? child_size.first : 0);
    if (!dv)
      rel_y += child_size.second;
    it = it->sibling;
  }
}

// TODO: comment
Pair<uint16_t, uint16_t> Engine::UI::Box::size() {
  uint16_t width = 0, height = 0;
  Box *it = first_child;
  while (it != nullptr) {
    // Pair<width, height>
    Pair<uint16_t, uint16_t> child_size = it->size();
    width = fr ? max_width : width + child_size.first;
    height =
        dv ? std::max(height, child_size.second) : height + child_size.second;

    it = it->sibling;
  }

  return Pair<uint16_t, uint16_t>(width + pl + pr, height + pt + pb);
}

Engine::Color Engine::UI::Box::foreground() { return fg; }
Engine::Color Engine::UI::Box::background() { return bg; }
// initializes or returns a memoized value for a ncurses color pair matching the
// foreground and background values of this component
int Engine::UI::Box::color_pair() {
  if (!color)
    return 0;

  if (prev_color_pair != -1)
    return prev_color_pair;

  if (fg == Colorable::foreground() && bg == Colorable::foreground())
    prev_color_pair = 0;
  else if (bg == Colorable::background())
    // if the background is set to transparent we don't need to create a pair
    // and we can just use the color for the foreground
    prev_color_pair = color_to_short(fg);
  else {
    init_pair(ncurses_pair_index++, color_to_short(fg), color_to_short(bg));
    prev_color_pair = COLOR_PAIR(ncurses_pair_index - 1);
  }

  return prev_color_pair;
}
