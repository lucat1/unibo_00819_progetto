#include "main.hpp"
#include "../screen.hpp"
#include "../ui/append.hpp"
#include "../ui/text_box.hpp"

#include <iostream>
using namespace std;

Engine::Menu::Main::Main(WINDOW *window)
    : Drawable(window, Screen::SCREEN_COLS, Screen ::SCREEN_LINES) {
  this->drawable_kind = Kind::menu;
  this->root = generate();
}

Engine::UI::Box *Engine::Menu::Main::generate() {
  UI::Box *root = new UI::Box(width, height);
  UI::append<UI::TextBox, const wchar_t *>(root, 1, 1, {}, L"Main Menu");

  return root;
}

void Engine::Menu::Main::redraw() {
  root->show(window, 1, 1);
  wrefresh(window);
}

void Engine::Menu::Main::handle_event(Event e) {
  switch (e) {
  case Event::redraw:
    redraw();
    break;
  case Event::move_up:
  case Event::move_down:
  case Event::move_left:
  case Event::move_right:
    break;
  };
}
