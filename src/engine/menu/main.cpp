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
#include "../ui/center.hpp"

using Engine::UI::Box;

Engine::UI::Logo *Engine::Menu::Main::append_logo(Box *parent) {
  auto container = parent->append<UI::Center>();
  container->props(Box::Property::padding_bottom, 2);

  auto logo = container->append<UI::Logo>();
  return logo;
}

Engine::UI::Button *Engine::Menu::Main::append_button(Box *parent,
                                                      const wchar_t *str) {
  auto btn = parent->append<UI::Button, const wchar_t *>(str);
  unfocus(btn);
  return btn;
}

Box *Engine::Menu::Main::generate() {
  auto root = new UI::Center();
  auto center = root->append<UI::Center>();
  center->propb(Box::Property::center_horizontal, true);
  append_logo(center);

  auto btn_container = center->append<UI::Center>();
  btn_container->propb(Box::Property::center_horizontal, true);
  auto play = append_button(btn_container, L"Play");
  play->props(Box::Property::padding_bottom, 1);
  auto settings = append_button(btn_container, L"Settings");
  settings->props(Box::Property::padding_bottom, 1);
  append_button(btn_container, L"Quit");

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

Engine::Color main_button_fg = Engine::Color::red,
              main_button_bg = Engine::Color::grey23;

void Engine::Menu::Main::focus(Box *box) {
  box->propc(Box::Property::background, main_button_fg);
  box->propc(Box::Property::foreground, main_button_bg);
}

void Engine::Menu::Main::unfocus(Box *box) {
  box->propc(Box::Property::background, main_button_bg);
  box->propc(Box::Property::foreground, main_button_fg);
}

void Engine::Menu::Main::interact(Box *) { clicked_on = focused; }

bool Engine::Menu::Main::is_over() { return clicked_on != -1; }

Engine::Menu::Main::Result Engine::Menu::Main::get_result() {
  Result actions[] = {Result::play, Result::settings, Result::quit};
  return actions[clicked_on];
}
