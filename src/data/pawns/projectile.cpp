/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/19/2021

  projectile.cpp: implementation of Data::Pawns::Projectile.
*/

#include "projectile.hpp"

#include <algorithm>

#include "../../engine/colorable.hpp"
#include "../database.hpp"

using Data::Pawns::Projectile;

Projectile::Projectile(Engine::Color foreground, wchar_t character,
                       const Nostd::WString &name, int healthDamage,
                       int manaDamage, int scoreDamage, int range)
    : Engine::EntityTile{character, foreground}, Pawn{name, character,
                                                      foreground},
      hD{healthDamage}, mD{manaDamage}, sD{scoreDamage}, rng{range} {
  if (hD < 0)
    throw std::invalid_argument("Health damage must be positive or zero.");
  if (mD < 0)
    throw std::invalid_argument("Mana damage must be positive or zero.");
  if (sD < 0)
    throw std::invalid_argument("Score damage must be positive or zero.");
  if (range < 0)
    throw std::invalid_argument("Range must be positive or zero.");
}

void Projectile::countMovement() {
  if (isExpired())
    throw std::logic_error("This projectile is already expired.");
  --rng;
}

bool Projectile::isExpired() const noexcept { return !rng; }

int Projectile::uncheckedHealthEffect(int currentHealth, int) {
  return std::max(0, currentHealth - hD);
}

int Projectile::uncheckedManaEffect(int currentMana, int) {
  return std::max(0, currentMana - mD);
}

int Projectile::uncheckedScoreEffect(int currentScore) {
  return std::max(0, currentScore - sD);
}

std::basic_istream<wchar_t> &
Data::Pawns::operator>>(std::basic_istream<wchar_t> &is, Projectile &p) {
  short foreground;
  (is >> foreground).ignore();
  wchar_t character;
  (is >> character).ignore();
  Nostd::WString name;
  Data::get_CSV_WString(is, name);
  int healthDamage, manaDamage, scoreDamage, range;
  (is >> healthDamage).ignore();
  (is >> manaDamage).ignore();
  (is >> scoreDamage).ignore();
  if (is >> range)
    p = Projectile(Engine::short_to_color(foreground), character, name,
                   healthDamage, manaDamage, scoreDamage, range);
  return is;
}
