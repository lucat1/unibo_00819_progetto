#ifndef ENGINE_UI_BOX_HPP
#define ENGINE_UI_BOX_HPP

#include "../../nostd/pair.hpp"
#include "../../nostd/vector.hpp"
#include "../colorable.hpp"
#include <map>
#include <ncurses.h>
#include <stdint.h>

namespace Engine {
namespace UI {

// Box is a UI primitive extended by all other UI elements
class Box : public Colorable {
protected:
  // padding(left|right|top|bottom)
  uint16_t pl = 0, pr = 0, pt = 0, pb = 0;
  // direction vertical, float right, should we paint custom colors
  bool dh = false, fr = false;

  // color values
  short fg = color_to_short(Colorable::foreground()),
        bg = color_to_short(Colorable::background());
  Nostd::Vector<int> used_color_pairs;
  // returns a ncurses color pair to draw the content in the approriate color
  int color_pair();
  // starts to draw chars in the color described by the Box's properties
  void start_color(WINDOW *window);
  // stops drawing in color
  void end_color(WINDOW *window);

public:
  enum class Property {
    direction_horizontal, // vertical = 0, horizontal = 1
    float_right,          // left = 0, right = 1
    center_horizontal,    // vertical = 0, horizontal = 1

    // paddsings
    padding_left,
    padding_right,
    padding_top,
    padding_bottom,

    foreground,
    background,
  };

  // size values
  uint16_t max_width, max_height, max_child_width, max_child_height;
  // child-parent-sibling relation values;
  Box *first_child = nullptr, *last_child = nullptr, *sibling = nullptr,
      *parent = nullptr;

  Box(uint16_t max_width, uint16_t max_height);
  ~Box();

  Engine::Color foreground() const;
  Engine::Color background() const;
  // sets a color property
  void propc(Box::Property key, Color color);
  // sets a bool property
  void propb(Box::Property key, bool value);
  // sets a size property
  void props(Box::Property key, uint16_t value);
  // returns the n-th child of this node, or null if an invalid index is
  // provided
  Box *child(size_t n);

  // Engine::UI::Box is merely a container, therefore we are only interested in
  // displaying its children and most importantly _how_ we display then. When
  // showing the children we have to take into account three major factors:
  // - Engine::UI::Box::Property::DIRECTION which defines the direction in which
  // to display the children and therefore also imposes relative limits
  // regarding the number of children to be shown.
  //
  // - Engine::UI::Box::Property::FLOAT which defines the direction from which
  // we should start displaying the children. Left is the most commonly used
  // value
  //
  // - Engine::UI::Box::Property::PADDING_* adds paddings on the side of the Box
  // around its children
  virtual void show(WINDOW *window, uint16_t x, uint16_t y);
  // returns the dimentions of the element when drawn
  virtual Nostd::Pair<uint16_t, uint16_t> size();

  // adds a child to the list of children of this node. This method is meant for
  // internal usage only relatively to the Engine::UI library. External usage
  // should be avoided. Please refer to the Engine::UI::append function
  //
  // NOTE: it prevents the width and height of the child from exceeding the ones
  // of the parent
  void add_child(Box *box);
};

} // namespace UI
} // namespace Engine

#endif // ENGINE_UI_BOX_HPP
