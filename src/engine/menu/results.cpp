/*
  University of bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  04/26/2021

  results.cpp: Implements the Engine::Menu::Results menu, hooking into the
  database's data structure to gather informations about the match and various
  heroes.
*/

#include "results.hpp"
#include "../../data/palette.hpp"

using Data::Palette::button;
using Engine::UI::Box;

Engine::Menu::Results::Results(WINDOW *window,
                               const Nostd::Vector<Data::Result> &results)
    : Menu(window) {
  this->results = results;
}

Box *Engine::Menu::Results::generate() {
  auto root = new UI::Box();
  return root;
}

Box *Engine::Menu::Results::curr_box() { return nullptr; }

Box *Engine::Menu::Results::next_box() { return curr_box(); }

Box *Engine::Menu::Results::prev_box() { return curr_box(); }

void Engine::Menu::Results::focus(Box *box) {
  box->propc(Box::Property::background, button.first);
  box->propc(Box::Property::foreground, button.second);
}

void Engine::Menu::Results::unfocus(Box *box) {
  box->propc(Box::Property::background, button.second);
  box->propc(Box::Property::foreground, button.first);
}

void Engine::Menu::Results::interact(Box *box) { clicked_on = focused; }

// no behaviour defiend for the results menu
void Engine::Menu::Results::decrement(Box *) {}
void Engine::Menu::Results::increment(Box *) {}

bool Engine::Menu::Results::is_over() { return clicked_on >= max_focused - 1; }
