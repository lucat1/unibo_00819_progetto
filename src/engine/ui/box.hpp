/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  03/13/2021

  box.hpp: Defines the Engine::UI::Box class. A Box is the most basic visual
  element. It is a general visual container used to place content without adding
  any visual details. It is also the class all other visual components base
  upon.
*/

#ifndef ENGINE_UI_BOX_HPP
#define ENGINE_UI_BOX_HPP

#include "../../nostd/pair.hpp"
#include "../../nostd/vector.hpp"
#include "../colorable.hpp"
#include <ncurses.h>

namespace Engine {
namespace UI {

// returns a new color_pair based on the fg and bg arguments
// we cache already initializes color pairs.
int color_pair(short fg, short bg);
void start_color(WINDOW *window, int pair);
void end_color(WINDOW *window, int pair);

// Box is a UI primitive extended by all other UI elements
class Box : public Colorable {
public:
  // size unit
  using szu = uint16_t;
  // dimentions
  using dim = Nostd::Pair<szu, szu>;

protected:
  // padding(left|right|top|bottom)
  szu pl = 0, pr = 0, pt = 0, pb = 0;
  // direction vertical, float right, should we paint custom colors
  bool dh = false, fr = false;

  // adds a child to the tail of the list of children
  void add_child(Box *child);

  // color values
  short fg = color_to_short(Colorable::foreground()),
        bg = color_to_short(Colorable::background());
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

  // child-parent-sibling relation values;
  Box *first_child = nullptr, *last_child = nullptr, *sibling = nullptr,
      *parent = nullptr;

  // Engine::UI::Box has nothing to do with ncurses's box function
  // We use Box as a UI primitive to build interfaces. For example each block
  // (be it a List, a Button, a Checkbox) extends the box class, which provides
  // rendering primitives such as the automatic display of its children in the
  // appropriate order
  Box() = default;
  // frees its children list recursively (as deleted children will do the same
  // and so on)
  ~Box();

  Engine::Color foreground() const;
  Engine::Color background() const;
  // sets a color property
  void propc(Box::Property key, Color color);
  // sets a bool property
  void propb(Box::Property key, bool value);
  // sets a size property
  void props(Box::Property key, szu value);
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
  virtual void show(WINDOW *window, szu x, szu y, szu max_width,
                    szu max_height);
  // returns the dimentions of the element when drawn
  virtual dim size(szu max_width, szu max_height);

  // Creates a new %T instance and adds it to the target Box's list of children.
  // The width and height of the new box can be defined relatively to the new
  // parent's dimentions with the w and h parameters
  template <typename T = Box> T *append() {
    T *box = new T();
    add_child(box);
    return box;
  }
  // Creates a new %T instance and adds it to the target Box's list of children.
  // The width and height of the new box can be defined relatively to the new
  // parent's dimentions with the w and h parameters
  template <typename T, typename A>
  T *append(A extra = T::append_default_value) {
    T *box = new T(extra);
    add_child(box);
    return box;
  }
};

} // namespace UI
} // namespace Engine

#endif // ENGINE_UI_BOX_HPP
