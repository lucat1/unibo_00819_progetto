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

Item::Item(Engine::Color foreground, wchar_t character,
           const Nostd::WString &name, int healthBonus, bool healthMode,
           int manaBonus, bool manaMode, int scoreBonus)
    : fg{foreground}, chr{character}, nm{name}, hB{healthBonus}, mB{manaBonus},
      sB{scoreBonus}, hM{healthMode}, mM{manaMode} {
  if (hB < 0)
    throw std::invalid_argument("Health bonus must be non-negative.");
  if (hM && hB > 100)
    throw std::invalid_argument("Health bonus cannot be > 100%.");
  if (mB < 0)
    throw std::invalid_argument("Mana bonus must be non-negative.");
  if (mM && mB > 100)
    throw std::invalid_argument("Mana bonus cannot be > 100%.");
  if (sB < 0)
    throw std::invalid_argument("Score bonus must be non-negative.");
}

Engine::Color Item::foreground() const noexcept { return fg; }

wchar_t Item::character() const noexcept { return chr; }

const Nostd::WString &Item::name() const noexcept { return nm; }

int Item::uncheckedHealthEffect(int currentHealth, int maxHealth) {
  return std::min(maxHealth, currentHealth + (hM ? maxHealth * hB / 100 : hB));
}

int Item::uncheckedManaEffect(int currentMana, int maxMana) {
  return std::min(maxMana, currentMana + (mM ? maxMana * mB / 100 : mB));
}

int Item::uncheckedScoreEffect(int currentScore) { return currentScore + sB; }

std::basic_istream<wchar_t> &
Data::Pawns::operator>>(std::basic_istream<wchar_t> &is, Item &i) {
  short foreground;
  (is >> foreground).ignore();
  wchar_t character;
  (is >> character).ignore();
  Nostd::WString name;
  Data::get_CSV_WString(is, name);
  int healthBonus, manaBonus, scoreBonus;
  (is >> healthBonus).ignore();
  bool healthMode, manaMode;
  (is >> healthMode).ignore();
  (is >> manaBonus).ignore();
  (is >> manaMode).ignore();
  (is >> scoreBonus).ignore();
  if (is >> scoreBonus) {
    i = Item(Engine::short_to_color(foreground), character, name, healthBonus,
             healthMode, manaBonus, manaMode, scoreBonus);
    is.ignore();
  }
  return is;
}
