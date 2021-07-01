/*
  University of bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  06/27/2021

  select.cpp: Implements the Engine::Menu::Select menu, used to pick your
  champion for the current game. The menu will display a mugshot and a brief
  description of the selected cmapion, while showing the others to the side.
*/

#include "select.hpp"
#include "../../data/palette.hpp"
#include "../screen.hpp"
#include "../ui/center.hpp"
#include "../ui/strict_box.hpp"
#include "../ui/arrow.hpp"
#include "../ui/mugshot.hpp"
#include "../ui/button.hpp"

using Data::Palette::primary;
using Engine::UI::Box;

Engine::Menu::Select::Select(WINDOW *window,
                             const Nostd::Vector<Data::Pawns::Hero> &heroes)
    : Menu(window), heroes{heroes} {
  max_focused = heroes.size() - 1;
}

  void Engine::Menu::Select::add_arrow(UI::Box *root, bool left) {
  auto right_column = root->append<UI::Center>();
  auto wrapper = right_column->append();
  wrapper->props(Box::Property::padding_left, 1);
  wrapper->props(Box::Property::padding_right, 1);
  wrapper->append<UI::Arrow>(left);
  }

Box *Engine::Menu::Select::generate() {
  auto root = new UI::Box();
  root->propb(Box::Property::direction_horizontal, true);

  // left columnm
  add_arrow(root, true);

  // center column, title and selected champion
  szu max_width = Screen::columns - (UI::Arrow::width + 2) * 2;
  auto center_column = root->append<UI::StrictBox, Box::dim>({max_width, Screen::lines});
  auto title = center_column->append<UI::Center>();
  title->propb(Box::Property::center_horizontal, true);
  title->props(Box::Property::padding_top, 1);
  title->props(Box::Property::padding_bottom, 1);
  title->append<Engine::UI::TextBox, const wchar_t *>(L"Pick your hero:");
  title->propc(Box::Property::foreground, primary);

  auto c1 = center_column->append<UI::Center>();
  auto c2 = c1->append<UI::Center>();
  c2->propb(Box::Property::center_horizontal, true);
  c2->append<Engine::UI::Mugshot, const Data::Mugshot &>(
      heroes[focused].mugshot());

  // right column
  add_arrow(root, false);

  return root;
}

Box *Engine::Menu::Select::curr_box() { return root; }

Box *Engine::Menu::Select::next_box() { return curr_box(); }

Box *Engine::Menu::Select::prev_box() { return curr_box(); }

void Engine::Menu::Select::focus(Box *box) {}
void Engine::Menu::Select::unfocus(Box *box) {}

// at the first interaction we close the menu
void Engine::Menu::Select::interact(Box *box) { clicked_on = focused; }
bool Engine::Menu::Select::is_over() { return clicked_on != -1; }
Data::Pawns::Hero Engine::Menu::Select::get_result() {
  return heroes[clicked_on];
}

// no behaviour defiend for the results menu
void Engine::Menu::Select::decrement(Box *) {}
void Engine::Menu::Select::increment(Box *) {}
