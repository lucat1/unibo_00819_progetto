#include "screen.hpp"
#include "menu/main.hpp"

Engine::Screen::Screen() {
  this->content = nullptr;
  this->stdscreen = nullptr;
  this->container = nullptr;
}
Engine::Screen::~Screen() {
  close();
  // free the currently allocated drawable
  delete content;
}

Engine::Drawable::Kind Engine::Screen::get_state() {
  if (content == nullptr)
    return Engine::Drawable::Kind::none;

  return content->kind();
}
void Engine::Screen::set_content(Engine::Drawable *drawable) {
  if (content != nullptr)
    // free the previous content data
    delete content;

  content = drawable;
  send_event(Engine::Drawable::Event::redraw);
}
Engine::Drawable *Engine::Screen::get_content() { return content; }
void Engine::Screen::send_event(Drawable::Event e) {
  if (content != nullptr)
    content->handle_event(e);
}

WINDOW *Engine::Screen::get_container() { return container; }

bool Engine::Screen::can_fit() {
  getmaxyx(stdscreen, terminal_lines, terminal_cols);

  // check that the terminal is big enough to fit the game
  if (terminal_cols < SCREEN_COLS || terminal_lines < SCREEN_LINES)
    return false;

  x = (terminal_cols - SCREEN_COLS) / 2;
  y = (terminal_lines - SCREEN_LINES) / 2;
  return true;
}

bool Engine::Screen::open() {
  stdscreen = initscr();
  if (stdscreen == nullptr || start_color())
    return false;

  noecho(); // prevents user-inputted charters to be displayed on the stdscreen
  raw();    // intercept all keystrokes and prevent ^C from quitting the game
  curs_set(0); // hide the cursor by default
  keypad(stdscreen,
         false); // keypad(.., false) is used to caputre RESIZE events

  if (container != nullptr)
    delwin(container);

  container = newwin(SCREEN_LINES + 2, SCREEN_COLS + 2, y, x);
  return reposition();
}

bool Engine::Screen::reposition() {
  if (!can_fit())
    return false;

  clear();   // clear the stdscreen and
  refresh(); // send the changes to the user so we can start drawing

  mvwin(container, y, x);
  box(container, ACS_VLINE, ACS_HLINE);
  send_event(Engine::Drawable::Event::redraw);
  wrefresh(container);

  return true;
}

void Engine::Screen::close() {
  delwin(container);
  endwin();
  stdscreen = nullptr;
  container = nullptr;
}
