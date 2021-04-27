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

using Engine::UI::Box;
using Engine::Utils::padstr;

Engine::Menu::Results::Results(WINDOW *window,
                               const Nostd::List<Data::Result> &results)
    : Menu(window), results{results} {}

Box *Engine::Menu::Results::append_line(Box *parent, int rank, int score,
                                        const Nostd::WString &nick) {
  Nostd::WString score_str, rank_str;
  Utils::stringify(rank, rank_str);
  Utils::stringify(score, score_str);
  return append_line(parent, nick, score_str, rank_str);
}

Box::szu menu_padding = 12;
Box::szu rank_size = 4;
Box::szu nick_size = 10;
Box::szu score_size =
    Engine::Screen::columns - (2 * menu_padding) - rank_size - nick_size - 2;
Engine::Utils::Pad pad_dir = Engine::Utils::Pad::left;

Box *Engine::Menu::Results::append_line(Box *parent, const Nostd::WString &rank,
                                        const Nostd::WString &score,
                                        const Nostd::WString &nick) {
  Nostd::WString padded_rank = rank, padded_score = score, padded_nick = nick;
  padstr(pad_dir, rank_size, padded_rank);
  padstr(pad_dir, score_size, padded_score);
  padstr(pad_dir, nick_size, padded_nick);

  auto line = parent->append<UI::Box>();
  line->propb(Box::Property::direction_horizontal, true);
  auto rank_text =
      line->append<UI::TextBox, const Nostd::WString &>(padded_rank);
  rank_text->props(Box::Property::padding_right, 1);
  auto score_text =
      line->append<UI::TextBox, const Nostd::WString &>(padded_score);
  score_text->props(Box::Property::padding_right, 1);
  line->append<UI::TextBox, const Nostd::WString &>(padded_nick);
  return line;
}

// n (number of displayable results) = screen_height - 2 (padding) - 3 (button)
// - 3 for the header) / 3 (height of each result)
Box::szu n_of_results = Engine::Screen::lines - 5;

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
  append_line(list, L"Rank", L"Score", L"Nick");

  // TODO: when we have list iterators
  /* int i = 1; */
  /* for (auto result : results) { */
  /*   append_line(list, result.nick(), result.score(), i % 2); */
  /*   if (i == n_of_results) */
  /*     break; */
  /*   i++; */
  /* } */
  append_line(list, 1, 1083941, L"Luca");

  // buttons at the end of the page for closing the menu
  auto center = root->append<UI::Center>();
  center->propb(Box::Property::center_horizontal, true);
  auto button = center->append<UI::Button, const wchar_t *>(L"Back");
  button->propc(Box::Property::foreground, Data::Palette::button.second);
  button->propc(Box::Property::background, Data::Palette::button.first);
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
