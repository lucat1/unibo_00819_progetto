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
#include "../ui/center.hpp"
using Engine::UI::Box;

Engine::UI::Logo *Engine::Menu::Main::append_logo(Box *parent) {
  auto container = Engine::UI::append<Engine::UI::Box>(parent);
  container->props(Box::Property::padding_bottom, 2);

  auto logo = Engine::UI::append<Engine::UI::Logo>(container);
  return logo;
}

Engine::UI::Button *Engine::Menu::Main::append_button(Box *parent,
                                                      const wchar_t *str) {
  auto btn =
      Engine::UI::append<Engine::UI::Button, const wchar_t *>(parent, str);
  unfocus(btn);
  return btn;
}

Box *Engine::Menu::Main::generate() {
  auto root = new UI::Center(width, height);
  auto center = UI::append<UI::Center>(root);
  center->propb(Box::Property::center_horizontal, 1);

  append_logo(center);

  auto btn_container = UI::append<UI::Center>(center);
  btn_container->propb(Box::Property::center_horizontal, 1);
  auto play = append_button(btn_container, L"Play");
  play->props(Box::Property::padding_bottom, 1);
  append_button(btn_container, L"Settings");

  return root;
}

// These are common across al menus, but a shared abstraction has been avoided
// to allow more complex menus to be created. This naive appreach with simple
// `child` calls and a counter would not work in a more complex element tree
// where the fous items are scattered around and not all contained neatly under
// the same parent.
Box *Engine::Menu::Main::focus_start() { return root->child(0)->child(1); }

Box *Engine::Menu::Main::curr_box() { return focus_start()->child(focused); }

Box *Engine::Menu::Main::next_box() {
  // if we are at the last element go to the top, otherwhise increment
  focused = focused == max_focused ? 0 : focused + 1;
  return curr_box();
}

Box *Engine::Menu::Main::prev_box() {
  // if we are at the first element go to the bottom, otherwhise decrement
  focused = focused == 0 ? max_focused : focused - 1;
  return curr_box();
}

Engine::Color fg = Engine::Color::red, bg = Engine::Color::grey23;

void Engine::Menu::Main::focus(Box *box) {
  box->propc(Box::Property::background, fg);
  box->propc(Box::Property::foreground, bg);
}

void Engine::Menu::Main::unfocus(Box *box) {
  box->propc(Box::Property::background, bg);
  box->propc(Box::Property::foreground, fg);
}
