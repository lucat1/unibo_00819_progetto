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

Engine::UI::Box *mkbtn(Engine::UI::Box *parent, const wchar_t *str) {
  Engine::UI::Center *hcenter = Engine::UI::append<Engine::UI::Center>(parent);
  hcenter->propb(Engine::UI::Box::Property::center_horizontal, 1);
  hcenter->props(Engine::UI::Box::Property::padding_bottom, 1);
  Engine::UI::Button *btn =
      Engine::UI::append<Engine::UI::Button, const wchar_t *>(hcenter, str);
  btn->propc(Engine::UI::Box::Property::background, Engine::Color::grey23);
  return btn;
}

Engine::UI::Box *Engine::Menu::Main::generate() {
  UI::Box *root = new UI::Box(width, height);
  UI::Center *hcenter = UI::append<UI::Center>(root);
  hcenter->propb(UI::Box::Property::center_horizontal, 1);
  UI::Center *vcenter = UI::append<UI::Center>(hcenter);

  mkbtn(vcenter, L"Start a game");
  mkbtn(vcenter, L"Settings");

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
