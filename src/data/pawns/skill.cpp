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
#include "../database.hpp"
#include "projectile.hpp"

using Data::Pawns::Projectile;
using Data::Pawns::Skill;

Skill::Skill(const Nostd::String &name,
             Nostd::UnorderedMap<Nostd::Pair<int, int>, Projectile> projectiles,
             int healthEffect, bool healthMode)
    : Pawn{name}, p{projectiles}, he{healthEffect}, hm{healthMode} {
  for (auto pair : projectiles) {
    const int x{pair->first.first}, y{pair->first.second};
    if (!x && !y)
      throw std::invalid_argument("Cannot spawn projectile on user.");
    if (std::abs(x) > 1 || std::abs(y) > 1)
      throw std::invalid_argument("Must spawn projectile in an adjacent cell.");
  }
  if (he < 0)
    throw std::invalid_argument("Health effect must be non-negative.");
  if (hm && he > 100)
    throw std::invalid_argument("Health effect cannot be > 100%.");
}

const Nostd::UnorderedMap<Nostd::Pair<int, int>, Projectile> &
Skill::projectiles() const noexcept {
  return p;
}

std::basic_istream<char> &Data::Pawns::operator>>(std::basic_istream<char> &is,
                                                  Skill &s) {
  Nostd::String name;
  get_CSV_String(is, name);
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
  int health_effect;
  (is >> health_effect).ignore();
  bool health_mode;
  if (is >> health_mode)
    s = Skill(name, projectiles, health_effect, health_mode);
  return is;
}

int Skill::unchecked_health_effect(int current_health, int max_health) {
  return std::min(max_health,
                  current_health + (hm ? max_health * he / 100 : he));
}
