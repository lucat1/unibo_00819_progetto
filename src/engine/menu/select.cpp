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
#include "../ui/button.hpp"
#include "../ui/center.hpp"
#include "../utils.hpp"

/* using Data::Palette::button; */
/* using Data::Palette::primary; */
using Engine::UI::Box;
/* using Engine::Utils::leftpad; */

Engine::Menu::Select::Select(WINDOW *window,
                             const Nostd::Vector<Data::Pawns::Hero> &heroes)
    : Menu(window), heroes{heroes} {
  max_focused = heroes.size() - 1;
}

Box *Engine::Menu::Select::generate() { return nullptr; }

Box *Engine::Menu::Select::curr_box() { return root->child(1)->child(0); }

Box *Engine::Menu::Select::next_box() { return curr_box(); }

Box *Engine::Menu::Select::prev_box() { return curr_box(); }

// we have only one button, we moved the whole focusing mechanic to the generate
// function and leave the tree untouched every update
void Engine::Menu::Select::focus(Box *box) {}
void Engine::Menu::Select::unfocus(Box *box) {}

// at the first interaction we close the menu
void Engine::Menu::Select::interact(Box *box) { clicked_on = focused; }
bool Engine::Menu::Select::is_over() { return clicked_on != 1; }
Data::Pawns::Hero Engine::Menu::Select::get_result() {
  return heroes[clicked_on];
}

// no behaviour defiend for the results menu
void Engine::Menu::Select::decrement(Box *) {}
void Engine::Menu::Select::increment(Box *) {}
