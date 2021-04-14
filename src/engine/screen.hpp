/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  02/21/2021

  screen.hpp: provides the public api for the Engine::Screen class, which
  manages what and how content is displayed on the screen.
*/
#ifndef ENGINE_SCREEN_HPP
#define ENGINE_SCREEN_HPP

#include "../nostd/pair.hpp"
#include "drawable.hpp"
#include <ncurses.h>

namespace Engine {

// Screen wraps the whole ncurses screen in a box of SCREEN_WIDTHxSCREEN_HEIGHT
// that is centered on the screen and repositioned properly on resizes
// Furthermore the screen class keeps track of the terminal dimentions
// to center boxes as we see fit and also calls helper functions like
// `raw`, `keypad` and `noecho` to properly get the user input.
//
// Alongside the ncurses-related drawing duties we also keep track of what
// content is being displayed on the screen and handle certain events for menus
// and a general redraw event for the game content
class Screen {
private:
  // stdscreen refers to the WINDOW* returns by initscr, whereas container is
  // the main ncurses window where all content is drawn. The container borders
  // are marked with ncurses' box function
  //
  // we use a wrapper around container called outer_box to draw the borders of
  // the window but still be able to call werase/wclear on container without
  // removing these borders. It should also prevent some flicekrign when
  // erasing content at a fast rate.
  WINDOW *stdscreen, *outer_box, *container;
  // x, y are the offest from the screen (left, top) to start printing inside
  // the game container
  Drawable::szu x, y, terminal_cols, terminal_lines;
  // checks if the terminal window is big enough to make the content fit
  bool can_fit();

  Drawable *content;
  // removes and frees the content of the window
  void clear_content();

public:
  static const Drawable::szu SCREEN_COLS = 80;
  static const Drawable::szu SCREEN_LINES = 25;

  Screen();
  ~Screen();

  // returns the "state" of the screen, meaning wheter we are displaying the
  // game, a menu or none (therefore we use Drawable::Kind)
  Drawable::Kind get_state();
  // updates the screen with a fresh drawing of a new content
  template <typename T = Drawable> void set_content() {
    clear_content();
    content = new T(container);
    send_event(Engine::Drawable::Event::redraw);
  }
  // updates the screen with a fresh drawing of a new content
  // NOTE: variant with a second arguent
  template <typename T = Drawable, typename E> void set_content(E extra) {
    clear_content();
    content = new T(container, extra);
    send_event(Engine::Drawable::Event::redraw);
  }
  // returns the current drawable being displayed on the screen
  template <typename T = Drawable> T *get_content() {
    return static_cast<T *>(content);
  }
  // returns true if the currently displayed content if of the requested type
  template <typename T = Drawable> bool is_content() {
    return dynamic_cast<T *>(content);
  }
  // returns true if the current content has finished its drawing duties
  bool is_over();
  // sends an event to the current content displayed on the screen which will
  // react accordingly
  void send_event(Drawable::Event e);

  // returns the container ncurses window
  WINDOW *get_container();

  // opens the terminal window and sets up the behaviour defined in the preable
  // of this class
  bool open();
  // repositions the content box on resize events
  bool reposition();
  // closes the current ncurses screen wihtout freeing the content values. it is
  // suggestd to use this ONLY if you know what you're after. In all other
  // cases, _please_ delete the Screen instance.
  void close();
};

} // namespace Engine

#endif // ENGINE_SCREEN_HPP
