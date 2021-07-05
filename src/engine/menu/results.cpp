/*
  University of bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  04/26/2021

  results.cpp: Implements the Engine::Menu::Results menu, hooking into the
  database's data structure to gather informations about the match and various
  heroes. Precondition: the input list containing the results is already sorted.

  Inspiration for the menu:
  https://www.gamesdatabase.org/Media/SYSTEM/Arcade/Score/big/Special_Criminal_Investigation_-_1989_-_Taito.jpg
*/

#include "results.hpp"
#include "../../data/palette.hpp"
#include "../screen.hpp"
#include "../ui/button.hpp"
#include "../ui/center.hpp"
#include "../utils.hpp"

using Data::Palette::button;
using Data::Palette::primary;
using Engine::UI::Box;
using Engine::Utils::leftpad;

Engine::Menu::Results::Results(WINDOW *window,
                               const Nostd::List<Data::Pawns::Result> &results)
    : Menu(window), results{results} {}

Box *Engine::Menu::Results::append_line(Box *parent, int rank, int score,
                                        const Nostd::String &nick) {
  Nostd::String score_str, rank_str;
  Utils::stringify(rank, rank_str);
  Utils::stringify(score, score_str);
  return append_line(parent, score_str, rank_str, nick);
}

Box::szu menu_padding = 12;
Box::szu rank_size = 4;
Box::szu nick_size = 14;
Box::szu score_size =
    Engine::Screen::columns - (2 * menu_padding) - rank_size - nick_size - 2;

Box *Engine::Menu::Results::append_line(Box *parent, const Nostd::String &rank,
                                        const Nostd::String &score,
                                        const Nostd::String &nick,
                                        bool color) {
  Nostd::String padded_rank = rank, padded_score = score, padded_nick = nick;
  leftpad(rank_size, padded_rank);
  padded_rank.append(" ");
  leftpad(score_size, padded_score);
  padded_score.append(" ");
  leftpad(nick_size, padded_nick);

  auto line = parent->append<UI::Box>();
  line->propb(Box::Property::direction_horizontal, true);
  auto r = line->append<UI::TextBox, const Nostd::String &>(padded_rank);
  auto s = line->append<UI::TextBox, const Nostd::String &>(padded_score);
  auto n = line->append<UI::TextBox, const Nostd::String &>(padded_nick);
  if (color) {
    r->propc(Box::Property::foreground, primary);
    s->propc(Box::Property::foreground, primary);
    n->propc(Box::Property::foreground, primary);
  }
  return line;
}

// n (number of displayable results) = screen_height - 2 for window padding - 2
// for button padding - 3 for button's height - 1 for table header
Box::szu n_of_results = Engine::Screen::lines - 8;

// highly similar to the settings menu page with a
// vertical list and a closing button
Box *Engine::Menu::Results::generate() {
  auto root = new UI::Box();
  auto list = root->append<UI::Box>();
  list->props(Box::Property::padding_left, menu_padding);
  list->props(Box::Property::padding_right, menu_padding);
  list->props(Box::Property::padding_top, 1);
  list->props(Box::Property::padding_bottom, 1);

  // append a fake table header as another line
  append_line(list, "Rank", "Score", "Nick", true);

  Box::szu i = 1;
  for (auto result : results) {
    append_line(list, result.score(), i, result.name());
    if (i == n_of_results)
      break;
    i++;
  }

  // buttons at the end of the page for closing the menu
  auto center = root->append<UI::Center>();
  center->propb(Box::Property::center_horizontal, true);
  auto btn = center->append<UI::Button, const char *>("Back");
  btn->props(Box::Property::padding_top, 1);
  btn->props(Box::Property::padding_bottom, 1);
  btn->propc(Box::Property::foreground, button.second);
  btn->propc(Box::Property::background, button.first);
  return root;
}

Box *Engine::Menu::Results::curr_box() { return root->child(1)->child(0); }

Box *Engine::Menu::Results::next_box() { return curr_box(); }

Box *Engine::Menu::Results::prev_box() { return curr_box(); }

// we have only one button, we moved the whole focusing mechanic to the generate
// function and leave the tree untouched every update
void Engine::Menu::Results::focus(Box *box) {}
void Engine::Menu::Results::unfocus(Box *box) {}

// at the first interaction we close the menu
void Engine::Menu::Results::interact(Box *box) { has_interacted = true; }
bool Engine::Menu::Results::is_over() { return has_interacted; }

// no behaviour defiend for the results menu
void Engine::Menu::Results::decrement(Box *) {}
void Engine::Menu::Results::increment(Box *) {}
