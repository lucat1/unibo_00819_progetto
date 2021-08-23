/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/15/2021

  skill.cpp: implementation of Data::Pawns::Skill.
*/

#include "skill.hpp"

#include <cstdlib>
#include <istream>

#include "../database.hpp"

using Data::Pawns::Projectile;
using Data::Pawns::Skill;

Skill::Skill(const Nostd::String &name,
             const Nostd::Vector<Projectile> &projectiles, int healthEffect,
             bool healthMode)
    : Pawn{name}, p{projectiles}, he{healthEffect}, hm{healthMode} {
  if (hm && he > 100)
    throw std::invalid_argument("Health effect cannot be > 100%.");
}

Nostd::Vector<Projectile> &Skill::projectiles() noexcept { return p; }

std::basic_istream<char> &Data::Pawns::operator>>(std::basic_istream<char> &is,
                                                  Skill &s) {
  Nostd::String name;
  get_CSV_String(is, name);
  int n; // number of projectiles
  (is >> n).ignore();
  Nostd::Vector<Projectile> projectiles(
      n, {Engine::Color::transparent, u' ', "", 0, 0, 0, 0});
  for (auto &p : projectiles)
    (is >> p).ignore();
  int health_effect;
  (is >> health_effect).ignore();
  bool health_mode;
  if (is >> health_mode)
    s = Skill(name, projectiles, health_effect, health_mode);
  return is;
}

int Skill::unchecked_health_effect(int current_health, int max_health) const {
  return std::min(max_health,
                  current_health + (hm ? max_health * he / 100 : he));
}
