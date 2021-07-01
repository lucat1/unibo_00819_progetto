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

using Engine::UI::Box;

Box::szu arrow_padding = 3;

Engine::Menu::Select::Select(WINDOW *window,
                             const Nostd::Vector<Data::Pawns::Hero> &heroes)
    : Menu(window), heroes{heroes} {
  max_focused = heroes.size() - 1;
}

void Engine::Menu::Select::append_arrow(UI::Box *root, bool left) {
  auto right_column = root->append<UI::Center>();
  auto wrapper = right_column->append();
  wrapper->props(left ? Box::Property::padding_left : Box::Property::padding_right, arrow_padding);
  wrapper->append<UI::Arrow>(left);
  }

void Engine::Menu::Select::append_title(UI::Box *root) {
  auto title = root->append<UI::Center>();
  title->propb(Box::Property::center_horizontal, true);
  auto wrapper = title->append();
  wrapper->props(Box::Property::padding_top, 1);
  wrapper->props(Box::Property::padding_bottom, arrow_padding);
  auto title_text = wrapper->append<UI::TextBox, const wchar_t *>(L"Pick your hero");
  title_text->propc(Box::Property::foreground, Data::Palette::primary);
  }

Box *Engine::Menu::Select::generate() {
  auto root = new UI::Box();
  root->propb(Box::Property::direction_horizontal, true);

  // left columnm
  append_arrow(root, true);

  // center column, title and selected champion
  szu max_width = Screen::columns - (UI::Arrow::width + arrow_padding) * 2;
  auto center_column = root->append<UI::StrictBox, Box::dim>({max_width, Screen::lines});
  append_title(center_column);

  auto center = center_column->append<UI::Center>();
  center->propb(Box::Property::center_horizontal, true);
  auto hero = center->append();

  auto name_wrapper = hero->append();
  name_wrapper->props(Box::Property::padding_bottom, 1);
  auto name = name_wrapper->append<UI::TextBox, const Nostd::WString &>(heroes[focused].name());
  name->propc(Box::Property::foreground, Data::Palette::secondary);

  hero->append<UI::Mugshot, const Data::Mugshot &>(
      heroes[focused].mugshot());

  auto description_wrapper = hero->append();
  description_wrapper->props(Box::Property::padding_top, 1);
  auto description = description_wrapper->append<UI::TextBox, const Nostd::WString &>(heroes[focused].description());
  description->propc(Box::Property::foreground, Data::Palette::button.first);

  // right column
  append_arrow(root, false);

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
