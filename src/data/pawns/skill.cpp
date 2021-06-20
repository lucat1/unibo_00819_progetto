/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/15/2021

  skill.cpp: implementation of Data::Pawns::Skill.
*/

#include "skill.hpp"

#include <algorithm>
#include <istream>

using Data::Pawns::Projectile;
using Data::Pawns::Skill;

Skill::Skill(
    Nostd::UnorderedMap<Nostd::Pair<int, int>, Projectile *> projectiles,
    int healthEffect, bool healthMode)
    : p{projectiles}, hE{healthEffect}, hM{healthMode} {
  if (hE < 0)
    throw std::invalid_argument("Health effect must be non-negative.");
  if (hM && hE > 100)
    throw std::invalid_argument("Health effect cannot be > 100%.");
}

const Nostd::UnorderedMap<Nostd::Pair<int, int>, Projectile *> &
Skill::projectiles() const noexcept {
  return p;
}

std::basic_istream<wchar_t> &
Data::Pawns::operator>>(std::basic_istream<wchar_t> &is, Skill &s) {
  return is; // TODO mockup implementation
}

int Skill::uncheckedHealthEffect(int currentHealth, int maxHealth) {
  return std::min(maxHealth, currentHealth + (hM ? maxHealth * hE / 100 : hE));
}
