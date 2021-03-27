#include "main.hpp"
#include "../screen.hpp"
#include "../ui/append.hpp"
#include "../ui/button.hpp"
#include "../ui/center.hpp"

Engine::Menu::Main::Main(WINDOW *window)
    : Drawable(window, Screen::SCREEN_COLS, Screen::SCREEN_LINES) {
  this->drawable_kind = Kind::menu;
  this->root = generate();
}
Engine::Menu::Main::~Main() { delete root; }

Engine::UI::Box *Engine::Menu::Main::generate() {
  UI::Box *root = new UI::Box(width, height);
  UI::Center *hcenter = UI::append<UI::Center>(root);
  hcenter->propb(UI::Box::Property::center_horizontal, 1);
  UI::Center *vcenter = UI::append<UI::Center>(hcenter);

  UI::Button *play_btn =
      UI::append<UI::Button, const wchar_t *>(vcenter, L"play!");
  play_btn->propc(UI::Box::Property::background, Color::grey);

  return root;
}

void Engine::Menu::Main::redraw() {
  UI::Box *tb = root->child(0)->child(0)->child(0);
  Color c = short_to_color(rand() % 256);
  tb->propc(UI::Box::Property::foreground, c);
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
