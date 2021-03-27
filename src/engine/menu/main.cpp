#include "main.hpp"
#include "../screen.hpp"
#include "../ui/append.hpp"
#include "../ui/center.hpp"
#include "../ui/text_box.hpp"

Engine::Menu::Main::Main(WINDOW *window)
    : Drawable(window, Screen::SCREEN_COLS, Screen::SCREEN_LINES) {
  this->drawable_kind = Kind::menu;
  this->root = generate();
}

Engine::UI::Box *Engine::Menu::Main::generate() {
  UI::Box *root = new UI::Box(width, height);
  UI::Center *center = UI::append<UI::Center>(root);
  /* center->prop(UI::Box::Property::center_horizontal, 1); */
  UI::append<UI::TextBox, const wchar_t *>(
      center,
      L"Press any key to change my cloror. q will quit the application");

  return root;
}

void Engine::Menu::Main::redraw() {
  UI::Box *tb = root->child(0)->child(0);
  Color c = short_to_color(rand() % 256);
  tb->prop(UI::Box::Property::foreground, c);
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
