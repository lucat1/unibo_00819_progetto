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
#include "../screen.hpp"
#include "../ui/append.hpp"
#include "../ui/center.hpp"
using Engine::UI::Box;

Box *Engine::Menu::Settings::generate() { return nullptr; }

Box *Engine::Menu::Settings::curr_box() { return nullptr; }

Box *Engine::Menu::Settings::next_box() { return nullptr; }

Box *Engine::Menu::Settings::prev_box() { return nullptr; }

void Engine::Menu::Settings::focus(Box *box) {}

void Engine::Menu::Settings::unfocus(Box *box) {}

bool Engine::Menu::Settings::is_over() { return clicked_on != -1; }
template <typename T> T Engine::Menu::Settings::get_result() { return false; }
template bool Engine::Menu::Settings::get_result<bool>();
