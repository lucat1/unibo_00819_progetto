/*
  University of bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  03/22/2021

  main.cpp: Implements the Engine::Menu::Main main screen by using all
  previously built visual elements and handling cursor movement, focus and
  interaction with the UI.
*/
#include "main.hpp"
#include "../screen.hpp"
#include "../ui/append.hpp"
#include "../ui/button.hpp"
#include "../ui/center.hpp"
#include "../ui/logo.hpp"

Engine::Menu::Main::Main(WINDOW *window)
    : Drawable(window, Screen::SCREEN_COLS, Screen::SCREEN_LINES) {
  this->drawable_kind = Kind::menu;
  this->root = generate();
}
Engine::Menu::Main::~Main() { delete root; }

Engine::UI::Logo *append_logo(Engine::UI::Box *parent) {
  Engine::UI::Center *hcenter = Engine::UI::append<Engine::UI::Center>(parent);
  hcenter->propb(Engine::UI::Box::Property::center_horizontal, 1);
  hcenter->props(Engine::UI::Box::Property::padding_bottom, 2);
  auto logo = Engine::UI::append<Engine::UI::Logo>(hcenter);
  return logo;
}

Engine::UI::Button *append_button(Engine::UI::Box *parent, const wchar_t *str) {
  Engine::UI::Center *hcenter = Engine::UI::append<Engine::UI::Center>(parent);
  hcenter->propb(Engine::UI::Box::Property::center_horizontal, 1);
  hcenter->props(Engine::UI::Box::Property::padding_bottom, 1);
  auto btn =
      Engine::UI::append<Engine::UI::Button, const wchar_t *>(hcenter, str);
  btn->propc(Engine::UI::Box::Property::foreground, Engine::Color::red);
  btn->propc(Engine::UI::Box::Property::background, Engine::Color::grey23);
  return btn;
}

Engine::UI::Box *Engine::Menu::Main::generate() {
  auto root = new UI::Box(width, height);
  auto hcenter = UI::append<UI::Center>(root);
  hcenter->propb(UI::Box::Property::center_horizontal, 1);
  auto vcenter = UI::append<UI::Center>(hcenter);

  append_logo(vcenter);
  append_button(vcenter, L"Play a match");
  append_button(vcenter, L"Settings");

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
