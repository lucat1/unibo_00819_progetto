#ifndef ENGINE_DRAWABLE_HPP
#define ENGINE_DRAWABLE_HPP

#include <ncurses.h>

namespace Engine {

// Drawable is an interface/abstract class which all drawable entities (namely
// Menus and Game) implement to be rendered by the game's Screen instance. A
// drawable is capable of handling events sent to it which update the state of
// its content and trigger a repaint on the ncurses' screen
class Drawable {
protected:
  // the window the drawable can draw into
  WINDOW *window;

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

  virtual Kind kind() const;
  virtual void handle_event(Event e);

  Drawable(WINDOW *window);
  virtual ~Drawable() = default;
};

} // namespace Engine

#endif // ENGINE_DRAWABLE_HPP
