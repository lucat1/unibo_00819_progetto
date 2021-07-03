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
#include "../ui/arrow.hpp"
#include "../ui/center.hpp"
#include "../ui/mugshot.hpp"
#include "../ui/strict_box.hpp"
#include "../ui/text_box.hpp"
#include "../utils.hpp"

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
  wrapper->props(left ? Box::Property::padding_left
                      : Box::Property::padding_right,
                 arrow_padding);
  auto arrow = wrapper->append<UI::Arrow>(left);
  if (heroes.size() > 1)
    arrow->propc(Box::Property::foreground, Data::Palette::button.first);
  else
    arrow->propc(Box::Property::foreground, Data::Palette::button.second);
}

void Engine::Menu::Select::append_title(UI::Box *root) {
  auto title = root->append<UI::Center>();
  title->propb(Box::Property::center_horizontal, true);
  auto wrapper = title->append();
  wrapper->props(Box::Property::padding_top, 1);
  wrapper->props(Box::Property::padding_bottom, 2);
  auto title_text =
      wrapper->append<UI::TextBox, const char *>("Pick your hero");
  title_text->propc(Box::Property::foreground, Data::Palette::primary);
}

Box *Engine::Menu::Select::generate() {
  auto root = new UI::Box();
  root->propb(Box::Property::direction_horizontal, true);

  // left columnm
  append_arrow(root, true);

  // center column, title and selected champion
  szu max_width = Screen::columns - (UI::Arrow::width + arrow_padding) * 2;
  auto center_column =
      root->append<UI::StrictBox, Box::dim>({max_width, Screen::lines});
  append_title(center_column);

  auto name_wrapper = center_column->append<UI::Center>();
  name_wrapper->propb(Box::Property::center_horizontal, true);
  name_wrapper->props(Box::Property::padding_bottom, 1);
  auto name = name_wrapper->append<UI::TextBox, const Nostd::String &>(
      heroes[focused].name());
  name->propc(Box::Property::foreground, Data::Palette::secondary);

  auto hero_wrapper = center_column->append<UI::Center>();
  hero_wrapper->propb(Box::Property::center_horizontal, true);
  hero_wrapper->props(Box::Property::padding_top, 1);
  hero_wrapper->append<UI::Mugshot, const Data::Mugshot &>(
      heroes[focused].mugshot());

  auto description_wrapper = center_column->append<UI::Center>();
  description_wrapper->propb(Box::Property::center_horizontal, true);
  description_wrapper->props(Box::Property::padding_bottom, 1);
  auto description_restriction =
      description_wrapper->append<UI::StrictBox, Box::dim>({40, 3});
  description_restriction->append<UI::TextBox, const Nostd::String &>(
      heroes[focused].description());

  auto data_wrapper = center_column->append<UI::Center>();
  data_wrapper->propb(Box::Property::center_horizontal, true);
  auto data_restriction =
      data_wrapper->append<UI::StrictBox, Box::dim>({40, 1});
  data_restriction->propb(Box::Property::direction_horizontal, true);
  Nostd::String health = "health: ", mana = "mana: ";
  Utils::stringify(heroes[focused].maxHealth(), health);
  Utils::stringify(heroes[focused].maxMana(), mana);
  auto health_text =
      data_restriction->append<UI::TextBox, const Nostd::String &>(health);
  health_text->propc(Box::Property::foreground, Data::Palette::health);
  auto mana_text =
      data_restriction->append<UI::TextBox, const Nostd::String &>(mana);
  mana_text->propb(Box::Property::float_right, true);
  mana_text->propc(Box::Property::foreground, Data::Palette::mana);

  // right column
  append_arrow(root, false);

  return root;
}

void Engine::Menu::Select::increment(Box *parent_box) {
  focused = focused == max_focused ? 0 : focused + 1;
  root = generate();
}
void Engine::Menu::Select::decrement(Box *parent_box) {
  focused = focused == 0 ? max_focused : focused - 1;
  root = generate();
}

// noops
void Engine::Menu::Select::focus(Box *box) {}
void Engine::Menu::Select::unfocus(Box *box) {}
Box *Engine::Menu::Select::curr_box() { return root; }
Box *Engine::Menu::Select::next_box() { return root; }
Box *Engine::Menu::Select::prev_box() { return root; }

// at the first interaction we close the menu
void Engine::Menu::Select::interact(Box *box) { clicked_on = focused; }
bool Engine::Menu::Select::is_over() { return clicked_on != -1; }
Data::Pawns::Hero Engine::Menu::Select::get_result() {
  return heroes[clicked_on];
}
