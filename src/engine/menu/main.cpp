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
using Engine::UI::Box;

Engine::Color foc_color = Engine::Color::grey53,
              unfoc_color = Engine::Color::grey23;

Engine::UI::Logo *append_logo(Box *parent) {
  auto container = Engine::UI::append<Engine::UI::Box>(parent);
  container->props(Box::Property::padding_bottom, 2);

  auto logo = Engine::UI::append<Engine::UI::Logo>(container);
  return logo;
}

Engine::UI::Button *append_button(Box *parent, const wchar_t *str) {
  /* Engine::UI::Center *hcenter =
   * Engine::UI::append<Engine::UI::Center>(parent); */
  /* hcenter->propb(Box::Property::center_horizontal, 1); */
  auto btn =
      Engine::UI::append<Engine::UI::Button, const wchar_t *>(parent, str);
  btn->propc(Box::Property::foreground, Engine::Color::red);
  btn->propc(Box::Property::background, unfoc_color);
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

// TODO: consider adding this to the Menu generalization as it seems pretty
// generic and universal. just leave the focus_start function up to the user.
Box *Engine::Menu::Main::focus_start() { return root->child(0)->child(1); }
Box *Engine::Menu::Main::curr_box() { return focus_start()->child(focused); }
Box *Engine::Menu::Main::next_box() {
  if (focused == max_focused)
    focused = 0;
  return focus_start()->child(focused++);
}
Box *Engine::Menu::Main::prev_box() {
  if (focused == 0)
    focused = max_focused;
  return focus_start()->child(focused--);
}

void Engine::Menu::Main::focus(Box *box) {
  box->propc(Box::Property::background, Color::blue);
}
void Engine::Menu::Main::unfocus(Box *box) {
  box->propc(Box::Property::background, Color::red);
}
