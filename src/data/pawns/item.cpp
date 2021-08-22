/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/17/2021

  item.cpp: implementation of Data::Pawns::Item.
*/

#include "item.hpp"

#include <algorithm>

#include "../database.hpp"

using Data::Pawns::Item;

Item::Item(Engine::Color foreground, char character, const Nostd::String &name,
           int health_bonus, bool health_mode, int mana_bonus, bool mana_mode,
           int score_bonus)
    : Engine::EntityTile{character, foreground},
      Pawn{name, character, foreground}, hb{health_bonus}, mb{mana_bonus},
      sb{score_bonus}, hm{health_mode}, mm{mana_mode} {
  if (hb < 0)
    throw std::invalid_argument("Health bonus must be non-negative.");
  if (hm && hb > 100)
    throw std::invalid_argument("Health bonus cannot be > 100%.");
  if (mb < 0)
    throw std::invalid_argument("Mana bonus must be non-negative.");
  if (mm && mb > 100)
    throw std::invalid_argument("Mana bonus cannot be > 100%.");
  if (sb < 0)
    throw std::invalid_argument("Score bonus must be non-negative.");
}

int Item::unchecked_health_effect(int current_health, int max_health) const {
  return std::min(max_health,
                  current_health + (hm ? max_health * hb / 100 : hb));
}

int Item::unchecked_mana_effect(int current_mana, int max_mana) const {
  return std::min(max_mana, current_mana + (mm ? max_mana * mb / 100 : mb));
}

int Item::unchecked_score_effect(int current_score) const {
  return current_score + sb;
}

std::basic_istream<char> &Data::Pawns::operator>>(std::basic_istream<char> &is,
                                                  Item &i) {
  short foreground;
  (is >> foreground).ignore();
  char character;
  (is >> character).ignore();
  Nostd::String name;
  Data::get_CSV_String(is, name);
  int health_bonus, mana_bonus, score_bonus;
  (is >> health_bonus).ignore();
  bool health_mode, mana_mode;
  (is >> health_mode).ignore();
  (is >> mana_bonus).ignore();
  (is >> mana_mode).ignore();
  if (is >> score_bonus) {
    i = Item(Engine::short_to_color(foreground), character, name, health_bonus,
             health_mode, mana_bonus, mana_mode, score_bonus);
    is.ignore();
  }
  return is;
}
