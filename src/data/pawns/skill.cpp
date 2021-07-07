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
#include <cstdlib>
#include <istream>

#include "../../nostd/unordered_map.hpp"
#include "projectile.hpp"

using Data::Pawns::Projectile;
using Data::Pawns::Skill;

Skill::Skill(Nostd::UnorderedMap<Nostd::Pair<int, int>, Projectile> projectiles,
             int healthEffect, bool healthMode)
    : p{projectiles}, hE{healthEffect}, hM{healthMode} {
  for (auto pair : projectiles) {
    const int x{pair->first.first}, y{pair->first.second};
    if (!x && !y)
      throw std::invalid_argument("Cannot spawn projectile on user.");
    if (std::abs(x) > 1 || std::abs(y) > 1)
      throw std::invalid_argument("Must spawn projectile in an adjacent cell.");
  }
  if (hE < 0)
    throw std::invalid_argument("Health effect must be non-negative.");
  if (hM && hE > 100)
    throw std::invalid_argument("Health effect cannot be > 100%.");
}

const Nostd::UnorderedMap<Nostd::Pair<int, int>, Projectile> &
Skill::projectiles() const noexcept {
  return p;
}

std::basic_istream<char> &Data::Pawns::operator>>(std::basic_istream<char> &is,
                                                  Skill &s) {
  int n; // number of projectiles
  (is >> n).ignore();
  Nostd::UnorderedMap<Nostd::Pair<int, int>, Projectile> projectiles{};
  for (int i{0}; i < n; ++i) {
    int x, y;
    (is >> x).ignore();
    (is >> y).ignore();
    Projectile p{Engine::Color::transparent, u' ', "", 0, 0, 0, 0};
    (is >> p).ignore();
    projectiles.put({x, y}, p);
  }
  int healthEffect;
  (is >> healthEffect).ignore();
  bool healthMode;
  if (is >> healthMode)
    s = Skill(projectiles, healthEffect, healthMode);
  return is;
}

int Skill::uncheckedHealthEffect(int currentHealth, int maxHealth) {
  return std::min(maxHealth, currentHealth + (hM ? maxHealth * hE / 100 : hE));
}
