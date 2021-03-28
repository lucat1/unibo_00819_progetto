/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  03/20/2021

  drawable.hpp: Defines the Engine::Drawable interface used to describe any
  content which can be drawn on the screen.
*/
#ifndef ENGINE_DRAWABLE_HPP
#define ENGINE_DRAWABLE_HPP

#include <cstdint>
#include <ncurses.h>

namespace Engine {

// Drawable is an interface/abstract class which all drawable entities (namely
// Menus and Game) implement to be rendered by the game's Screen instance. A
// drawable is capable of handling events sent to it which update the state of
// its content and trigger a repaint on the ncurses' screen
class Drawable {
public:
  // two kinds of objects we can draw into the main container
  // - menu: a series of Engine::UI elements used to form a TUI menu to change
  // settings, select maps and difficulty
  // - game: the abstract world provided and modified by other modules drawn to
  // the screen
  enum class Kind { none, menu, game };

  enum class Event {
    // the ubiquitous event used to trigger a re-render on any drawable instance
    redraw,

    // menu events sent from the game module to update the menus
    move_up,
    move_down,
    move_left,
    move_right,
  };

protected:
  // the ncurses screen to draw upon
  WINDOW *window;
  uint16_t width, height;
  Kind drawable_kind = Kind::none;

public:
  virtual Kind kind() const;
  virtual void handle_event(Event e);

  Drawable(WINDOW *window, uint16_t width, uint16_t height);
  virtual ~Drawable() = default;
};

} // namespace Engine

#endif // ENGINE_DRAWABLE_HPP
