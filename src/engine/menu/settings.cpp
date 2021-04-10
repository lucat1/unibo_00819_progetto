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
#include "../ui/button.hpp"
#include "../ui/center.hpp"
#include "../ui/choice.hpp"
#include "../ui/list.hpp"
#include "../ui/text_box.hpp"

using Engine::UI::Box;

void Engine::Menu::Settings::alloc_updated(
    Nostd::Vector<Data::Setting> &settings) {
  for (auto setting : settings)
    updated.push_back(new Data::Setting(setting));
}

Nostd::Vector<Data::Setting> Engine::Menu::Settings::dereference_updated() {
  Nostd::Vector<Data::Setting> res(updated.size());
  for (size_t i = 0; i < updated.size(); i++)
    res[i] = *updated[i];

  return res;
}

Engine::UI::Button *Engine::Menu::Settings::append_button(Box *parent,
                                                          const wchar_t *str) {
  auto btn = parent->append<UI::Button, const wchar_t *>(str);
  unfocus(btn);
  return btn;
}

Box *Engine::Menu::Settings::append_line(Box *parent, Data::Setting *setting) {
  auto wrapper = parent->append<UI::Box>();
  wrapper->props(Box::Property::padding_top, 1);
  auto line = parent->append<UI::Box>();
  line->propb(Box::Property::direction_horizontal, true);
  line->props(Box::Property::padding_left, 2);
  line->props(Box::Property::padding_right, 2);
  line->props(Box::Property::padding_top, 1);
  line->props(Box::Property::padding_bottom, 1);

  line->append<UI::TextBox, const Nostd::WString &>(setting->label());
  auto choice = line->append<UI::Choice, Data::Setting *>(setting);
  choice->propb(Box::Property::float_right, true);
  unfocus(line);
  return wrapper;
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
}

Box *Engine::Menu::Settings::generate() {
  auto root = new UI::Box();
  auto list = root->append<UI::List>();
  list->props(Box::Property::padding_right, 2);
  for (auto setting : updated)
    append_line(list, setting);

  // buttons at the end of the page for closing the menu
  auto chbox = root->append<UI::Center>();
  chbox->propb(Box::Property::center_horizontal, true);
  auto hbox = chbox->append<UI::Box>();
  hbox->propb(Box::Property::direction_horizontal, true);
  hbox->props(Box::Property::padding_top, 8);
  auto btn1 = append_button(hbox, L"Save");
  btn1->props(Box::Property::padding_right, 8);
  append_button(hbox, L"Discard");
  return root;
}

Box *Engine::Menu::Settings::curr_box() {
  if (focused >= max_focused - 1)
    return root->child(1)->child(0)->child(focused == max_focused ? 1 : 0);
  else
    return root->child(0)->child(focused)->child(0);
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

Engine::Color settings_button_fg = Engine::Color::red,
              settings_button_bg = Engine::Color::grey23,
              settings_line = Engine::Color::grey23;

void Engine::Menu::Settings::focus(Box *box) {
  if (dynamic_cast<Engine::UI::Button *>(box)) {
    // visually focus buttons
    box->propc(Box::Property::background, settings_button_fg);
    box->propc(Box::Property::foreground, settings_button_bg);
  } else {
    // visually focus boxes (lines of the list)
    box->propc(Box::Property::background, settings_line);
  }
}

void Engine::Menu::Settings::unfocus(Box *box) {
  if (dynamic_cast<Engine::UI::Button *>(box)) {
    // visually unfocus buttons
    box->propc(Box::Property::background, settings_button_bg);
    box->propc(Box::Property::foreground, settings_button_fg);
  } else {
    // visually unfocus boxes (lines of the list)
    box->propc(Box::Property::background, Color::transparent);
  }
}

void Engine::Menu::Settings::interact(Box *box) { clicked_on = focused; }

bool Engine::Menu::Settings::is_over() { return clicked_on >= max_focused - 1; }

Nostd::Vector<Data::Setting> Engine::Menu::Settings::get_result() {
  // return the initial settings if the discard button has been pressed
  if (clicked_on == max_focused)
    return original;
  else
    return dereference_updated();
}
