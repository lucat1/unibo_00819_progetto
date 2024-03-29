/*
  University of bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  04/04/2021

  settings.cpp: Implements the Engine::Menu::Settings screen wich contains a
  series of options in a List element drawing sliders/multi options on the
  right of each line
*/

#include "settings.hpp"
#include "../../data/palette.hpp"
#include "../ui/button.hpp"
#include "../ui/center.hpp"
#include "../ui/choice.hpp"
#include "../ui/text_box.hpp"

using Data::Palette::button;
using Data::Palette::slider;
using Data::Palette::unfocused;
using Engine::UI::Box;

using namespace std;

void Engine::Menu::Settings::alloc_updated(
    Nostd::Vector<Data::Setting> &settings) {
  for (auto setting : settings)
    updated.push_back(new Data::Setting(setting));
}

Nostd::Vector<Data::Setting> Engine::Menu::Settings::dereference_updated() {
  Nostd::Vector<Data::Setting> res;
  for (size_t i = 0; i < updated.size(); i++)
    res.push_back(*updated.at(i));

  return res;
}

Engine::UI::Button *Engine::Menu::Settings::append_button(Box *parent,
                                                          const char *str) {
  auto wrapper = parent->append<UI::Center>();
  wrapper->propb(Box::Property::center_horizontal, true);
  auto btn = wrapper->append<UI::Button, const char *>(str);
  unfocus(btn);
  return btn;
}

Box *Engine::Menu::Settings::append_line(Box *parent, Data::Setting *setting) {
  auto line = parent->append<UI::Box>();
  line->propb(Box::Property::direction_horizontal, true);
  line->props(Box::Property::padding_left, 2);
  line->props(Box::Property::padding_right, 2);
  line->props(Box::Property::padding_top, 1);
  line->props(Box::Property::padding_bottom, 1);
  line->append<UI::TextBox, const Nostd::String &>(setting->label());
  auto choice = line->append<UI::Choice, Data::Setting *>(setting);
  choice->propb(Box::Property::float_right, true);
  choice->propc(Box::Property::foreground, slider.first);
  choice->propc(Box::Property::background, slider.second);

  unfocus(line);
  return line;
}

Engine::Menu::Settings::Settings(WINDOW *window,
                                 const Nostd::Vector<Data::Setting> &settings)
    : Menu(window) {
  original = settings;
  alloc_updated(original);

  max_focused =
      settings.size() + 1; // n of settings + 1 for the save and discard button
}

Engine::Menu::Settings::~Settings() {
  for (auto setting : updated)
    delete setting;
  updated.clear();
  original.clear();
}

Box *Engine::Menu::Settings::generate() {
  auto root = new UI::Box();
  auto list = root->append<UI::Box>();
  list->props(Box::Property::padding_left, 2);
  list->props(Box::Property::padding_right, 2);
  list->props(Box::Property::padding_top, 1);
  list->props(Box::Property::padding_bottom, 1);
  for (auto setting : updated)
    append_line(list, setting);

  // buttons at the end of the page for closing the menu
  auto chbox = root->append<UI::Center>();
  chbox->propb(Box::Property::center_horizontal, true);
  auto btn_parent = chbox->append<UI::Box>();
  auto btn1 = append_button(btn_parent, "Save");
  btn1->props(Box::Property::padding_bottom, 1);
  append_button(btn_parent, "Cancel");
  return root;
}

Box *Engine::Menu::Settings::curr_box() {
  if (focused >= max_focused - 1)
    return root->child(1)
        ->child(0)
        ->child(focused == max_focused ? 1 : 0)
        ->child(0);
  else
    return root->child(0)->child(focused);
}

Box *Engine::Menu::Settings::next_box() {
  // if we are at the last element go to the top, otherwhise increment
  focused = focused == max_focused ? 0 : focused + 1;
  return curr_box();
}

Box *Engine::Menu::Settings::prev_box() {
  // if we are at the first element go to the bottom, otherwhise decrement
  focused = focused == 0 ? max_focused : focused - 1;
  return curr_box();
}

void Engine::Menu::Settings::focus(Box *box) {
  if (dynamic_cast<Engine::UI::Button *>(box)) {
    // visually focus buttons
    box->propc(Box::Property::background, button.first);
    box->propc(Box::Property::foreground, button.second);
  } else {
    // visually focus boxes (lines of the list)
    box->propc(Box::Property::background, unfocused);
  }
}

void Engine::Menu::Settings::unfocus(Box *box) {
  if (dynamic_cast<Engine::UI::Button *>(box)) {
    // visually unfocus buttons
    box->propc(Box::Property::background, button.second);
    box->propc(Box::Property::foreground, button.first);
  } else {
    // visually unfocus boxes (lines of the list)
    box->propc(Box::Property::background, Color::transparent);
  }
}

void Engine::Menu::Settings::interact(Box *box) { clicked_on = focused; }

void Engine::Menu::Settings::decrement(Box *parent_box) {
  Box *box = parent_box->child(1);
  if (!dynamic_cast<Engine::UI::Choice *>(box))
    return;

  auto choice = static_cast<Engine::UI::Choice *>(box);
  Data::Setting *setting = choice->get_setting();
  if (*setting->current_value() != setting->first())
    setting->set(--setting->current_value());
}

void Engine::Menu::Settings::increment(Box *parent_box) {
  Box *box = parent_box->child(1);
  if (!dynamic_cast<Engine::UI::Choice *>(box))
    return;

  auto choice = static_cast<Engine::UI::Choice *>(box);
  Data::Setting *setting = choice->get_setting();
  if (*setting->current_value() != setting->last())
    setting->set(++setting->current_value());
}

bool Engine::Menu::Settings::is_over() { return clicked_on >= max_focused - 1; }

Nostd::Vector<Data::Setting> Engine::Menu::Settings::get_result() {
  // return the initial settings if the discard button has been pressed
  if (clicked_on == max_focused)
    return original;
  else
    return dereference_updated();
}
